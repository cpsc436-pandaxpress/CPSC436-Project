
#include "player_animation_system.h"
#include "components/panda.h"
#include "components/interactable.h"


PlayerAnimationSystem::PlayerAnimationSystem() {}

void PlayerAnimationSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {

    auto view = registry.view<Panda, Interactable, Sprite>();

    for (auto entity: view) {
        auto &panda = view.get<Panda>(entity);
        auto &walkable = view.get<Interactable>(entity);
        auto &sprite = view.get<Sprite>(entity);
        /*
         * Walking Left and Right and standing
         */

        if (walkable.grounded) {
            if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)) {
                sprite.set_uvs(walkL1uv1, walkL1uv2);
                direction_left = true;
            } else if (blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT)) {
                sprite.set_uvs(walkR1uv1, walkR1uv2);
                direction_left = false;
            } else if (direction_left){
                sprite.set_uvs(standLuv1, standLuv2);
            } else {
                sprite.set_uvs(standRuv1, standRuv2);
            }
        }

        /*
         * Jumping
         */

        if (walkable.grounded && blackboard.input_manager.key_just_pressed(SDL_SCANCODE_SPACE)) {
            walkable.grounded = false;
            holding_jump = true;
            time_since_jump = 0.f;
            if (!direction_left){
                sprite.set_uvs(jumpR1uv1, jumpR1uv2);
            }
        }


        if (!walkable.grounded) {
            // left and right in air
            if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)) {
                direction_left = true;
                sprite.set_uvs(jumpL1uv1, jumpL1uv2);
            } else if(blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT) || !direction_left){
                direction_left = false;
                sprite.set_uvs(jumpR1uv1, jumpR1uv2);
            } else {
                sprite.set_uvs(jumpL1uv1, jumpL1uv2);
            }
            //falling
            if (blackboard.input_manager.key_released(SDL_SCANCODE_SPACE) || (holding_jump && time_since_jump >= 0.6f)) {
                holding_jump = false;
                time_since_jump = 0.f;

                if (direction_left){
                    sprite.set_uvs(jumpLfallinguv1, jumpLfallinguv2);
                } else {
                    sprite.set_uvs(jumpRfallinguv1, jumpRfallinguv2);
                }
            }
            time_since_jump += blackboard.delta_time;
        }

    }
}
