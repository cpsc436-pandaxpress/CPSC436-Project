//
// Created by Prayansh Srivastava on 2019-02-12.
//

#ifndef PANDAEXPRESS_TEST_SCENE_2_H
#define PANDAEXPRESS_TEST_SCENE_2_H


#include "scene.h"
#include <queue>
#include <systems/horizontal_level_system.h>
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

class HorizontalScene: public Scene {
private:
    const float CAMERA_START_X = 0.f;
    const float CAMERA_START_Y = 0.f;
    const float CAMERA_SPEED = 150.f;
    const float PANDA_START_X = -10.f;
    const float PANDA_START_Y = -200.f;
    const float MAX_CAMERA_Y_DIFF = 200.f;

    uint32_t bg_entity;
    uint32_t panda_entity;
    HorizontalLevelSystem level_system;
    SpriteTransformSystem sprite_transform_system;
    SpriteRenderSystem sprite_render_system;
    BackgroundRenderSystem background_render_system;
    BackgroundTransformSystem background_transform_system;
    PhysicsSystem physics_system;
    PlayerMovementSystem player_movement_system;
    CollisionSystem collision_system;

    void create_background(Blackboard &blackboard);
    void create_panda(Blackboard& blackboard);
    void reset_scene(Blackboard& blackboard);
    void init_scene(Blackboard &blackboard);
    void update_panda(Blackboard& blackboard);
    void update_camera(Blackboard& blackboard);

public:
    HorizontalScene(Blackboard &blackboard,
                   SceneManager &scene_manager);

    virtual void update(Blackboard& blackboard) override;

    virtual void render(Blackboard& blackboard) override;

};


#endif //PANDAEXPRESS_TEST_SCENE_2_H
