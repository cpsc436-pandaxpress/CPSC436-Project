//
// Created by alex on 27/01/19.
//

#include "sprite_transform_system.h"

#include "../components/position.h"
#include "../graphics/sprite.h"

SpriteTransformSystem::SpriteTransformSystem() {}

void SpriteTransformSystem::update(Blackboard &blackboard, entt::registry <uint32_t> &registry) {
    // construct a view for all entites with a position and sprite component
    auto view = registry.view<Position, Sprite>();

    // foreach loop over all entities in view
    for (auto entity: view) {
        //get the position and sprite for the current entity
        auto& pos = view.get<Position>(entity);
        auto& sprite = view.get<Sprite>(entity);

        //transform the sprite
        sprite.set_pos(pos.x, pos.y);
        sprite.set_rotation_rad(pos.theta);
    }
}