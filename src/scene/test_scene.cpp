//
// Created by alex on 29/01/19.
//

#include <components/panda.h>
#include <components/platform.h>
#include "test_scene.h"

#include "components/transform.h"

void create_panda();
void create_platforms();

TestScene::TestScene(Blackboard& blackboard, SceneManager& scene_manager) :
    Scene(scene_manager),
    sprite_render_system(),
    sprite_transform_system(),
    physics_system()
{
    create_panda(blackboard);
    create_platforms(blackboard);
}

void TestScene::update(Blackboard& blackboard) {
    // some sample input handling
    auto& transform = registry_.get<Transform>(panda_entity);
    auto& panda = registry_.get<Panda>(panda_entity);

    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_LEFT)) {
        panda.x_velocity = -5;
    } else if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_RIGHT)) {
        panda.x_velocity = 5;
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

void TestScene::render(Blackboard& blackboard) {
    // update the rendering systems
    sprite_render_system.update(blackboard, registry_);

}

void TestScene::create_panda(Blackboard& blackboard) {
    panda_entity = registry_.create();

    auto texture = blackboard.textureManager.get_texture("panda");
    auto shader = blackboard.shader_manager.get_shader("sprite");

    float scale = 0.5;
    registry_.assign<Transform>(panda_entity, 0., 0., 0., scale, scale);
    registry_.assign<Sprite>(panda_entity, texture, shader);
    registry_.assign<Panda>(panda_entity, texture.width() * scale, texture.height() * scale);

}

void TestScene::create_platforms(Blackboard& blackboard) {
    auto texture = blackboard.textureManager.get_texture("platform");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    float scale = 100.f / texture.width();

    for (int i = 0; i < 5; i++) {
        auto platform = registry_.create();

        registry_.assign<Transform>(platform, 200 * i - 200., 200., 0., scale, scale);
        registry_.assign<Sprite>(platform, texture, shader);
        registry_.assign<Platform>(platform, texture.width() * scale, texture.height() * scale);

        platforms.push_back(platform);
    }
}