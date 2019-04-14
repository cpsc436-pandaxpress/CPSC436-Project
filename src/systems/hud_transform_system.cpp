//
// Created by Prayansh Srivastava on 2019-03-27.
//

#include <components/hud_element.h>
#include <graphics/health_bar.h>
#include <graphics/text.h>
#include <components/score.h>
#include "hud_transform_system.h"

HudTransformSystem::HudTransformSystem() {

}

void HudTransformSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    // construct a view for all entites with a position and sprite component
    auto healthBarViews = registry.view<HudElement, HealthBar>(); // HealthBar HUD Elements
    for (auto entity: healthBarViews) {
        auto& hud = healthBarViews.get<HudElement>(entity);
        auto& healthbar = healthBarViews.get<HealthBar>(entity);
        healthbar.set_pos(blackboard.camera.get_relative_pos(hud.position));
    }
    auto textViews = registry.view<HudElement, Text>(); // Text HUD Elements
    for (auto entity: textViews) {
        auto& hud = textViews.get<HudElement>(entity);
        auto& text = textViews.get<Text>(entity);
        text.set_pos(blackboard.camera.get_relative_pos(hud.position));
    }
}
