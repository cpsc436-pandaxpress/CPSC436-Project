//
// Created by Prayansh Srivastava on 2019-03-14.
//

#ifndef PANDAEXPRESS_ENEMYDAMAGESYSTEM_H
#define PANDAEXPRESS_ENEMYDAMAGESYSTEM_H


#include "system.h"

class DamageSystem : System {
private:
    void handle_panda_damage(unsigned int entity, Blackboard &blackboard,
                             entt::DefaultRegistry &registry);

public:
    const float PANDA_DMG_INVINCIBLE_TIMER = 1.f;
    const float PANDA_DMG_REACTION_X = 200.f;
    const float PANDA_DMG_REACTION_Y = -1000.f;
    const std::string PANDA_DMG_TIMER_LABEL = "dmg_invincible";
    DamageSystem();

    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;

    void
    handle_bread_damage(unsigned int bread_entity, Blackboard &blackboard, entt::DefaultRegistry &registry);

    void
    handle_jacko_damage(unsigned int jacko_entity, Blackboard &blackboard, entt::DefaultRegistry &registry);
};


#endif //PANDAEXPRESS_ENEMYDAMAGESYSTEM_H
