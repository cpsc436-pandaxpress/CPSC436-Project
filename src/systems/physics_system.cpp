//
// Created by cowan on 30/01/19.
//

#include "components/platform.h"
#include "physics_system.h"
#include "components/panda.h"
#include "components/transform.h"

bool checkCollision(Panda pa, Transform pa_tr, Platform pl, Transform pl_tr);

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {
    auto view = registry.view<Panda, Transform>();

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
                transform.y = pl_transform.y - panda.height;
                panda.grounded = true;
                panda.y_velocity = 0;
            }
        }

        if (!panda.grounded) {
            panda.y_velocity += GRAVITY;
        }

        transform.x += panda.x_velocity;
        transform.y += panda.y_velocity;
    }
}

bool checkCollision(Panda pa, Transform pa_tr, Platform pl, Transform pl_tr) {
    return
        pa_tr.x <= pl_tr.x + pl.width &&
        pa_tr.x + pa.width >= pl_tr.x &&
        pa_tr.y <= pl_tr.y + pl.height &&
        pa_tr.y + pa.height >= pl_tr.y;
}