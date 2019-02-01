//
// Created by cowan on 30/01/19.
//

#include "components/collidable.h"
#include "physics_system.h"
#include "components/panda.h"
#include "components/transform.h"

bool checkCollision(Panda pa, Transform pa_tr, Collidable pl, Transform pl_tr);

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {
    auto view = registry.view<Panda, Transform>();

    auto pl_view = registry.view<Collidable, Transform>();

    for (auto entity: view) {
        auto& panda = view.get<Panda>(entity);
        auto& transform = view.get<Transform>(entity);

        if (!panda.grounded) {
            panda.y_velocity += GRAVITY;
        }

        transform.x += panda.x_velocity;
        transform.y += panda.y_velocity;
    }
}