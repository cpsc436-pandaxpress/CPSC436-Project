//
// Created by Avery Brown on 2019-04-09.
//

#ifndef PANDAEXPRESS_STORY_INTRO_H
#define PANDAEXPRESS_STORY_INTRO_H


#include "game_scene.h"
#include <systems/timer_system.h>
#include <systems/fade_overlay_system.h>
#include <systems/physics_system.h>
#include <systems/pause_menu_transform_system.h>
#include <systems/render_system.h>
#include <systems/story_animation_system.h>
#include "scene.h"
#include "scene_manager.h"
#include "../systems/sprite_transform_system.h"
#include "../util/blackboard.h"
#include "../systems/timer_system.h"

class StoryIntroScene: public GameScene {
private:
    const float PANDA_POS_X = -420.f;
    const float PANDA_POS_Y = 150.f;
    const float KELLY_POS_X = -230.f;
    const float KELLY_POS_Y = 200.f;
    const float HEARTS_POS_X = -290.f;
    const float HEARTS_POS_Y = 40.f;
    const float JACKO_START_X = 1000.f;
    const float JACKO_START_Y = 80.f;
    const std::string BEACH_SCENE_END_LABEL = "end_scene";
    const float BEACH_SCENE_END = 27.f;

    bool pause = false;
    bool endScene = false;

    uint32_t background_entity;
    uint32_t panda_entity;
    uint32_t kelly_entity;
    uint32_t hearts_entity;
    uint32_t jacko_entity;
    SpriteTransformSystem sprite_transform_system;
    StoryAnimationSystem story_animation_system;
    TimerSystem timer_system;
    FadeOverlaySystem fade_overlay_system;
    PauseMenuTransformSystem pause_menu_transform_system;
    RenderSystem render_system;
    PhysicsSystem physics_system;
    Timer scene_timer;


    void create_background(Blackboard &blackboard);
    void create_panda(Blackboard& blackboard);
    void create_kelly(Blackboard& blackboard);
    void create_hearts(Blackboard& blackboard);
    void create_jacko(Blackboard& blackboard);
    void init_scene(Blackboard &blackboard);


public:
    StoryIntroScene(Blackboard &blackboard,
                    SceneManager &scene_manager);

    virtual void update(Blackboard& blackboard) override;
    virtual void render(Blackboard& blackboard) override;
    void reset_scene(Blackboard& blackboard) override;

};

#endif //PANDAEXPRESS_STORY_INTRO_H
