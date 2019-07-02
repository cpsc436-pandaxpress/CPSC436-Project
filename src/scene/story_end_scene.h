//
// Created by Avery Brown on 2019-04-19.
//

#ifndef PANDAEXPRESS_STORY_END_SCENE_H
#define PANDAEXPRESS_STORY_END_SCENE_H


#include "game_scene.h"
#include <systems/timer_system.h>
#include <systems/fade_overlay_system.h>
#include <systems/physics_system.h>
#include <systems/pause_menu_transform_system.h>
#include <systems/background_transform_system.h>
#include <systems/render_system.h>
#include <systems/story_end_animation_system.h>
#include "scene.h"
#include "scene_manager.h"
#include "../systems/sprite_transform_system.h"
#include "../util/blackboard.h"
#include "../systems/timer_system.h"

class StoryEndScene: public GameScene {
private:
    const float PANDA_POS_X = -2200.f;
    const float PANDA_POS_Y = 130.f;
    const float KELLY_POS_X = 430.f;
    const float KELLY_POS_Y = 230.f;
    const float END_SCENE_END = 15.f;
    const float SKIP_POS_X = 1800.f;
    const float SKIP_POS_Y = 350.f;
    const std::string SKIP_SCENE_LABEL;
    const float SKIP_SCENE = 20.f;
    const float SKIP_SPEED = 250.f;


    bool pause = false;
    bool endScene = false;

    uint32_t panda_entity;
    uint32_t kelly_entity;
    uint32_t background_entity;
    uint32_t skip_entity;
    SpriteTransformSystem sprite_transform_system;
    StoryEndAnimationSystem story_animation_system;
    TimerSystem timer_system;
    FadeOverlaySystem fade_overlay_system;
    PauseMenuTransformSystem pause_menu_transform_system;
    RenderSystem render_system;
    PhysicsSystem physics_system;
    Timer scene_timer;


    void create_background(Blackboard &blackboard);
    void create_panda(Blackboard& blackboard);
    void create_kelly(Blackboard& blackboard);
    void create_skip_message(Blackboard &blackboard);
    void init_scene(Blackboard &blackboard);


public:
    StoryEndScene(Blackboard &blackboard,
                         SceneManager &scene_manager);

    static const std::string END_SCENE_END_LABEL;

    virtual void update(Blackboard& blackboard) override;
    virtual void render(Blackboard& blackboard) override;
    void reset_scene(Blackboard& blackboard) override;

};

#endif //PANDAEXPRESS_STORY_END_SCENE_H
