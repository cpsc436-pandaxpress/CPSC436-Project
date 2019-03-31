//
// Created by Avery Brown on 2019-03-30.
//

#include <graphics/fade_overlay.h>
#include <components/panda.h>
#include "fade_overlay_system.h"

FadeOverlaySystem::FadeOverlaySystem() {}

void FadeOverlaySystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {

    float change_in_alpha = FADE_OUT_SPEED*blackboard.delta_time;

    auto viewFade = registry.view<FadeOverlay>();
    for (auto entity: viewFade) {
        auto &fadeOverlay = viewFade.get(entity);
        (fadeOverlay.pause()) ? alpha = 0.f: (alpha += change_in_alpha);
        float position_x = blackboard.camera.position().x;
        float position_y = blackboard.camera.position().y;
        fadeOverlay.set_pos(position_x, position_y);
        fadeOverlay.set_alpha(alpha);
    }

    auto viewPanda = registry.view<Panda>();

    for (auto entity: viewPanda) {
        auto &panda = viewPanda.get(entity);
        if (panda.dead) {
            alpha = 0.f;
        }
    }
}
