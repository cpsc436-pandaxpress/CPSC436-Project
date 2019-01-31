//
// Created by cowan on 30/01/19.
//

#include "physics_system.h"
#include "../components/physics.h"
#include "components/transform.h"

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {
    auto view = registry.view<Physics, Transform>();

    for (auto entity: view) {
        auto& physics = view.get<Physics>(entity);
        auto& transform = view.get<Transform>(entity);


        if (physics.gravity) {
            physics.y_velocity += GRAVITY;
        }

        transform.y += physics.y_velocity;
    }
}