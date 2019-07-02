//
// Created by alex on 27/01/19.
//

#include <components/panda.h>
#include "sprite_transform_system.h"

#include "components/transform.h"
#include "../graphics/sprite.h"

SpriteTransformSystem::SpriteTransformSystem() {}

void SpriteTransformSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {
    // construct a view for all entites with a position and sprite component
    auto view = registry.view<Transform, Sprite>();

    // foreach loop over all entities in view
    for (auto entity: view) {
        //get the position and sprite for the current entity
        auto& transform = view.get<Transform>(entity);
        auto& sprite = view.get<Sprite>(entity);

        //transform the sprite
        sprite.set_pos((int)transform.x, (int)transform.y);
        sprite.set_rotation_rad(transform.theta);
        sprite.set_scale_int(transform.x_scale, transform.y_scale);
    }
}
