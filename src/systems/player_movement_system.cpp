//
// Created by Kenneth William on 2019-01-31.
//

#include "player_movement_system.h"
#include "physics_system.h"
#include "components/panda.h"
#include "components/transform.h"

playerMovementSystem::playerMovementSystem() {}

void playerMovementSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {
    auto view = registry.view<Panda, Transform>();
    for (auto entity: view) {
        auto &panda = view.get<Panda>(entity);
        auto &transform = view.get<Transform>(entity);

        if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_LEFT)) {
            panda.x_velocity = -5;
        } else if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_RIGHT)) {
            panda.x_velocity = 5;
        } else if (blackboard.input_manager.key_just_released(SDL_SCANCODE_LEFT) ||
                   blackboard.input_manager.key_just_released(SDL_SCANCODE_RIGHT)) {
            panda.x_velocity = 0;
        }

        if (panda.grounded && blackboard.input_manager.key_just_pressed(SDL_SCANCODE_SPACE)) {

            transform.y -= 2;
            panda.y_velocity = -2;
            panda.grounded = false;
        }


    }
}
