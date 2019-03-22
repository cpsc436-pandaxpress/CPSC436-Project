
#include "player_animation_system.h"
#include "util/constants.h"
#include "scene/horizontal_scene.h"


PlayerAnimationSystem::PlayerAnimationSystem(SceneID scene_id) :
        scene_id(scene_id) {}

void PlayerAnimationSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {

    auto view = registry.view<Panda, Interactable, Sprite, Transform>();

    for (auto entity: view) {
        auto &panda = view.get<Panda>(entity);
        auto &transform = view.get<Transform>(entity);
        auto &walkable = view.get<Interactable>(entity);
        auto &sprite = view.get<Sprite>(entity);

        switch (scene_id) {
            case HORIZONTAL_SCENE_ID:
                update_horizontal_scene(blackboard, walkable, sprite, panda);
                break;
            case VERTICAL_SCENE_ID:
                update_vertical_boss_scene(blackboard, walkable, sprite, panda, transform);
                break;
            case BOSS_SCENE_ID:
                update_vertical_boss_scene(blackboard, walkable, sprite, panda, transform);
                break;
            default:
                fprintf(stderr, "Invalid scene ID: %d\n", scene_id);
        }

    }
}

void PlayerAnimationSystem::update_horizontal_scene(Blackboard &blackboard, Interactable &walkable, Sprite &sprite,
                                                    Panda &panda) {
    float frameRate = 8.f;
    int frames, row;
    int index = 0;
    /*
     * Walking
     */
    if (walkable.grounded) {
        frames = 8;
        if (blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT)) {
            frameRate = 10.f;
        } else if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)) {
            frameRate = 6.f;
        }
    }
    /*
     * Jumping
     */
    if (!walkable.grounded) {
        frames = 2;
        index = 8;
        if (blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT)) {
            frameRate = 3.f;
        } else if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)) {
            frameRate = 1.f;
        } else {
            frameRate = 2.f;
        }
    }

    if (panda.alive){
        row = 1;
        animate(true, frames, index, row, sprite);
//        printf("%d, \n", death_index);
    } else {
        int mod = ((int) animationTime % 4);
        printf("%f, \n", animationTime);
        if (death_index < frames && mod == 0) {
            frames = 10;
            frameRate = 1.f;
            row = 2;
//            printf("%d, \n", death_index);
            animate(false, frames, death_index, row, sprite);
        }
    }

    animationTime += frameRate*blackboard.delta_time;

}

void PlayerAnimationSystem::update_vertical_boss_scene(Blackboard &blackboard, Interactable &walkable, Sprite &sprite,
                                                       Panda &panda, Transform &transform) {
    float frameRate = 8.f;
    int frames, index, row;
    bool idle = true;
    index = 0;

    if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)) {
        direction_left = true;
        transform.x_scale = -abs(transform.x_scale);
        idle = false;
    } else if (blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT)) {
        direction_left = false;
        transform.x_scale = abs(transform.x_scale);
        idle = false;
    }
    /*
     * Walking
     */

    if (walkable.grounded) {
        frames = 8;
        if (!idle) {
            row = 1;
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
        row = 1;
    }

    if (panda.alive){
        animate(true, frames, index, row, sprite);
    } else {
        frames = 10;
        if (death_index < frames) {
            row = 2;
            frameRate = 1.f;
            animate(false, frames, death_index, row, sprite);
        }
    }
    animationTime += frameRate * blackboard.delta_time;

}

void PlayerAnimationSystem::animate(bool alive, int frames, int index, int row, Sprite &sprite) {
    if (alive) {
        index += ((int) animationTime % frames);
        death_index = 0;
    } else{
        death_index++;
    }
    vec2 uv1 = {index * pandawidth - 0.004f, pandaheight * row + 0.03f};
    vec2 uv2 = {(index + 1) * pandawidth - 0.008f, pandaheight * (1 + row) - 0.09f};
    sprite.set_uvs(uv1, uv2);
}
