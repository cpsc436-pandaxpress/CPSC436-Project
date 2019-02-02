//
// Created by alex on 29/01/19.
//

#include <components/panda.h>
#include <components/platform.h>
#include "test_scene.h"
#include <random>
#include "components/transform.h"

TestScene::TestScene(Blackboard &blackboard, SceneManager &scene_manager) :
        Scene(scene_manager),
        sprite_render_system(),
        sprite_transform_system(),
        physics_system() {
    initScene(blackboard);
}
void TestScene::initScene(Blackboard &blackboard) {
    srand(0);
    blackboard.camera.set_position(CAMERA_START_X, CAMERA_START_Y);
    blackboard.camera.compose();
    last_placed_x = PLATFORM_START_X;
    create_panda(blackboard);
}

void TestScene::update(Blackboard &blackboard) {
    vec2 cam_size = blackboard.camera.size();
    vec2 cam_position = blackboard.camera.position();
    generate_platforms(blackboard);
    blackboard.camera.set_position(cam_position.x + 0.4f, cam_position.y);
    blackboard.camera.compose();

    auto &transform = registry_.get<Transform>(panda_entity);
    auto &panda = registry_.get<Panda>(panda_entity);

    if (transform.x + panda.width / 2 < cam_position.x - cam_size.x / 2
        || transform.y + panda.height / 2 > cam_position.y + cam_size.y) {
        reset_scene(blackboard);
    }


    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_LEFT)) {
        panda.x_velocity = -1;
    } else if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_RIGHT)) {
        panda.x_velocity = 1;
    } else if (blackboard.input_manager.key_just_released(SDL_SCANCODE_LEFT) ||
               blackboard.input_manager.key_just_released(SDL_SCANCODE_RIGHT)) {
        panda.x_velocity = 0;
    }

    if (panda.grounded && blackboard.input_manager.key_just_pressed(SDL_SCANCODE_SPACE)) {
        transform.y -= 5;
        panda.y_velocity = -5;
        panda.grounded = false;
    }

    // update the systems here
    physics_system.update(blackboard, registry_);

    sprite_transform_system.update(blackboard, registry_);
}

void TestScene::render(Blackboard &blackboard) {
    // update the rendering systems
    sprite_render_system.update(blackboard, registry_);

}

void TestScene::create_panda(Blackboard &blackboard) {
    panda_entity = registry_.create();

    auto texture = blackboard.textureManager.get_texture("panda");
    auto shader = blackboard.shader_manager.get_shader("sprite");

    float scale = 0.5;
    registry_.assign<Transform>(panda_entity, PANDA_START_X, PANDA_START_Y, 0., scale, scale);
    registry_.assign<Sprite>(panda_entity, texture, shader);
    registry_.assign<Panda>(panda_entity, texture.width() * scale, texture.height() * scale);

}

void TestScene::generate_platforms(Blackboard &blackboard) {
    auto texture = blackboard.textureManager.get_texture("platform");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    float scale = 50.0f / texture.width();
    float max_x = blackboard.camera.position().x + blackboard.camera.size().x; // some distance off camera
    while (last_placed_x < max_x) {
//        if (rand() % 100 > 75) {
//            last_placed_x += texture.width();
//            continue;
//        }
        auto platform = registry_.create();
        registry_.assign<Transform>(platform, last_placed_x, PLATFORM_START_Y, 0., scale,
                                    scale);
        last_placed_x += texture.width();
        registry_.assign<Sprite>(platform, texture, shader);
        registry_.assign<Platform>(platform, texture.width() * scale, texture.height() * scale);

        platforms.push(platform);
    }
    while (platforms.size() > 30) {
        uint32_t platform = platforms.front();
        registry_.destroy(platform);
        platforms.pop();
    }
    const auto firstP = registry_.get<Transform>(platforms.front());
    printf("lastPlaced: %f, #platforms:%lu, firstPlatformX:%f\n", last_placed_x, platforms.size(), firstP.x);
}

void TestScene::reset_scene(Blackboard &blackboard) {
    registry_.destroy(panda_entity);
    while (!platforms.empty()) {
        uint32_t platform = platforms.front();
        registry_.destroy(platform);
        platforms.pop();
    }
    initScene(blackboard);
}