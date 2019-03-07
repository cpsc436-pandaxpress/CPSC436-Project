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
        auto &walkable = view.get<Interactable>(entity);
        auto &gravity = view.get<ObeysGravity>(entity);

        if(!walkable.grounded) {
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

        if (!panda.recovering) {
            switch (scene_id) {
                case HORIZONTAL_SCENE_ID:
                    update_horizontal_scene(blackboard, velocity);
                    break;
                case VERTICAL_SCENE_ID:
                    update_vertical_scene(blackboard, velocity, panda);
                    break;
                case BOSS_SCENE_ID:
                    update_boss_scene(blackboard, velocity, panda);
                    break;
                default:
                    fprintf(stderr, "Invalid scene ID: %d\n", scene_id);
            }
        }

        /*
         * Jumping
         */

        if (walkable.grounded && blackboard.input_manager.key_pressed(SDL_SCANCODE_SPACE)) {
            walkable.grounded = false;
            velocity.y_velocity = -PANDA_JUMP_SPEED;
            time_since_jump = 0.f;
            blackboard.soundManager.playSFX(SFX_JUMP);
            holding_jump = true;
        }


    }
}

void PlayerMovementSystem::update_horizontal_scene(Blackboard &blackboard, Velocity &velocity) {
    const float dvx = PANDA_HS_ACCELERATION * blackboard.delta_time;
    const float camera_vx = HorizontalScene::CAMERA_SPEED;
    if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)) {
        // First if for quick turn around, otherwise it felt too slidey when switching movement direction
        if (velocity.x_velocity > camera_vx) {
            velocity.x_velocity = camera_vx - dvx;
        } else if (velocity.x_velocity - dvx > camera_vx - PANDA_BACK_OFFSET_SPEED) {
            velocity.x_velocity -= dvx;
        } else {
            velocity.x_velocity = camera_vx - PANDA_BACK_OFFSET_SPEED;
        }
    } else if (blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT)) {
        if (velocity.x_velocity < camera_vx) {
            velocity.x_velocity = camera_vx + dvx;
        } else if (velocity.x_velocity + dvx < camera_vx + PANDA_OFFSET_SPEED) {
            velocity.x_velocity += dvx;
        } else {
            velocity.x_velocity = camera_vx + PANDA_OFFSET_SPEED;
        }
    } else {
        if (velocity.x_velocity - dvx > camera_vx) {
            velocity.x_velocity -= dvx;
        } else if (velocity.x_velocity + dvx < camera_vx) {
            velocity.x_velocity += dvx;
        } else {
            velocity.x_velocity = camera_vx;
        }
    }
}

void PlayerMovementSystem::update_vertical_scene(Blackboard &blackboard,
        Velocity &velocity, Panda &panda) {
    const float dvx = PANDA_ACCELERATION * blackboard.delta_time;
    if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)) {
        // First if for quick turn around, otherwise it felt too slidey when switching movement direction
        if (velocity.x_velocity > 0) {
            velocity.x_velocity = -dvx;
        } else if (velocity.x_velocity - dvx > -PANDA_SPEED) {
            velocity.x_velocity -= dvx;
        } else {
            velocity.x_velocity = -PANDA_SPEED;
        }
      panda.facingRight = false;
    } else if (blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT)) {
        if (velocity.x_velocity < 0) {
            velocity.x_velocity = dvx;
        } else if (velocity.x_velocity + dvx < PANDA_SPEED) {
            velocity.x_velocity += dvx;
        } else {
            velocity.x_velocity = PANDA_SPEED;
        }
      panda.facingRight = true;
    } else {
        if (velocity.x_velocity - dvx > 0) {
            velocity.x_velocity -= dvx;
        } else if (velocity.x_velocity + dvx < 0) {
            velocity.x_velocity += dvx;
        } else {
            velocity.x_velocity = 0;
        }
    }
}

void PlayerMovementSystem::update_boss_scene(Blackboard &blackboard,
        Velocity &velocity, Panda &panda) {
    const float dvx = PANDA_ACCELERATION * blackboard.delta_time;
    if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)) {
        // First if for quick turn around, otherwise it felt too slidey when switching movement direction
        if (velocity.x_velocity > 0) {
            velocity.x_velocity = -dvx;
        } else if (velocity.x_velocity - dvx > -PANDA_SPEED) {
                velocity.x_velocity -= dvx;
        } else {
            velocity.x_velocity = -PANDA_SPEED;
        }
        panda.facingRight = false;
    } else if (blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT)) {
        if (velocity.x_velocity < 0) {
            velocity.x_velocity = dvx;
        } else if (velocity.x_velocity + dvx < PANDA_SPEED) {
            velocity.x_velocity += dvx;
        } else {
            velocity.x_velocity = PANDA_SPEED;
        }
        panda.facingRight = true;
    } else {
        if (velocity.x_velocity - dvx > 0) {
            velocity.x_velocity -= dvx;
        } else if (velocity.x_velocity + dvx < 0) {
            velocity.x_velocity += dvx;
        } else {
            velocity.x_velocity = 0;
        }
    }
}
