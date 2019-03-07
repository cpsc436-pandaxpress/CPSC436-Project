//
// Created by Prayansh Srivastava on 2019-03-07.
//

#include <components/transform.h>
#include <graphics/health_bar.h>
#include "health_bar_transform_system.h"

HealthBarTransformSystem::HealthBarTransformSystem() {}

void HealthBarTransformSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    // construct a view for all entites with a position and sprite component
    auto view = registry.view<Transform, HealthBar>();

    // foreach loop over all entities in view
    for (auto entity: view) {
        //get the position and sprite for the current entity
        auto &transform = view.get<Transform>(entity);
        auto &healthBar = view.get<HealthBar>(entity);
        // keep at bottom of screen centered
        transform.x = blackboard.camera.position().x;
        transform.y = blackboard.camera.position().y + blackboard.camera.size().y / 2 - 100.f;
        //transform the sprite
        healthBar.set_pos(transform.x, transform.y);
        healthBar.set_rotation_rad(transform.theta);
        healthBar.set_scale(transform.x_scale, transform.y_scale);
    }
}