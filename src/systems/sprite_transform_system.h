//
// Created by alex on 27/01/19.
//

#pragma once

#include "system.h"

class SpriteTransformSystem : public System {
public:
    SpriteTransformSystem();
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;
};
