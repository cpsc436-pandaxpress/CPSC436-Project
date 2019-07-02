//
// Created by Prayansh Srivastava on 2019-03-05.
//

#include "text_transform_system.h"
#include "components/transform.h"
#include <graphics/text.h>

TextTransformSystem::TextTransformSystem() {}

void TextTransformSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {
    // construct a view for all entites with a position and sprite component
    auto view = registry.view<Transform, Text>();

    // foreach loop over all entities in view
    for (auto entity: view) {
        //get the position and sprite for the current entity
        auto& transform = view.get<Transform>(entity);
        auto& text = view.get<Text>(entity);

        //transform the sprite
        text.set_pos(transform.x, transform.y);
        text.set_scale(transform.x_scale); // y-scale is unused
    }
}
