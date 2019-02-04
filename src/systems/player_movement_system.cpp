//
// Created by Kenneth William on 2019-01-31.
//

#include "player_movement_system.h"
#include "physics_system.h"
#include "components/panda.h"
#include "components/velocity.h"
#include "components/interactable.h"
#include "components/transform.h"


PlayerMovementSystem::PlayerMovementSystem() {}

void PlayerMovementSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {
    auto view = registry.view<Panda, Transform, Velocity, Interactable>();
    for (auto entity: view) {
        auto &panda = view.get<Panda>(entity);
        auto &transform = view.get<Transform>(entity);
        auto &velocity = view.get<Velocity>(entity);
        auto &walkable = view.get<Interactable>(entity);

        /*
         * Walking Left and Right
         */

        if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_LEFT)) {
            velocity.x_velocity = -2.f;
        } else if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_RIGHT)) {
            velocity.x_velocity = 2.f;
        } else if (blackboard.input_manager.key_just_released(SDL_SCANCODE_LEFT) ||
                   blackboard.input_manager.key_just_released(SDL_SCANCODE_RIGHT)) {
            velocity.x_velocity = 0.f;
        }

        /*
         * Jumping
         */

        if (walkable.grounded && blackboard.input_manager.key_just_pressed(SDL_SCANCODE_SPACE)) {

            walkable.grounded = false;
            velocity.y_velocity = -2.f;

        }


    }
}
