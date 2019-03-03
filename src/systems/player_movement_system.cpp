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
#include "util/constants.h"
#include "scene/horizontal_scene.h"


PlayerMovementSystem::PlayerMovementSystem(SceneID scene_id) :
    scene_id(scene_id) {}

void PlayerMovementSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {
    auto view = registry.view<Panda, Transform, Velocity, Interactable, ObeysGravity>();
    for (auto entity: view) {
        auto &panda = view.get<Panda>(entity);
        auto &transform = view.get<Transform>(entity);
        auto &velocity = view.get<Velocity>(entity);
        auto &interactable = view.get<Interactable>(entity);
        auto &gravity = view.get<ObeysGravity>(entity);

        if(!interactable.grounded) {
            if(holding_jump && blackboard.input_manager.key_released(SDL_SCANCODE_SPACE)) {
                holding_jump = false;
            }
            time_since_jump += blackboard.delta_time;
        }

        if (holding_jump && time_since_jump < 0.6f) {
            gravity.gravityFactor = 0.5f;
        }
        else {
            gravity.gravityFactor = 1.5f;
        }

        if(panda.damaged){
            if(interactable.grounded){
                panda.damaged=false;
                panda.invincible=false;
            }
        }

        if(!panda.damaged) { // Player can't control direction until he hits the ground if damaged
            switch (scene_id) {
                case HORIZONTAL_SCENE_ID:

                    update_horizontal_scene(blackboard, velocity);

                    break;
                case VERTICAL_SCENE_ID:
                    update_vertical_scene(blackboard, velocity);
                    break;
                case BOSS_SCENE_ID:
                    update_boss_scene(blackboard, velocity);
                    break;
                default:
                    fprintf(stderr, "Invalid scene ID: %d\n", scene_id);
            }
        }

        /*
         * Jumping
         */

        if (interactable.grounded && blackboard.input_manager.key_pressed(SDL_SCANCODE_SPACE)) {
            interactable.grounded = false;
            velocity.y_velocity = -PANDA_JUMP_SPEED;
            time_since_jump = 0.f;
            holding_jump = true;
        }


    }
}

void PlayerMovementSystem::update_horizontal_scene(Blackboard &blackboard, Velocity &velocity) {
    float vx = HorizontalScene::CAMERA_SPEED;
    if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)) {
        vx -= PANDA_OFFSET_SPEED * 1.5;
    } else if (blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT)) {
        vx += PANDA_OFFSET_SPEED;
    }
        velocity.x_velocity = vx;
}

void PlayerMovementSystem::update_vertical_scene(Blackboard &blackboard, Velocity &velocity) {
    if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)) {
        velocity.x_velocity = -PANDA_SPEED;
    } else if (blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT)) {
        velocity.x_velocity = PANDA_SPEED;
    } else {
        velocity.x_velocity = 0;
    }
}

void PlayerMovementSystem::update_boss_scene(Blackboard &blackboard, Velocity &velocity) {
    if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)) {
        velocity.x_velocity = -PANDA_SPEED;
    } else if (blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT)) {
        velocity.x_velocity = PANDA_SPEED;
    } else {
        velocity.x_velocity = 0;
    }
}
