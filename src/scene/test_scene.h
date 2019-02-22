//
// Created by alex on 29/01/19.
//

#pragma once

#include <queue>
#include <systems/background_render_system.h>
#include <systems/background_transform_system.h>
#include "scene.h"
#include "scene_manager.h"
#include "../systems/sprite_render_system.h"
#include "../systems/sprite_transform_system.h"
#include "../util/blackboard.h"
#include "../systems/physics_system.h"
#include "../systems/player_movement_system.h"
#include "../systems/collision_system.h"

class TestScene : public Scene {
private:

    std::queue<uint32_t> obstacles;
    uint32_t panda_entity;
    std::vector<uint32_t> bg_entities;
    std::queue<uint32_t> platforms;// platforms are in order of x
    std::queue<uint32_t> floating_platforms;
    std::queue<uint32_t> enemies;
    SpriteTransformSystem sprite_transform_system;
    SpriteRenderSystem sprite_render_system;
    PhysicsSystem physics_system;
    PlayerMovementSystem player_movement_system;
    CollisionSystem collision_system;
    BackgroundRenderSystem background_render_system;
    BackgroundTransformSystem background_transform_system;

    float last_placed_x;

    float last_rock_x;
    float last_placed_x_floating;
    float last_bread_x;

    const float CAMERA_START_X = 0.f;
    const float CAMERA_START_Y = 0.f;
    const float CAMERA_SPEED = 150.f;
    const float PANDA_START_X = -10.f;
    const float PANDA_START_Y = -200.f;
    const float PLATFORM_START_X = -200.f;
    const float PLATFORM_START_Y = 400.f;
    const float FLOATING_PLATFORM_START_Y = 100.f;
    const float BREAD_START_X = 700.f;
    const float BREAD_START_Y = -600.f;
    const float BREAD_SPEED = 75.f;
    const int MAX_PLATFORMS = 30;
    const float MAX_CAMERA_Y_DIFF = 200.f;


    void create_panda(Blackboard& blackboard);
    void create_bread(Blackboard& blackboard);
    void generate_obstacles(Blackboard& blackboard);
    void clean_bread(Blackboard& blackboard);
    void generate_platforms(Blackboard &blackboard);
    void reset_scene(Blackboard& blackboard);
    void init_scene(Blackboard &blackboard);
    void generate_floating_platforms(Blackboard &blackboard);
    void update_camera(Blackboard& blackboard);
    void update_panda(Blackboard& blackboard);

public:
    TestScene(Blackboard& blackboard, SceneManager& scene_manager);

    virtual void update(Blackboard& blackboard) override;

    virtual void render(Blackboard& blackboard) override;

    void create_background(Blackboard &blackboard);
};