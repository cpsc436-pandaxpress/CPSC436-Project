//
// Created by cowan on 01/03/19.
//

#include <components/timer.h>
#include "timer_system.h"

void TimerSystem::update(Blackboard& blackboard, entt::DefaultRegistry& registry) {
    auto timers = registry.view<Timer>();
    for (auto entity : timers) {
        Timer& timer = timers.get(entity);
        timer.update(blackboard.delta_time);
    }
}