//
// Created by alex on 29/01/19.
//

#pragma once

#include "scene.h"
#include "scene_manager.h"
#include "../systems/sprite_render_system.h"
#include "../systems/sprite_transform_system.h"
#include "../util/blackboard.h"

class TestScene : public Scene {
private:
    uint32_t test_entity;
    SpriteTransformSystem sprite_transform_system;
    SpriteRenderSystem sprite_render_system;
public:
    TestScene(Blackboard& blackboard, SceneManager& scene_manager);

    virtual void update(Blackboard& blackboard) override;

    virtual void render(Blackboard& blackboard) override;
};