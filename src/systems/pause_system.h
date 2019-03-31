//
// Created by Avery Brown on 2019-03-30.
//

#ifndef PANDAEXPRESS_PAUSE_SYSTEM_H
#define PANDAEXPRESS_PAUSE_SYSTEM_H

#include "system.h"

class PauseSystem: System {
private:
    const float DMG_INVINCIBLE_TIMER = 1.f;
    const float DMG_REACTION_X = 200.f;
    const float DMG_REACTION_Y = -1000.f;
public:
    PauseSystem();
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;
};

#endif //PANDAEXPRESS_PAUSE_SYSTEM_H
