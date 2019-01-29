//
// Created by alex on 27/01/19.
//

#pragma once

#include "system.h"

class SpriteRenderSystem : public System {
public:
    SpriteRenderSystem();

    virtual void update(Blackboard& blackboard, entt::registry<uint32_t>& registry) override;

};