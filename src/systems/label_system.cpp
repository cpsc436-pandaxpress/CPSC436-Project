//
// Created by Prayansh Srivastava on 2019-03-30.
//

#include <graphics/text.h>
#include <components/label.h>
#include <components/panda.h>
#include <components/transform.h>
#include "label_system.h"
#include <algorithm>

LabelSystem::LabelSystem() {

}

void LabelSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    auto labelViews = registry.view<Text, Label, Transform>();
    for (auto entity:labelViews) {
        auto &label = labelViews.get<Label>(entity);
        auto &text = labelViews.get<Text>(entity);
        auto &transform = labelViews.get<Transform>(entity);
        label.opacity = std::max<float>(0.0, label.opacity - blackboard.delta_time * 0.7f / label.opacity); // decrease opacity non-linearly
        transform.y -= blackboard.delta_time * 10.0f; // move up
        transform.x_scale += blackboard.delta_time * 1.0f; // scale up
        text.set_opacity(label.opacity);
    }
    for (auto entity: labelViews) { // Destroy invisible labels
        auto &label = labelViews.get<Label>(entity);
        if (label.opacity == 0.0f) {
            registry.destroy(entity);
        }
    }
}
