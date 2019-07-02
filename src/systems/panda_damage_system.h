//
// Created by Prayansh Srivastava on 2019-03-04.
//

#ifndef PANDAEXPRESS_PANDA_DAMAGE_SYSTEM_H
#define PANDAEXPRESS_PANDA_DAMAGE_SYSTEM_H


#include "system.h"
#include <string>

class PandaDamageSystem: System {
private:
    const float DMG_INVINCIBLE_TIMER = 1.f;
    const float DMG_REACTION_X = 200.f;
    const float DMG_REACTION_Y = -1000.f;
    const std::string DMG_TIMER_LABEL = "dmg_invincible";
    const std::string DEATH_TIMER_LABEL = "dying";
    const float DEATH_TIMER = 2.5f;

public:
    PandaDamageSystem();
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;
};


#endif //PANDAEXPRESS_PANDA_DAMAGE_SYSTEM_H
