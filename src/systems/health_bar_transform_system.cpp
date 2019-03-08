//
// Created by Prayansh Srivastava on 2019-03-07.
//

#include <components/transform.h>
#include <graphics/health_bar.h>
#include <components/panda.h>
#include <components/health.h>
#include "health_bar_transform_system.h"

HealthBarTransformSystem::HealthBarTransformSystem() {}

void HealthBarTransformSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    // construct a view for all entites with a position and sprite component
    auto view = registry.view<Panda, Health, Transform, HealthBar>();

    // foreach loop over all entities in view
    for (auto entity: view) {
        //get the position and sprite for the current entity
        auto &panda = view.get<Panda>(entity);
        auto &health = view.get<Health>(entity);
        auto &transform = view.get<Transform>(entity);
        auto &healthBar = view.get<HealthBar>(entity);
        // transform the HealthBar
        // keep at bottom of screen centered
        healthBar.set_status(0);
        if (panda.invincible) {
            healthBar.set_status(1);
        }
        healthBar.set_pos(transform.x,
                          blackboard.camera.position().y + blackboard.camera.size().y / 2 - 100.f);
        healthBar.set_rotation_rad(transform.theta);
        healthBar.set_health(health.healthPoints / (float) health.max_health);
    }
}