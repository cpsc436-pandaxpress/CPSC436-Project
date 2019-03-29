//
// Created by Prayansh Srivastava on 2019-02-12.
//

#ifndef PANDAEXPRESS_BOSS_SCENE_H
#define PANDAEXPRESS_BOSS_SCENE_H


#include "scene.h"
#include <queue>
#include <systems/boss_level_system.h>
#include <systems/background_render_system.h>
#include <systems/a_star_system.h>
#include <systems/background_transform_system.h>
#include <systems/panda_damage_system.h>
#include <systems/timer_system.h>
#include <systems/health_bar_render_system.h>
#include <systems/health_bar_transform_system.h>
#include "scene.h"
#include "scene_manager.h"
#include "../systems/sprite_render_system.h"
#include "../systems/sprite_transform_system.h"
#include "../util/blackboard.h"
#include "../util/coordinates.h"
#include "../systems/physics_system.h"
#include "../systems/player_movement_system.h"
#include "../systems/timer_system.h"
#include "../systems/jacko_ai_system.h"
#include "../systems/falling_platform_system.h"
#include "../systems/chase_system.h"
#include "../systems/seek_system.h"
#include "../systems/player_animation_system.h"
#include "../systems/enemy_animation_system.h"

class BossScene: public Scene {
private:
    const float CAMERA_START_X = 0.f;
    const float CAMERA_START_Y = 0.f;
    const float CAMERA_SPEED = 150.f;
    const float PANDA_START_X = -10.f;
    const float PANDA_START_Y = -200.f;
    const float MAX_CAMERA_Y_DIFF = 200.f;

    std::vector<uint32_t> bg_entities;
    uint32_t panda_entity;
    uint32_t jacko_entity;
    uint32_t burger_entity;
    uint32_t bat_entity;
    uint32_t tutorial_entity;
    uint32_t tutorial2_entity;
    BossLevelSystem level_system;
    SpriteTransformSystem sprite_transform_system;
    SpriteRenderSystem sprite_render_system;
    BackgroundRenderSystem background_render_system;
    BackgroundTransformSystem background_transform_system;
    PhysicsSystem physics_system;
    PlayerMovementSystem player_movement_system;
    ChaseSystem chase_system;
    JackoAISystem jacko_ai_system;
    PlayerAnimationSystem player_animation_system;
    TimerSystem timer_system;
    FallingPlatformSystem falling_platform_system;
    AStarSystem a_star_system;
    SeekSystem seek_system;
    PandaDamageSystem panda_dmg_system;
    EnemyAnimationSystem enemy_animation_system;
    HealthBarRenderSystem health_bar_render_system;
    HealthBarTransformSystem health_bar_transform_system;


    void create_background(Blackboard &blackboard);
    void create_panda(Blackboard& blackboard);
    void create_jacko(Blackboard& blackboard, uint32_t panda);
    void create_tutorial(Blackboard& blackboard);
    void reset_scene(Blackboard& blackboard);
    void init_scene(Blackboard &blackboard);
    void update_panda(Blackboard& blackboard);
    void update_tutorial(Blackboard& blackboard);
    void update_camera(Blackboard& blackboard);

public:
    BossScene(Blackboard &blackboard,
                    SceneManager &scene_manager);

    virtual void update(Blackboard& blackboard) override;
    void create_food(Blackboard &blackboard);
    virtual void render(Blackboard& blackboard) override;

};


#endif //PANDAEXPRESS_BOSS_SCENE_H

