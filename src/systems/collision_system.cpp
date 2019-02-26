//
// Created by Kenneth William on 2019-01-31.
//


#include <iostream>
#include "components/collidable.h"
#include "components/platform.h"
#include "components/velocity.h"
#include "components/interactable.h"
#include "collision_system.h"
#include "components/panda.h"
#include "components/transform.h"
#include "components/bread.h"
#include "components/ghost.h"
#include "components/llama.h"
#include "components/spit.h"
#include "components/obstacle.h"
using namespace std;

bool checkCollision(Collidable collidable1, Transform transform1, Velocity velocity1, Collidable collidable2, Transform transform2);
bool checkEnemyPandaCollisionFatal(Collidable pa_co, Transform pa_tr, Collidable br_co, Transform brd_tr);
bool checkEnemyPandaCollisionSafe(Collidable pa_co, Transform pa_tr, Velocity pa_velocity, Collidable br_co, Transform br_tr);
bool checkObstaclePandaCollision(Collidable pa_co, Transform pa_tr, Collidable ob_co, Transform ob_tr);

CollisionSystem::CollisionSystem() {}


void CollisionSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {

    /*
     * Checking Collisions between interactables and platforms
     * This should be refactored into its own function later as we will be making a few of these loops
     */

    auto interactable_view = registry.view<Interactable, Collidable, Transform, Velocity>();

    auto platform_view = registry.view<Collidable, Transform, Platform>();

    for (auto entity: interactable_view) {
        auto &interactable = interactable_view.get<Interactable>(entity);
        auto &transform1 = interactable_view.get<Transform>(entity);
        auto &velocity = interactable_view.get<Velocity>(entity);
        auto &collidable1 = interactable_view.get<Collidable>(entity);
        bool hitTheGround = false;

        for (auto pl_entity: platform_view) {
            if (registry.has<Panda>(pl_entity) || registry.has<Bread>(pl_entity))
                break;

            auto &collidable2 = platform_view.get<Collidable>(pl_entity);
            auto &transform2 = platform_view.get<Transform>(pl_entity);

            if (checkCollision(collidable1, transform1, velocity, collidable2, transform2)) {
                if (transform1.y < transform2.y) {
                    transform1.y = transform2.y - collidable1.height / 2 - collidable2.height / 2;
                    hitTheGround = true;
                }
            }

        }
        if (!hitTheGround) {
            interactable.grounded = false;
        } else {
            interactable.grounded = true;
        }
    }

    // TODO: generalize this to use the causesDamage component
    auto pandas_view = registry.view<Panda, Transform, Interactable, Collidable, Velocity>();
    auto bread_view = registry.view<Bread, Transform, Interactable, Collidable>();
    auto ghost_view = registry.view<Ghost, Transform, Collidable>();
    auto llama_view = registry.view<Llama, Transform, Interactable, Collidable>();
    auto projectile_view = registry.view<Spit, Transform, Interactable, Collidable>();
    auto obstacle_view = registry.view<Obstacle, Transform, Collidable>();

    for (auto panda_entity : pandas_view) {
        auto &panda = pandas_view.get<Panda>(panda_entity);
        auto &pa_collidable = pandas_view.get<Collidable>(panda_entity);
        auto &pa_transform = pandas_view.get<Transform>(panda_entity);
        auto &pa_velocity = pandas_view.get<Velocity>(panda_entity);

        for (auto enemy_entity : bread_view) {
            auto &bread = bread_view.get<Bread>(enemy_entity);
            auto &br_collidable = bread_view.get<Collidable>(enemy_entity);
            auto &br_transform = bread_view.get<Transform>(enemy_entity);

            if (!bread.alive) {
                registry.remove<Interactable>(enemy_entity);
                break;
            }

            if (checkEnemyPandaCollisionSafe(pa_collidable, pa_transform, pa_velocity, br_collidable, br_transform)) {
                bread.alive = false;
                pa_velocity.y_velocity = -400.f;
            } else if (checkEnemyPandaCollisionFatal(pa_collidable, pa_transform, br_collidable, br_transform)) {
                panda.alive = false;
            }
        }

        for (auto enemy_entity : ghost_view) {
            auto &ghost = ghost_view.get<Ghost>(enemy_entity);
            auto &gh_collidable = ghost_view.get<Collidable>(enemy_entity);
            auto &gh_transform = ghost_view.get<Transform>(enemy_entity);

            if (checkEnemyPandaCollisionSafe(pa_collidable, pa_transform, pa_velocity, gh_collidable, gh_transform)) {
                panda.alive = false;
            } else if (checkEnemyPandaCollisionFatal(pa_collidable, pa_transform, gh_collidable, gh_transform)) {
                panda.alive = false;
            }
        }

        for (auto enemy_entity : llama_view) {
            auto &llama = llama_view.get<Llama>(enemy_entity);
            auto &br_collidable = llama_view.get<Collidable>(enemy_entity);
            auto &br_transform = llama_view.get<Transform>(enemy_entity);

            if (!llama.alive) {
                registry.remove<Interactable>(enemy_entity);
                break;
            }

            if (checkEnemyPandaCollisionSafe(pa_collidable, pa_transform, pa_velocity, br_collidable,
                                             br_transform)) {
                llama.alive = false;
                pa_velocity.y_velocity = -400.f;
            } else if (checkEnemyPandaCollisionFatal(pa_collidable, pa_transform, br_collidable, br_transform)) {
                panda.alive = false;
            }
        }

        for (auto enemy_entity : projectile_view) {
            auto &projectile = projectile_view.get<Spit>(enemy_entity);
            auto &proj_collidable = projectile_view.get<Collidable>(enemy_entity);
            auto &proj_transform = projectile_view.get<Transform>(enemy_entity);

            if (checkEnemyPandaCollisionSafe(pa_collidable, pa_transform, pa_velocity, proj_collidable,
                                             proj_transform)) {
                panda.alive = false;
            } else if (checkEnemyPandaCollisionFatal(pa_collidable, pa_transform, proj_collidable,
                                                     proj_transform)) {
                panda.alive = false;
            }
        }

        for (auto obstacle_entity : obstacle_view) {
            auto &obstacle = obstacle_view.get<Obstacle>(obstacle_entity);
            auto &ob_co = obstacle_view.get<Collidable>(obstacle_entity);
            auto &ob_tr = obstacle_view.get<Transform>(obstacle_entity);

            if (checkObstaclePandaCollision(pa_collidable, pa_transform, ob_co, ob_tr)) {
                panda.alive = false;
            }
        }
    }
}

