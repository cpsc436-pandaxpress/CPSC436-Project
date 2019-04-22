//
// Created by Prayansh Srivastava on 2019-02-12.
//

#ifndef PANDAEXPRESS_TEST_SCENE_2_H
#define PANDAEXPRESS_TEST_SCENE_2_H

#include "scene.h"
#include <queue>
#include <level/horizontal_level_system.h>
#include <systems/background_transform_system.h>
#include <systems/timer_system.h>
#include <systems/falling_platform_system.h>
#include <systems/panda_damage_system.h>
#include <systems/health_bar_transform_system.h>
#include <systems/text_transform_system.h>
#include <systems/score_system.h>
#include <systems/fade_overlay_system.h>
#include <systems/pause_menu_transform_system.h>
#include <systems/hud_transform_system.h>
#include <systems/label_system.h>
#include <systems/render_system.h>
#include <systems/powerup_system.h>
#include "scene.h"
#include "scene_manager.h"
#include "../systems/sprite_transform_system.h"
#include "../util/blackboard.h"
#include "../systems/physics_system.h"
#include "../systems/player_movement_system.h"
#include "../systems/enemy_system.h"
#include "../systems/transition_system.h"
#include "../systems/player_animation_system.h"
#include "../systems/enemy_animation_system.h"
#include "game_scene.h"

class HorizontalScene: public GameScene {
private:
    const float MAX_CAMERA_Y_DIFF = 250.f;
    bool pause = false;
    int high_score_;

    uint32_t timer_entity;
    const std::string END_TIMER_LABEL = "end";
    const float END_TIMER_LENGTH = 40;

    std::vector<uint32_t> bg_entities;
    HorizontalLevelSystem level_system;
    SpriteTransformSystem sprite_transform_system;
    BackgroundTransformSystem background_transform_system;
    PhysicsSystem physics_system;
    PlayerMovementSystem player_movement_system;
    EnemySystem enemy_system;
    PlayerAnimationSystem player_animation_system;
    EnemyAnimationSystem enemy_animation_system;
    TimerSystem timer_system;
    FallingPlatformSystem falling_platform_system;
    PandaDamageSystem panda_dmg_system;
    HealthBarTransformSystem health_bar_transform_system;
    TextTransformSystem text_transform_system;
    ScoreSystem score_system;
    TransitionSystem transition_system;
    FadeOverlaySystem fade_overlay_system;
    PauseMenuTransformSystem pause_menu_transform_system;
    HudTransformSystem hud_transform_system;
    LabelSystem label_system;
    RenderSystem render_system;
    PowerupSystem powerup_system;

    void create_background(Blackboard &blackboard);
    void init_scene(Blackboard &blackboard);
    void update_panda(Blackboard& blackboard);
    void update_camera(Blackboard& blackboard);
    void check_end_timer();
public:
    HorizontalScene(Blackboard &blackboard,
                    SceneManager &scene_manager);
    virtual void update(Blackboard& blackboard) override;

    virtual void render(Blackboard& blackboard) override;

    void set_mode(SceneMode mode, Blackboard &blackboard) override;

    void set_high_score(int value);

    int get_high_score();
    void reset_scene(Blackboard& blackboard) override;

    static constexpr float CAMERA_SPEED = 400.f;

    void go_to_next_scene(Blackboard &blackboard);

    void cleanup();
};


#endif //PANDAEXPRESS_TEST_SCENE_2_H

