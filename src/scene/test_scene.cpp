//
// Created by alex on 29/01/19.
//

#include <components/physics.h>
#include "test_scene.h"

#include "components/transform.h"

TestScene::TestScene(Blackboard& blackboard, SceneManager& scene_manager) :
    Scene(scene_manager),
    sprite_render_system(),
    sprite_transform_system(),
    physics_system()
{
    test_entity = registry_.create();

    auto texture = blackboard.textureManager.get_texture("panda");
    auto shader = blackboard.shader_manager.get_shader("sprite");

    registry_.assign<Transform>(test_entity, 0., 0., 0., 0.5, 0.5);
    registry_.assign<Sprite>(test_entity, texture, shader);
    registry_.assign<Physics>(test_entity, true);

    auto platform_texture = blackboard.textureManager.get_texture("platform");
    float scale = 100.f / platform_texture.width();

    for (int i = 0; i < 5; i++) {
        auto platform = registry_.create();

        registry_.assign<Transform>(platform, 200 * i - 200., 200., 0., scale, scale);
        registry_.assign<Sprite>(platform, platform_texture, shader);

        platforms.push_back(platform);
    }
}

void TestScene::update(Blackboard& blackboard) {
    // some sample input handling
    auto& position = registry_.get<Transform>(test_entity);

    if (blackboard.input_manager.key_pressed(SDL_SCANCODE_UP)) {
        position.y -= 1;
    }
    if (blackboard.input_manager.key_pressed(SDL_SCANCODE_DOWN)) {
        position.y += 1;
    }
    if (blackboard.input_manager.key_pressed(SDL_SCANCODE_LEFT)) {
        position.x -= 1;
    }
    if (blackboard.input_manager.key_pressed(SDL_SCANCODE_RIGHT)) {
        position.x += 1;
    }

    // update the systems here
    physics_system.update(blackboard, registry_);

    sprite_transform_system.update(blackboard, registry_);
}

void TestScene::render(Blackboard& blackboard) {
    // update the rendering systems
    sprite_render_system.update(blackboard, registry_);

}