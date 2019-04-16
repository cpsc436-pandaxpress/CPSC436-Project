//
// Created by cowan on 14/04/19.
//

#include <components/panda.h>
#include <components/timer.h>
#include "powerup_system.h"

void PowerupSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    auto panda_view = registry.view<Panda, Timer>();

    for (auto entity : panda_view) {
        auto& panda = panda_view.get<Panda>(entity);
        auto& timer = panda_view.get<Timer>(entity);

        while (!panda.powerups.empty()) {
            PowerupType type = panda.powerups.front();
            switch (type) {
                case SHIELD_POWERUP:
                    panda.invincible = true;
                    timer.save_watch(SHIELD_TIMER_LABEL, SHIELD_TIMER_LENGTH);
                    break;
                default:
                    break;
            }

            panda.powerups.pop();
        }

        if (timer.exists(SHIELD_TIMER_LABEL) && timer.is_done(SHIELD_TIMER_LABEL)) {
            panda.invincible = false;
            timer.remove(SHIELD_TIMER_LABEL);
        }
    }
}