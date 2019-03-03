//
// Created by cowan on 01/03/19.
//

#ifndef PANDAEXPRESS_TIMER_SYSTEM_H
#define PANDAEXPRESS_TIMER_SYSTEM_H


#include <util/blackboard.h>
#include <entt/entity/registry.hpp>

class TimerSystem {
public:
    void update(Blackboard& blackboard, entt::DefaultRegistry& registry);
};


#endif //PANDAEXPRESS_TIMER_SYSTEM_H
