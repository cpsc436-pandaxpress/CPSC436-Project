//
// Created by Kenneth William on 2019-01-31.
//


#include <iostream>
#include "components/collidable.h"
#include "components/velocity.h"
#include "components/interactable.h"
#include "collision_system.h"
#include "components/panda.h"
#include "components/transform.h"
#include "components/bread.h"
using namespace std;

bool checkCollision(Collidable collidable1, Transform transform1, Velocity velocity1, Collidable collidable2, Transform transform2);
bool checkEnemyPandaCollisionFatal(Collidable pa_co, Transform pa_tr, Collidable br_co, Transform brd_tr);
bool checkEnemyPandaCollisionSafe(Collidable pa_co, Transform pa_tr, Velocity pa_velocity, Collidable br_co, Transform br_tr);

CollisionSystem::CollisionSystem() {}


void CollisionSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {

    /*
     * Checking Collisions between walkables (entities able to walk on platforms) and platforms
     */

    auto interactable_view = registry.view<Interactable, Collidable, Transform, Velocity>();

    auto platform_view = registry.view<Collidable, Transform>();

    for (auto entity: interactable_view) {
        auto& interactable = interactable_view.get<Interactable>(entity);
        auto& transform1 = interactable_view.get<Transform>(entity);
        auto& velocity = interactable_view.get<Velocity>(entity);
        auto& collidable1 = interactable_view.get<Collidable>(entity);

        bool hitTheGround = false;
        bool hitTheCeiling = false;

        for (auto pl_entity: platform_view) {
            if (registry.has<Panda>(pl_entity) || registry.has<Bread>(pl_entity))
                break;

            auto& collidable2 = platform_view.get<Collidable>(pl_entity);
            auto& transform2 = platform_view.get<Transform>(pl_entity);

            if (checkCollision(collidable1, transform1, velocity, collidable2, transform2)) {
                if(transform1.y < transform2.y) {
                    transform1.y = transform2.y - collidable1.height - collidable2.height;
                    hitTheGround = true;
                }else{

                }
            }

        }
        if(!hitTheGround){
            interactable.grounded = false;
        } else{
            interactable.grounded = true;
        }
    }

    // TODO: generalize this to use the causesDamage component
    auto pandas_view = registry.view<Panda, Transform, Interactable, Collidable, Velocity>();
    auto bread_view = registry.view<Bread, Transform, Interactable, Collidable>();

    for (auto panda_entity : pandas_view) {
        auto& panda = pandas_view.get<Panda>(panda_entity);
        auto& pa_collidable = pandas_view.get<Collidable>(panda_entity);
        auto& pa_transform = pandas_view.get<Transform>(panda_entity);
        auto& pa_velocity = pandas_view.get<Velocity>(panda_entity);

        for (auto enemy_entity : bread_view) {
            auto& bread = bread_view.get<Bread>(enemy_entity);
            auto& br_collidable = bread_view.get<Collidable>(enemy_entity);
            auto& br_transform = bread_view.get<Transform>(enemy_entity);

            if (!bread.alive) {
                registry.remove<Interactable>(enemy_entity);
                break;
            }
//
//            bread_transform.x = bread_transform.x + bread.x_velocity;
//            bread_transform.y = bread_transform.y + bread.y_velocity;

            if (checkEnemyPandaCollisionSafe(pa_collidable, pa_transform, pa_velocity, br_collidable, br_transform)) {
                bread.alive = false;
            } else if (checkEnemyPandaCollisionFatal(pa_collidable, pa_transform, br_collidable, br_transform)) {
                panda.alive = false;
            }
        }
    }
}

bool checkCollision(Collidable collidable1, Transform transform1, Velocity velocity1, Collidable collidable2, Transform transform2) {

    return
            transform1.x - collidable1.width <= transform2.x + collidable2.width &&
                    transform1.x + collidable1.width >= transform2.x - collidable2.width &&
                    transform1.y + velocity1.y_velocity - collidable1.height <= transform2.y + collidable2.height &&
                    transform1.y + velocity1.y_velocity + collidable1.height >= transform2.y - collidable2.height;
    /*
            pa_tr.x <= pl_tr.x + pl.width &&
            pa_tr.x + pa.width >= pl_tr.x &&
            pa_tr.y+pa.y_velocity <= pl_tr.y + pl.height &&
            pa_tr.y+pa.y_velocity + pa.height >= pl_tr.y;
    */
}

bool checkEnemyPandaCollisionFatal(Collidable pa_co, Transform pa_tr, Collidable br_co, Transform brd_tr) {
    return
            pa_tr.x - pa_co.width <= brd_tr.x + br_co.width &&
            pa_tr.x + pa_co.width >= brd_tr.x - br_co.width &&
            pa_tr.y - pa_co.height <= brd_tr.y + br_co.height &&
            pa_tr.y + pa_co.height >= brd_tr.y - br_co.height;
}

// Check if panda jumps on enemy
bool checkEnemyPandaCollisionSafe(Collidable pa_co, Transform pa_tr, Velocity pa_velocity, Collidable br_co, Transform br_tr) {
    return
            pa_tr.x - pa_co.width <= br_tr.x + br_co.width &&
            pa_tr.x + pa_co.width >= br_tr.x - br_co.width &&
            pa_tr.y + pa_co.height >= br_tr.y - br_co.height - 5 &&
            pa_tr.y + pa_co.height <= br_tr.y - br_co.height + 5&&
            pa_velocity.y_velocity > 0;
}