//
// Created by alex on 29/01/19.
//

#include <components/bread.h>
#include <components/panda.h>
#include <components/platform.h>
#include "test_scene.h"

#include "components/transform.h"

TestScene::TestScene(Blackboard& blackboard, SceneManager& scene_manager) :
    Scene(scene_manager),
    sprite_render_system(),
    sprite_transform_system(),
    physics_system()
{
    blackboard.camera.set_position(CAMERA_START_X, CAMERA_START_Y);
    blackboard.camera.compose();

    create_panda(blackboard);
    create_bread(blackboard);
    create_platforms(blackboard);
}

void TestScene::update(Blackboard& blackboard) {
    vec2 cam_size = blackboard.camera.size();
    vec2 cam_position = blackboard.camera.position();
    blackboard.camera.set_position(cam_position.x + CAMERA_SPEED * blackboard.delta_time, cam_position.y);
    blackboard.camera.compose();

    auto& transform = registry_.get<Transform>(panda_entity);
    auto& panda = registry_.get<Panda>(panda_entity);
    auto& enemy = registry_.get<Bread>(enemy_entity);
    auto& transform_enemy = registry_.get<Transform>(enemy_entity);

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

void TestScene::render(Blackboard& blackboard) {
    // update the rendering systems
    sprite_render_system.update(blackboard, registry_);

}

void TestScene::create_panda(Blackboard& blackboard) {
    panda_entity = registry_.create();

    auto texture = blackboard.textureManager.get_texture("panda");
    auto shader = blackboard.shader_manager.get_shader("sprite");

    float scale = 0.5;
    registry_.assign<Transform>(panda_entity, PANDA_START_X, PANDA_START_Y, 0., scale, scale);
    registry_.assign<Sprite>(panda_entity, texture, shader);
    registry_.assign<Panda>(panda_entity, texture.width() * scale, texture.height() * scale);

}

void TestScene::create_platforms(Blackboard& blackboard) {
    auto texture = blackboard.textureManager.get_texture("platform");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    float scale = 100.f / texture.width();

    for (int i = 0; i < 5; i++) {
        auto platform = registry_.create();

        registry_.assign<Transform>(platform, 200 * i + PLATFORM_START_X, PLATFORM_START_Y, 0., scale, scale);
        registry_.assign<Sprite>(platform, texture, shader);
        registry_.assign<Platform>(platform, texture.width() * scale, texture.height() * scale);

        platforms.push_back(platform);
    }
}

void TestScene::create_bread(Blackboard& blackboard) {
    enemy_entity = registry_.create();
    auto texture = blackboard.textureManager.get_texture("bread");
    auto shader = blackboard.shader_manager.get_shader("sprite");

    float scale = 0.3;
    registry_.assign<Transform>(enemy_entity, 350., 140., 0., scale, scale);
    registry_.assign<Sprite>(enemy_entity, texture, shader);
    registry_.assign<Bread>(enemy_entity, texture.width() * scale, texture.height() * scale);

}

void TestScene::reset_scene(Blackboard& blackboard) {
    blackboard.camera.set_position(CAMERA_START_X, CAMERA_START_Y);
    blackboard.camera.compose();

    registry_.destroy(panda_entity);
    registry_.destroy(enemy_entity);
    for (uint32_t &platform : platforms) {
        registry_.destroy(platform);
    }
    platforms.clear();

    create_panda(blackboard);
    create_bread(blackboard);
    create_platforms(blackboard);
}