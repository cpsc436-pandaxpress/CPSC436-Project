//
// Created by Prayansh Srivastava on 2019-04-07.
//

#ifndef PANDAEXPRESS_GAME_SCENE_H
#define PANDAEXPRESS_GAME_SCENE_H

#include <iomanip>
#include <graphics/fade_overlay.h>
#include <graphics/health_bar.h>
#include <graphics/text.h>
#include <components/timer.h>
#include <components/hud_element.h>
#include <components/score.h>
#include <components/pause_menu.h>
#include <components/transform.h>
#include <components/panda.h>
#include <components/obeys_gravity.h>
#include <components/health.h>
#include <components/interactable.h>
#include <components/causes_damage.h>
#include <components/velocity.h>
#include <components/collidable.h>
#include "scene.h"

class GameScene : public Scene {
protected:
    const float PANDA_START_X = -10.f;
    const float PANDA_START_Y = -200.f;
    const float HEALTH_BAR_X_SIZE = 750.f;
    const float HEALTH_BAR_Y_SIZE = 75.f;

    const float CAMERA_START_X = 0.f;
    const float CAMERA_START_Y = 0.f;

    const float HUD_Y_OFFSET = 50.f;
    const float HUD_SCORE_X_OFFSET = 350.f;
    const float HUD_HEALTH_X_OFFSET = 100.f;

    uint32_t panda_entity;
    uint32_t pause_menu_entity;

    GameScene(SceneManager &manager);

    void create_panda(Blackboard &blackboard);

    void create_score_text(Blackboard &blackboard);

    void create_high_score_text(Blackboard &blackboard, int high_score);

    void create_fade_overlay(Blackboard &blackboard);

    void create_pause_menu(Blackboard &blackboard);

    void cleanup();

};


#endif //PANDAEXPRESS_GAME_SCENE_H
