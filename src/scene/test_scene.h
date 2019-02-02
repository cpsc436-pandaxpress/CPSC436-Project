//
// Created by alex on 29/01/19.
//

#pragma once

#include "scene.h"
#include "scene_manager.h"
#include "../systems/sprite_render_system.h"
#include "../systems/sprite_transform_system.h"
#include "../util/blackboard.h"
#include "../systems/physics_system.h"

class TestScene : public Scene {
private:
    uint32_t panda_entity, enemy_entity;
    SpriteTransformSystem sprite_transform_system;
    SpriteRenderSystem sprite_render_system;
    std::vector<uint32_t> platforms;
    PhysicsSystem physics_system;

    const float CAMERA_START_X = 0.f;
    const float CAMERA_START_Y = 0.f;
    const float CAMERA_SPEED = 150.f;
    const float PANDA_START_X = 0.f;
    const float PANDA_START_Y = 0.f;
    const float PANDA_SPEED = 200.f;
    const float PANDA_JUMP_SPEED = 200.f;
    const float PLATFORM_START_X = -200.f;
    const float PLATFORM_START_Y = 200.f;

    void create_panda(Blackboard& blackboard);
    void create_bread(Blackboard& blackboard);
    void create_platforms(Blackboard& blackboard);
    void reset_scene(Blackboard& blackboard);

public:
    TestScene(Blackboard& blackboard, SceneManager& scene_manager);

    virtual void update(Blackboard& blackboard) override;

    virtual void render(Blackboard& blackboard) override;
};