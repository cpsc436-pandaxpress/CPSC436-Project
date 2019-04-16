//
// Created by cowan on 14/04/19.
//

#ifndef PANDAEXPRESS_POWERUP_SYSTEM_H
#define PANDAEXPRESS_POWERUP_SYSTEM_H


#include <util/blackboard.h>
#include <entt/entity/registry.hpp>

class PowerupSystem {
private:
    const std::string SHIELD_TIMER_LABEL;
    const float SHIELD_TIMER_LENGTH = 8.f;
public:
    void update(Blackboard& blackboard, entt::DefaultRegistry& registry);
};


#endif //PANDAEXPRESS_POWERUP_SYSTEM_H
