//
// Created by Prayansh Srivastava on 2019-02-12.
//

#ifndef PANDAEXPRESS_TEST_SCENE_2_H
#define PANDAEXPRESS_TEST_SCENE_2_H

#include "scene.h"
#include <queue>
#include <level/horizontal_level_system.h>
#include <systems/background_render_system.h>
#include <systems/background_transform_system.h>
#include <systems/timer_system.h>
#include <systems/falling_platform_system.h>
#include <systems/panda_damage_system.h>
#include <systems/health_bar_render_system.h>
#include <systems/health_bar_transform_system.h>
#include <systems/text_render_system.h>
#include <systems/text_transform_system.h>
#include <systems/score_system.h>
#include <systems/fade_overlay_system.h>
#include <systems/fade_overlay_render_system.h>
#include <systems/pause_menu_transform_system.h>
#include <systems/pause_menu_render_system.h>
#include <systems/hud_transform_system.h>
#include <systems/label_system.h>
#include "scene.h"
#include "scene_manager.h"
#include "../systems/sprite_render_system.h"
#include "../systems/cave_render_system.h"
#include "../systems/sprite_transform_system.h"
#include "../util/blackboard.h"
#include "../systems/physics_system.h"
#include "../systems/player_movement_system.h"
#include "../systems/enemy_system.h"
#include "../systems/transition_system.h"
#include "../systems/player_animation_system.h"
#include "../systems/enemy_animation_system.h"

class HorizontalScene: public Scene {
private:
    const float CAMERA_START_X = 0.f;
    const float CAMERA_START_Y = 0.f;
    const float PANDA_START_X = -10.f;
    const float PANDA_START_Y = -200.f;
    const float MAX_CAMERA_Y_DIFF = 250.f;
    const float HUD_Y_OFFSET = 50.f;
    const float HUD_SCORE_X_OFFSET = 350.f;
    const float HUD_HEALTH_X_OFFSET = 100.f;
    const float HEALTH_BAR_X_SIZE = 750.f;
    const float HEALTH_BAR_Y_SIZE = 75.f;
    bool pause = false;

    std::vector<uint32_t> bg_entities;
    uint32_t panda_entity;
    uint32_t score_entity;
    uint32_t fade_overlay_entity;
    uint32_t pause_menu_entity;
    HorizontalLevelSystem level_system;
    SpriteTransformSystem sprite_transform_system;
    SpriteRenderSystem sprite_render_system;
    BackgroundRenderSystem background_render_system;
    BackgroundTransformSystem background_transform_system;
    PhysicsSystem physics_system;
    PlayerMovementSystem player_movement_system;
    EnemySystem enemy_system;
    PlayerAnimationSystem player_animation_system;
    EnemyAnimationSystem enemy_animation_system;
    TimerSystem timer_system;
    FallingPlatformSystem falling_platform_system;
    PandaDamageSystem panda_dmg_system;
    HealthBarRenderSystem health_bar_render_system;
    CaveRenderSystem cave_render_system;
    HealthBarTransformSystem health_bar_transform_system;
    TextRenderSystem text_render_system;
    TextTransformSystem text_transform_system;
    ScoreSystem score_system;
    TransitionSystem transition_system;
    FadeOverlaySystem fade_overlay_system;
    FadeOverlayRenderSystem fade_overlay_render_system;
    PauseMenuTransformSystem pause_menu_transform_system;
    PauseMenuRenderSystem pause_menu_render_system;
    HudTransformSystem hud_transform_system;
    LabelSystem label_system;

    uint32_t high_score_entity;
    int high_score_;

    void create_background(Blackboard &blackboard);
    void create_panda(Blackboard& blackboard);
    void create_pause_menu(Blackboard& blackboard);
    void reset_scene(Blackboard& blackboard);
    void init_scene(Blackboard &blackboard);
    void update_panda(Blackboard& blackboard);
    void update_camera(Blackboard& blackboard);
    void create_score_text(Blackboard &blackboard);
    void create_fade_overlay(Blackboard &blackboard);
public:
    HorizontalScene(Blackboard &blackboard,
                    SceneManager &scene_manager);

    virtual void update(Blackboard& blackboard) override;

    virtual void render(Blackboard& blackboard) override;

    void set_mode(SceneMode mode) override;

    void set_high_score(int value);
    int get_high_score();

    static constexpr float CAMERA_SPEED = 400.f;

    void go_to_next_scene(Blackboard &blackboard);
};


#endif //PANDAEXPRESS_TEST_SCENE_2_H

