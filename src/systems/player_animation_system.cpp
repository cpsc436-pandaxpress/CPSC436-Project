
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

    if (panda.alive || !walkable.grounded) {
        row = 1;
        animate(true, frames, index, row, sprite);
    } else if (!panda.alive && walkable.grounded){
        frames = 10;
        frameRate = 15.f;
        if (death_index < frames && (counter != (int) animationTime)) {
            row = 2;
            animate(false, frames, death_index, row, sprite);
        }
    }
    counter = (int) animationTime;
    animationTime += frameRate * blackboard.delta_time;

}

void PlayerAnimationSystem::update_vertical_boss_scene(Blackboard &blackboard, Interactable &walkable, Sprite &sprite,
                                                       Panda &panda, Transform &transform) {
    float frameRate = 8.f;
    int frames, index, row;
    bool idle = true;
    index = 0;

    if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)) {
        transform.x_scale = -abs(transform.x_scale);
        idle = false;
    } else if (blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT)) {
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

    if (panda.alive) {
        animate(true, frames, index, row, sprite);
    } else if (!panda.alive && walkable.grounded){
        frames = 10;
        frameRate = 15.f;
        if (death_index < frames && (counter != (int) animationTime)) {
            row = 2;
            animate(false, frames, death_index, row, sprite);
        }
    }
    counter = (int) animationTime;
    animationTime += frameRate * blackboard.delta_time;

}

void PlayerAnimationSystem::animate(bool alive, int frames, int index, int row, Sprite &sprite) {
    float w1, w2, h1, h2;
    w1 = 0.0095f;
    w2 = -0.007f;
    h1 = 0.01f;
    h2 = 0.12f;
    if (alive) {
        index += ((int) animationTime % frames);
        death_index = 0;
    } else if (!alive) {
        death_index++;
    }
    vec2 uv1 = {index * pandawidth + w1, pandaheight * row + h1};
    vec2 uv2 = {(index + 1) * pandawidth + w2, pandaheight * (1 + row) - h2};
    sprite.set_uvs(uv1, uv2);
}
