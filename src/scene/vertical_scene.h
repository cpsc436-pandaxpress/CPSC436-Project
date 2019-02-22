//
// Created by cowan on 14/02/19.
//

#ifndef PANDAEXPRESS_VERTICAL_SCENE_H
#define PANDAEXPRESS_VERTICAL_SCENE_H

#include <systems/sprite_render_system.h>
#include <systems/physics_system.h>
#include <systems/sprite_transform_system.h>
#include "scene.h"
#include <queue>
#include <systems/player_movement_system.h>
#include <systems/collision_system.h>
#include <systems/vertical_level_system.h>

class VerticalScene : public Scene {
private:

    uint32_t panda_entity;
    SpriteTransformSystem sprite_transform_system;
    SpriteRenderSystem sprite_render_system;
    PhysicsSystem physics_system;
    PlayerMovementSystem player_movement_system;
    CollisionSystem collision_system;
    VerticalLevelSystem level_system;

    const float CAMERA_START_X = 0.f;
    const float CAMERA_START_Y = 0.f;
    const float CAMERA_SPEED = 350.f;
    const float PANDA_START_X = -10.f;
    const float PANDA_START_Y = -200.f;
    const float PLATFORM_START_X = -0.f;
    const float PLATFORM_START_Y = 400.f;

    void create_panda(Blackboard& blackboard);
    void reset_scene(Blackboard& blackboard);
    void init_scene(Blackboard &blackboard);

public:
    VerticalScene(Blackboard& blackboard, SceneManager& scene_manager);

    virtual void update(Blackboard& blackboard) override;

    virtual void render(Blackboard& blackboard) override;
};

#endif //PANDAEXPRESS_VERTICAL_SCENE_H