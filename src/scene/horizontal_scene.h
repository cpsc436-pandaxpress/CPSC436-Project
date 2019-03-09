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
#include <systems/timer_system.h>
#include <systems/falling_platform_system.h>
#include <systems/panda_damage_system.h>
#include <systems/health_bar_render_system.h>
#include <systems/health_bar_transform_system.h>
#include "scene.h"
#include "scene_manager.h"
#include "../systems/sprite_render_system.h"
#include "../systems/sprite_transform_system.h"
#include "../util/blackboard.h"
#include "../systems/physics_system.h"
#include "../systems/player_movement_system.h"
#include "../systems/collision_system.h"
#include "../systems/enemy_system.h"
#include "../systems/player_animation_system.h"
#include "../systems/enemy_animation_system.h"



class HorizontalScene: public Scene {
private:
    const float CAMERA_START_X = 0.f;
    const float CAMERA_START_Y = 0.f;
    const float PANDA_START_X = -10.f;
    const float PANDA_START_Y = -200.f;
    const float MAX_CAMERA_Y_DIFF = 250.f;

    std::vector<uint32_t> bg_entities;
    uint32_t panda_entity;
    uint32_t tutorial_entity;
    uint32_t tutorial2_entity;
    uint32_t health_entity;
    HorizontalLevelSystem level_system;
    SpriteTransformSystem sprite_transform_system;
    SpriteRenderSystem sprite_render_system;
    BackgroundRenderSystem background_render_system;
    BackgroundTransformSystem background_transform_system;
    PhysicsSystem physics_system;
    PlayerMovementSystem player_movement_system;
    CollisionSystem collision_system;
    EnemySystem enemy_system;
    PlayerAnimationSystem player_animation_system;
    EnemyAnimationSystem enemy_animation_system;
    TimerSystem timer_system;
    FallingPlatformSystem falling_platform_system;
    PandaDamageSystem panda_dmg_system;
    HealthBarRenderSystem health_bar_render_system;
    HealthBarTransformSystem health_bar_transform_system;

    void create_background(Blackboard &blackboard);
    void create_panda(Blackboard& blackboard);
    void create_tutorial(Blackboard& blackboard);
    void reset_scene(Blackboard& blackboard);
    void init_scene(Blackboard &blackboard);
    void update_panda(Blackboard& blackboard);
    void update_tutorial(Blackboard& blackboard);
    void update_camera(Blackboard& blackboard);

public:
    HorizontalScene(Blackboard &blackboard,
                    SceneManager &scene_manager);

    virtual void update(Blackboard& blackboard) override;

    virtual void render(Blackboard& blackboard) override;

    static constexpr float CAMERA_SPEED = 400.f;
};


#endif //PANDAEXPRESS_TEST_SCENE_2_H

