//
// Created by Kenneth William on 2019-01-31.
//


#include <iostream>
#include "components/collidable.h"
#include "components/velocity.h"
#include "components/walkable.h"
#include "collision_system.h"
#include "components/panda.h"
#include "components/transform.h"
using namespace std;

bool checkCollision(Collidable collidable1, Transform transform1, Velocity velocity1, Collidable collidable2, Transform transform2);
CollisionSystem::CollisionSystem() {}


void CollisionSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {

    /*
     * Checking Collisions between walkables (entities able to walk on platforms) and platforms
     */

    auto walkable_view = registry.view<Walkable, Collidable, Transform, Velocity>();

    auto platform_view = registry.view<Collidable, Transform>();

    for (auto entity: walkable_view) {
        auto& walkable = walkable_view.get<Walkable>(entity);
        auto& transform1 = walkable_view.get<Transform>(entity);
        auto& velocity = walkable_view.get<Velocity>(entity);
        auto& collidable1 = walkable_view.get<Collidable>(entity);

        bool hitTheGround = false;
        for (auto pl_entity: platform_view) {

            auto& collidable2 = platform_view.get<Collidable>(pl_entity);
            auto& transform2 = platform_view.get<Transform>(pl_entity);

            if (checkCollision(collidable1, transform1, velocity, collidable2, transform2)) {
                if(transform1.y < transform2.y) {
                    transform1.y = transform2.y - collidable1.height;
                    //walkable.grounded = true;
                    hitTheGround = true;
                    //cout << "GROUNDED \n";
                    //cout << "VELOCITY Y: "<< panda.y_velocity <<  "\n";
                }else{
                    //velocity.y_velocity = 0.f;
                    //walkable.grounded=false;

                }
            }

        }
        if(!hitTheGround){
            walkable.grounded = false;
        } else{
            walkable.grounded = true;
        }

    }

}

bool checkCollision(Collidable collidable1, Transform transform1, Velocity velocity1, Collidable collidable2, Transform transform2) {

    return
            transform1.x <= transform2.x + collidable2.width &&
                    transform1.x + collidable1.width >= transform2.x &&
                    transform1.y+velocity1.y_velocity <= transform2.y + collidable2.height &&
                    transform1.y+velocity1.y_velocity + collidable1.height >= transform2.y;
    /*
            pa_tr.x <= pl_tr.x + pl.width &&
            pa_tr.x + pa.width >= pl_tr.x &&
            pa_tr.y+pa.y_velocity <= pl_tr.y + pl.height &&
            pa_tr.y+pa.y_velocity + pa.height >= pl_tr.y;
    */
}
