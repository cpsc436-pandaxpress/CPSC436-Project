//
// Created by alex on 29/01/19.
//

#include <components/bread.h>
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
    create_bread(blackboard);
}

void TestScene::update(Blackboard &blackboard) {
    vec2 cam_size = blackboard.camera.size();
    vec2 cam_position = blackboard.camera.position();
    blackboard.camera.set_position(cam_position.x + CAMERA_SPEED * blackboard.delta_time, cam_position.y);
    blackboard.camera.compose();
    generate_platforms(blackboard);

    auto &transform = registry_.get<Transform>(panda_entity);
    auto &panda = registry_.get<Panda>(panda_entity);
    auto &enemy = registry_.get<Bread>(enemy_entity);
    auto &transform_enemy = registry_.get<Transform>(enemy_entity);

    if (transform.x + panda.width < cam_position.x - cam_size.x / 2 ||
        transform.y - panda.height > cam_position.y + cam_size.y / 2 || !panda.alive) {
        reset_scene(blackboard);
    } else if (transform.x + panda.width / 2 > cam_position.x + cam_size.x / 2) {
        transform.x = cam_position.x + cam_size.x / 2 - panda.width / 2;
    }


    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_LEFT)) {
        panda.x_velocity = -PANDA_SPEED;
    } else if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_RIGHT)) {
        panda.x_velocity = PANDA_SPEED;
    } else if (blackboard.input_manager.key_just_released(SDL_SCANCODE_LEFT) ||
               blackboard.input_manager.key_just_released(SDL_SCANCODE_RIGHT)) {
        panda.x_velocity = 0;
    }

    if (panda.grounded && blackboard.input_manager.key_just_pressed(SDL_SCANCODE_SPACE)) {
        transform.y -= 5;
        panda.y_velocity = -PANDA_JUMP_SPEED;
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

    float scale = 0.15f;
    registry_.assign<Transform>(panda_entity, PANDA_START_X, PANDA_START_Y, 0., scale, scale);
    registry_.assign<Sprite>(panda_entity, texture, shader);
    registry_.assign<Panda>(panda_entity, texture.width() * scale, texture.height() * scale);

}

void TestScene::generate_platforms(Blackboard &blackboard) {
    auto shader = blackboard.shader_manager.get_shader("sprite");
    float max_x =
            blackboard.camera.position().x + blackboard.camera.size().x; // some distance off camera
    while (last_placed_x < max_x) {
        auto texture = blackboard.textureManager.get_texture(
                (rand() % 2 == 0) ? "platform1" : "platform2");
        float scale = 50.0f / texture.width();
        if (platforms.size() > MAX_PLATFORMS) {//reuse
            auto platform = platforms.front();
            platforms.pop();
            registry_.replace<Transform>(platform, last_placed_x, PLATFORM_START_Y, 0.f, scale,
                                         scale);
            platforms.push(platform);
        } else {
            auto platform = registry_.create();
            registry_.assign<Transform>(platform, last_placed_x, PLATFORM_START_Y, 0., scale,
                                        scale);
            registry_.assign<Sprite>(platform, texture, shader);
            registry_.assign<Platform>(platform, texture.width() * scale, texture.height() * scale);

            platforms.push(platform);
        }
        last_placed_x += texture.width();
    }
}

void TestScene::create_bread(Blackboard &blackboard) {
    enemy_entity = registry_.create();
    auto texture = blackboard.textureManager.get_texture("bread");
    auto shader = blackboard.shader_manager.get_shader("sprite");

    float scale = 0.5;
    registry_.assign<Transform>(enemy_entity, 350., PLATFORM_START_Y - texture.height(), 0.,
                                scale, scale);
    registry_.assign<Sprite>(enemy_entity, texture, shader);
    registry_.assign<Bread>(enemy_entity, texture.width() * scale, texture.height() * scale);

}

void TestScene::reset_scene(Blackboard &blackboard) {
    registry_.destroy(panda_entity);
    registry_.destroy(enemy_entity);
    while (!platforms.empty()) {
        uint32_t platform = platforms.front();
        registry_.destroy(platform);
        platforms.pop();
    }
    initScene(blackboard);
}