
#include "player_animation_system.h"
#include "components/panda.h"
#include "components/interactable.h"
#include "util/constants.h"
#include "scene/horizontal_scene.h"




PlayerAnimationSystem::PlayerAnimationSystem(SceneID scene_id) :
        scene_id(scene_id) {}

void PlayerAnimationSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {

    auto view = registry.view<Panda, Interactable, Sprite>();

    for (auto entity: view) {
        auto &panda = view.get<Panda>(entity);
        auto &walkable = view.get<Interactable>(entity);
        auto &sprite = view.get<Sprite>(entity);

        switch (scene_id) {
            case HORIZONTAL_SCENE_ID:
                update_horizontal_scene(blackboard, walkable, sprite);
                break;
            case VERTICAL_SCENE_ID:
                update_vertical_boss_scene(blackboard, walkable, sprite);
                break;
            case BOSS_SCENE_ID:
                update_vertical_boss_scene(blackboard, walkable, sprite);
                break;
            default:
                fprintf(stderr, "Invalid scene ID: %d\n", scene_id);
        }

    }
}

void PlayerAnimationSystem::update_horizontal_scene(Blackboard &blackboard, Interactable &walkable, Sprite &sprite) {
    float frameRate = 8.f;
    int frames, row;
    /*
     * Walking
     */
    if (walkable.grounded) {
        frames = 8;
        row = 0;
        animate(frames, row, sprite);
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
        animate(frames, row, sprite);
        if (blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT)){
            frameRate = 2.f;
        } else if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)){
            frameRate = 0.8f;
        } else {
            frameRate = 1.f;
        }
    }

    animationTime += frameRate*blackboard.delta_time;
//    animationTime += frameRate;

}

void PlayerAnimationSystem::update_vertical_boss_scene(Blackboard &blackboard, Interactable &walkable, Sprite &sprite) {
    float frameRate = 8.f;
    int frames, row;
    bool idle = true;

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
        if (direction_left) {
            if (!idle){
                frames = 8;
                row = 1;
                animate(frames, row, sprite);
            } else {
                frames = 1;
                row = 1;
                animate(frames, row, sprite);
            }

        } else if (!direction_left && !idle){
            frames = 8;
            row = 0;
            animate(frames, row, sprite);
        } else {
            frames = 1;
            row = 0;
            animate(frames, row, sprite);
        }
    }

    /*
     * Jumping
     */

    if (!walkable.grounded) {
        frameRate = 1.f;
        if (direction_left) {
            frames = 2;
            row = 3;
            animate(frames, row, sprite);
        } else {
            frames = 2;
            row = 2;
            animate(frames, row, sprite);
        }
    }
    animationTime += frameRate*blackboard.delta_time;

}

void PlayerAnimationSystem::animate(int frames, int row, Sprite &sprite){
    int index = ((int) animationTime % frames);
    vec2 uv1 = {index*pandawidth + 0.006f, pandaheight*row - 0.012f};
    vec2 uv2 = {(index+1)*pandawidth + 0.006f, pandaheight*(1+row) - 0.012f};
    sprite.set_uvs(uv1, uv2);
}