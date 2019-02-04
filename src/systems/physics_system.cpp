//
// Created by cowan on 30/01/19.
//

#include "components/platform.h"
#include "components/bread.h"
#include "physics_system.h"
#include "components/panda.h"
#include "components/transform.h"

bool checkCollision(Panda pa, Transform pa_tr, Platform pl, Transform pl_tr);
bool checkEnemyPandaCollisionFatal(Panda pa, Transform pa_tr, Bread brd, Transform brd_tr);
bool checkEnemyPandaCollisionSafe(Panda pa, Transform pa_tr, Bread brd, Transform brd_tr);

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {
    auto view = registry.view<Panda, Transform>();
    auto bread_view = registry.view<Bread, Transform>();

    auto pl_view = registry.view<Platform, Transform>();

    for (auto entity: view) {
        auto& panda = view.get<Panda>(entity);
        auto& transform = view.get<Transform>(entity);

        for (auto pl_entity: pl_view) {
            if (panda.grounded)
                break;

            auto& platform = pl_view.get<Platform>(pl_entity);
            auto& pl_transform = pl_view.get<Transform>(pl_entity);

            if (checkCollision(panda, transform, platform, pl_transform)) {
                transform.y = pl_transform.y - (platform.height + panda.height);
                panda.grounded = true;
                panda.y_velocity = 0;
            }
        }

        for (auto enemy_entity: bread_view) {
            auto& bread = bread_view.get<Bread>(enemy_entity);
            auto& bread_transform = bread_view.get<Transform>(enemy_entity);

            if (!bread.alive) {
                bread.y_velocity = 400;
                bread_transform.y = bread_transform.y + bread.y_velocity * blackboard.delta_time;
                break;
            }

            bread_transform.x = bread_transform.x + bread.x_velocity * blackboard.delta_time;
            bread_transform.y = bread_transform.y + bread.y_velocity * blackboard.delta_time;


            if (checkEnemyPandaCollisionSafe(panda, transform, bread, bread_transform)) {
                bread.alive = false;
            } else if (checkEnemyPandaCollisionFatal(panda, transform, bread, bread_transform)) {
                panda.alive = false;
            }
        }


        if (!panda.grounded) {
            panda.y_velocity += GRAVITY * blackboard.delta_time;
        }

        transform.x += panda.x_velocity * blackboard.delta_time;
        transform.y += panda.y_velocity * blackboard.delta_time;
    }
}

bool checkCollision(Panda pa, Transform pa_tr, Platform pl, Transform pl_tr) {
    return
        pa_tr.x <= pl_tr.x + pl.width &&
        pa_tr.x + pa.width >= pl_tr.x &&
        pa_tr.y + pa.height <= pl_tr.y &&
        pa_tr.y + pa.height >= pl_tr.y - pl.height;
}

// Check if enemy collides with Panda and Panda is killed
bool checkEnemyPandaCollisionFatal(Panda pa, Transform pa_tr, Bread brd, Transform brd_tr) {
    return
            pa_tr.x <= brd_tr.x + brd.width &&
            pa_tr.x + 3*pa.width/4 >= brd_tr.x &&
            pa_tr.y <= brd_tr.y + brd.height &&
            pa_tr.y + pa.height >= brd_tr.y;
}

// Check if panda jumps on enemy
bool checkEnemyPandaCollisionSafe(Panda pa, Transform pa_tr, Bread brd, Transform brd_tr) {
    return
            pa_tr.x <= brd_tr.x + brd.width &&
            pa_tr.x + 3*pa.width/4 >= brd_tr.x &&
            pa_tr.y + pa.height + 5 >= brd_tr.y &&
            pa_tr.y + pa.height <= brd_tr.y &&
            pa.y_velocity > 0;
}