//
// Created by cowan on 14/02/19.
//

#ifndef PANDAEXPRESS_VERTICAL_SCENE_H
#define PANDAEXPRESS_VERTICAL_SCENE_H

#include <systems/physics_system.h>
#include <systems/sprite_transform_system.h>
#include "game_scene.h"
#include <queue>
#include <systems/player_movement_system.h>
#include <systems/player_animation_system.h>
#include <systems/falling_platform_system.h>
#include <level/vertical_level_system.h>
#include <systems/timer_system.h>
#include <systems/panda_damage_system.h>
#include <systems/background_transform_system.h>
#include <systems/enemy_system.h>
#include <systems/enemy_animation_system.h>
#include <systems/health_bar_transform_system.h>
#include <systems/text_transform_system.h>
#include <systems/score_system.h>
#include <systems/fade_overlay_system.h>
#include <systems/pause_menu_transform_system.h>
#include <systems/transition_system.h>
#include <systems/hud_transform_system.h>
#include <systems/label_system.h>
#include <systems/render_system.h>
#include <systems/powerup_system.h>

class VerticalScene : public GameScene {
private:
    std::vector<uint32_t> bg_entities;
    SpriteTransformSystem sprite_transform_system;
    PhysicsSystem physics_system;
    PlayerMovementSystem player_movement_system;
    VerticalLevelSystem level_system;
    PlayerAnimationSystem player_animation_system;
    EnemyAnimationSystem enemy_animation_system;
    TimerSystem timer_system;
    PandaDamageSystem panda_dmg_system;
    FallingPlatformSystem falling_platform_system;
    BackgroundTransformSystem background_transform_system;
    EnemySystem enemy_system;
    HealthBarTransformSystem health_bar_transform_system;
    TextTransformSystem text_transform_system;
    ScoreSystem score_system;
    FadeOverlaySystem fade_overlay_system;
    PauseMenuTransformSystem pause_menu_transform_system;
    TransitionSystem transition_system;
    HudTransformSystem hud_transform_system;
    LabelSystem label_system;
    RenderSystem render_system;
    PowerupSystem powerup_system;

    bool pause = false;
    int high_score_;

    uint32_t timer_entity;
    const std::string END_TIMER_LABEL = "end";
    const float END_TIMER_LENGTH = 30;

    void init_scene(Blackboard &blackboard);
    void check_end_timer();
public:

    VerticalScene(Blackboard& blackboard, SceneManager& scene_manager);
    virtual void update(Blackboard& blackboard) override;

    virtual void render(Blackboard& blackboard) override;

    void create_background(Blackboard &blackboard);

    void set_mode(SceneMode mode, Blackboard &blackboard) override;

    void set_high_score(int value);

    int get_high_score();
    static constexpr float CAMERA_SPEED = 250.f;

    void go_to_next_scene(Blackboard &blackboard);

    void cleanup();

    void update_camera(Blackboard &blackboard);

    void update_panda(Blackboard &blackboard);

    void reset_scene(Blackboard& blackboard) override;
};

#endif //PANDAEXPRESS_VERTICAL_SCENE_H
