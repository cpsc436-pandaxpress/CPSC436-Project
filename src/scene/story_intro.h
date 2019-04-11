//
// Created by Avery Brown on 2019-04-09.
//

#ifndef PANDAEXPRESS_STORY_INTRO_H
#define PANDAEXPRESS_STORY_INTRO_H


#include "scene.h"
#include <systems/timer_system.h>
#include <systems/fade_overlay_system.h>
#include <systems/fade_overlay_render_system.h>
#include <systems/pause_menu_transform_system.h>
#include <systems/pause_menu_render_system.h>
#include <systems/story_animation_system.h>
#include "scene.h"
#include "scene_manager.h"
#include "../systems/sprite_render_system.h"
#include "../systems/sprite_transform_system.h"
#include "../util/blackboard.h"
#include "../systems/timer_system.h"

class StoryIntroScene: public Scene {
private:
    const float PANDA_POS_X = -400.f;
    const float PANDA_POS_Y = 150.f;
    const float KELLY_POS_X = -230.f;
    const float KELLY_POS_Y = 200.f;
    const float HEARTS_POS_X = -290.f;
    const float HEARTS_POS_Y = 40.f;

    bool pause = false;
    uint32_t background_entity;
    uint32_t panda_entity;
    uint32_t kelly_entity;
    uint32_t hearts_entity;
    uint32_t jacko_entity;
    uint32_t pause_menu_entity;
    uint32_t fade_overlay_entity;
    SpriteTransformSystem sprite_transform_system;
    SpriteRenderSystem sprite_render_system;
    StoryAnimationSystem story_animation_system;
    TimerSystem timer_system;
    FadeOverlaySystem fade_overlay_system;
    FadeOverlayRenderSystem fade_overlay_render_system;
    PauseMenuTransformSystem pause_menu_transform_system;
    PauseMenuRenderSystem pause_menu_render_system;

    void create_background(Blackboard &blackboard);
    void create_panda(Blackboard& blackboard);
    void create_kelly(Blackboard& blackboard);
    void create_hearts(Blackboard& blackboard);
    void create_fade_overlay(Blackboard& blackboard);
    void create_pause_menu(Blackboard& blackboard);
//    void reset_scene(Blackboard& blackboard);
    void update_panda(Blackboard& blackboard);
//    void update_camera(Blackboard& blackboard);

public:
    StoryIntroScene(Blackboard &blackboard,
                    SceneManager &scene_manager);

    virtual void update(Blackboard& blackboard) override;
    virtual void render(Blackboard& blackboard) override;
    void init_scene(Blackboard &blackboard);
    void create_jacko(Blackboard& blackboard, uint32_t panda);

};

#endif //PANDAEXPRESS_STORY_INTRO_H
