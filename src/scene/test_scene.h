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
#include "../systems/player_movement_system.h"

class TestScene : public Scene {
private:
    uint32_t panda_entity;
    SpriteTransformSystem sprite_transform_system;
    SpriteRenderSystem sprite_render_system;
    std::vector<uint32_t> platforms;
    PhysicsSystem physics_system;
    playerMovementSystem player_movement_system;
    void create_panda(Blackboard& blackboard);
    void create_platforms(Blackboard& blackboard);

public:
    TestScene(Blackboard& blackboard, SceneManager& scene_manager);

    virtual void update(Blackboard& blackboard) override;

    virtual void render(Blackboard& blackboard) override;
};