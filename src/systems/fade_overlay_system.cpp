//
// Created by Avery Brown on 2019-03-30.
//

#include <graphics/fade_overlay.h>
#include <components/panda.h>
#include <components/timer.h>
#include "fade_overlay_system.h"

FadeOverlaySystem::FadeOverlaySystem() {}

void FadeOverlaySystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    float change_in_alpha = FADE_OUT_SPEED*blackboard.delta_time;
    /*if (blackboard.camera.transition_ready){
        change_in_alpha = FADE_OUT_SPEED_TRANSITION*blackboard.delta_time;
    }*/
    float alpha;

    auto viewPanda = registry.view<Panda, Timer>();
    for (auto entity: viewPanda) {
        auto &panda = viewPanda.get<Panda>(entity);
        if (panda.dead) {
            alpha = 0.f;
        }
        auto &timer = viewPanda.get<Timer>(entity);
        float curr_time = timer.get_curr_time("end_scene");
        if ((int) curr_time == 0){
            fadeIn = true;
        }
    }
    if(blackboard.camera.transition_ready) {
        alpha = 0.f;
    }
    auto viewFade = registry.view<FadeOverlay>();
    for (auto entity: viewFade) {
        auto &fadeOverlay = viewFade.get(entity);
        if (fadeIn) {
            alpha = fadeOverlay.alpha() - change_in_alpha;
            if ((int) alpha < 0) {
                fadeIn = false;
            }
        } else if ((int) alpha < 0) {
            alpha = fadeOverlay.alpha() + change_in_alpha;
        }
        float position_x = blackboard.camera.position().x;
        float position_y = blackboard.camera.position().y;
        fadeOverlay.set_pos(position_x, position_y);
        fadeOverlay.set_alpha(alpha);
    }
}