bool checkCollision(Collidable collidable1, Transform transform1, Velocity velocity1, Collidable collidable2, Transform transform2) {

    return
            transform1.x - collidable1.width / 2 <= transform2.x + collidable2.width / 2 &&
                    transform1.x + collidable1.width / 2 >= transform2.x - collidable2.width / 2 &&
                    transform1.y - collidable1.height / 2 <= transform2.y + collidable2.height / 2 &&
                    transform1.y + collidable1.height / 2 >= transform2.y - collidable2.height / 2 &&
                    velocity1.y_velocity > 0;
}

bool checkEnemyPandaCollisionFatal(Collidable pa_co, Transform pa_tr, Collidable br_co, Transform brd_tr) {
    return
            pa_tr.x - pa_co.width / 2 <= brd_tr.x + br_co.width / 2 &&
            pa_tr.x + pa_co.width / 2 >= brd_tr.x - br_co.width / 2 &&
            pa_tr.y - pa_co.height / 2 <= brd_tr.y + br_co.height / 2 &&
            pa_tr.y + pa_co.height / 2 >= brd_tr.y - br_co.height / 2;
}

// Check if panda jumps on enemy
bool checkEnemyPandaCollisionSafe(Collidable pa_co, Transform pa_tr, Velocity pa_velocity, Collidable br_co, Transform br_tr) {
    return
            pa_tr.x - pa_co.width / 2 <= br_tr.x + br_co.width / 2 &&
            pa_tr.x + pa_co.width / 2 >= br_tr.x - br_co.width / 2 &&
            pa_tr.y + pa_co.height / 2 >= br_tr.y - br_co.height / 2 - 5 &&
            pa_tr.y + pa_co.height / 2 <= br_tr.y - br_co.height / 2 + 5&&
            pa_velocity.y_velocity > 0;
}

bool checkObstaclePandaCollision(Collidable pa_co, Transform pa_tr, Collidable ob_co, Transform ob_tr) {
    return
            pa_tr.x - pa_co.width / 2 <= ob_tr.x + ob_co.width / 2 &&
            pa_tr.x + pa_co.width / 2 >= ob_tr.x - ob_co.width / 2 &&
            pa_tr.y - pa_co.height / 2 <= ob_tr.y + ob_co.height / 2 &&
            pa_tr.y + pa_co.height / 2 >= ob_tr.y - ob_co.height / 2;
}