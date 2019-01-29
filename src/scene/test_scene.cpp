//
// Created by alex on 29/01/19.
//

#include "test_scene.h"

#include "../components/position.h"

TestScene::TestScene(Blackboard& blackboard, SceneManager& scene_manager) :
    Scene(scene_manager),
    sprite_render_system(),
    sprite_transform_system()
{
    auto test_entity = registry_.create();

    auto texture = blackboard.textureManager.get_texture("panda");
    auto shader = blackboard.shader_manager.get_shader("sprite");

    registry_.assign<Position>(test_entity, 0., 0., 0.);
    registry_.assign<Sprite>(test_entity, texture, shader);
}

void TestScene::update(Blackboard& blackboard) {
    // update the systems
    sprite_transform_system.update(blackboard, registry_);
}

void TestScene::render(Blackboard& blackboard) {
    // update the rendering systems
    sprite_render_system.update(blackboard, registry_);

}