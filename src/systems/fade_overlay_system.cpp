//
// Created by Avery Brown on 2019-03-30.
//

#include <graphics/fade_overlay.h>
#include <components/panda.h>
#include <components/timer.h>
#include <scene/story_intro.h>
#include "fade_overlay_system.h"

FadeOverlaySystem::FadeOverlaySystem() {}

void FadeOverlaySystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    float change_in_alpha = FADE_OUT_SPEED*blackboard.delta_time;
    /*if (blackboard.camera.transition_ready){
        change_in_alpha = FADE_OUT_SPEED_TRANSITION*blackboard.delta_time;
    }*/
    float alpha;

    auto viewPanda = registry.view<Panda>();
    for (auto entity: viewPanda) {
        auto &panda = viewPanda.get(entity);
        if (panda.dead) {
            alpha = 0.f;
        }
    }
    if(blackboard.camera.transition_ready) {
        alpha = 0.f;
    }
    auto viewFade = registry.view<FadeOverlay, Timer>();
    for (auto entity: viewFade) {
        auto &fadeOverlay = viewFade.get<FadeOverlay>(entity);
        auto &timer = viewFade.get<Timer>(entity);
        float curr_time = timer.get_curr_time(StoryIntroScene::BEACH_SCENE_END_LABEL);
        if ((int) curr_time == 0){
            fadeOverlay.set_fadeIn(true);
        }

        if (fadeOverlay.fadeIn()) {
            alpha = fadeOverlay.alpha() - change_in_alpha;
            if ((int) alpha < 0) {
//                printf("%s \n", "sos");
                fadeOverlay.set_fadeIn(false);
            }
        } else if ((int) alpha < 0) {
//            printf("%s \n", "so");
            alpha = fadeOverlay.alpha() + change_in_alpha;
        }

        float position_x = blackboard.camera.position().x;
        float position_y = blackboard.camera.position().y;
        fadeOverlay.set_pos(position_x, position_y);
        fadeOverlay.set_alpha(alpha);
    }
}
