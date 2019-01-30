//
// Created by alex on 20/01/19.
//

#pragma once

#include <entt/entity/registry.hpp>

#include "../util/blackboard.h"

class System {
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) = 0;
};