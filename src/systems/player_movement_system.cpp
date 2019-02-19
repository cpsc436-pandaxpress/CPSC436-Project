//
// Created by Kenneth William on 2019-01-31.
//

#include "player_movement_system.h"
#include "physics_system.h"
#include "components/panda.h"
#include "components/velocity.h"
#include "components/interactable.h"
#include "components/transform.h"
#include "components/obeys_gravity.h"


PlayerMovementSystem::PlayerMovementSystem() {}

void PlayerMovementSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {
    auto view = registry.view<Panda, Transform, Velocity, Interactable, ObeysGravity>();
    for (auto entity: view) {
        auto &panda = view.get<Panda>(entity);
        auto &transform = view.get<Transform>(entity);
        auto &velocity = view.get<Velocity>(entity);
        auto &walkable = view.get<Interactable>(entity);
        auto &gravity = view.get<ObeysGravity>(entity);

        if(!walkable.grounded) {
            if(holding_jump && blackboard.input_manager.key_released(SDL_SCANCODE_SPACE)) {
                holding_jump = false;
            }
            time_since_jump += blackboard.delta_time;
        }

        if (holding_jump && time_since_jump < 0.6f) {
            gravity.gravityFactor = 0.1f;
        }
        else {
            gravity.gravityFactor = 1.5f;
        }



        /*
         * Walking Left and Right
         */
        float vx = 0;
        if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)) {
            vx -= PANDA_SPEED;
        } else if (blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT)) {
            vx += PANDA_SPEED;
        }

        velocity.x_velocity = vx;

        /*
         * Jumping
         */

        if (walkable.grounded && blackboard.input_manager.key_just_pressed(SDL_SCANCODE_SPACE)) {
            walkable.grounded = false;
            velocity.y_velocity = -PANDA_JUMP_SPEED;
            time_since_jump = 0.f;
            holding_jump = true;
        }


    }
}
