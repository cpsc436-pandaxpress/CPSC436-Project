
#include "player_animation_system.h"
#include "components/panda.h"
#include "util/constants.h"
#include "scene/horizontal_scene.h"




PlayerAnimationSystem::PlayerAnimationSystem(SceneType scene_type) :
        scene_type(scene_type) {}

void PlayerAnimationSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {

    auto view = registry.view<Panda, Interactable, Sprite>();

    for (auto entity: view) {
        auto &panda = view.get<Panda>(entity);
        auto &walkable = view.get<Interactable>(entity);
        auto &sprite = view.get<Sprite>(entity);

        switch (scene_type) {
            case JUNGLE_TYPE:
                update_horizontal_scene(blackboard, walkable, sprite);
                break;
            case SKY_TYPE:
                update_vertical_boss_scene(blackboard, walkable, sprite);
                break;
            case BOSS_TYPE:
                update_vertical_boss_scene(blackboard, walkable, sprite);
                break;
            default:
                fprintf(stderr, "Invalid scene ID: %d\n", scene_type);
        }

    }
}

void PlayerAnimationSystem::update_horizontal_scene(Blackboard &blackboard, Interactable &walkable, Sprite &sprite) {
    float frameRate = 8.f;
    int frames, row;
    int index = 0;
    /*
     * Walking
     */
    if (walkable.grounded) {
        frames = 8;
        row = 2;
        if (blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT)){
            frameRate = 10.f;
        } else if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)){
            frameRate = 6.f;
        }
    }
    /*
     * Jumping
     */
    if (!walkable.grounded) {
        frames = 2;
        row = 2;
        index = 8;
        if (blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT)){
            frameRate = 3.f;
        } else if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)){
            frameRate = 1.f;
        } else {
            frameRate = 2.f;
        }
    }
    animate(frames, index, row, sprite);

    animationTime += frameRate*blackboard.delta_time;

}

void PlayerAnimationSystem::update_vertical_boss_scene(Blackboard &blackboard, Interactable &walkable, Sprite &sprite) {
    float frameRate = 8.f;
    int frames, index, row;
    bool idle = true;
    index = 0;

    if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)) {
        direction_left = true;
        idle = false;
    } else if(blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT)){
        direction_left = false;
        idle = false;
    }
    /*
     * Walking
     */

    if (walkable.grounded) {
        frames = 8;
        if (direction_left) {
            if (!idle){
                row = 3;
            } else {
                row = 1;
                frameRate = 3.f;
            }

        } else if (!direction_left && !idle){
            row = 2;
        } else {
            row = 0;
            frameRate = 3.f;
        }
    }

    /*
     * Jumping
     */

    if (!walkable.grounded) {
        frameRate = 1.f;
        frames = 2;
        index = 8;
        if (direction_left) {
            row = 3;
        } else {
            row = 2;
        }
    }
    animate(frames, index, row, sprite);
    animationTime += frameRate*blackboard.delta_time;

}

void PlayerAnimationSystem::animate(int frames, int index, int row, Sprite &sprite){
    index += ((int) animationTime % frames);
    vec2 uv1 = {index*pandawidth, pandaheight*row};
    vec2 uv2 = {(index+1)*pandawidth - 0.001f, pandaheight*(1+row) - 0.02f};
    sprite.set_uvs(uv1, uv2);
}