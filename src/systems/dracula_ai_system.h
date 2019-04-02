//
// Created by Kenneth William on 2019-02-24.
//

#ifndef PANDAEXPRESS_DRACULA_AI_SYSTEM_H
#define PANDAEXPRESS_DRACULA_AI_SYSTEM_H

#include "system.h"
#include "util/selector_node.h"
#include "util/coordinates.h"
#include "components/dracula.h"
#include "components/seeks.h"
#include "components/chases.h"
#include "components/timer.h"
#include "components/evades.h"
#include "components/panda.h"
#include "components/food.h"
#include "components/transform.h"
#include "components/velocity.h"
#include "components/interactable.h"
#include "components/health.h"
#include "systems/a_star_system.h"

class DraculaAISystem: public System {
    private:
        SelectorNode *root;

    public:
    DraculaAISystem(Blackboard& blackboard, entt::DefaultRegistry& registry, AStarSystem& a_star_system);
    void ShootBats(Blackboard& blackboard, entt::DefaultRegistry& registry, AStarSystem& a_star_system);
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;
    int getPandaHealth(Blackboard& blackboard, entt::DefaultRegistry& registry);
    int getDraculaHealth(Blackboard& blackboard, entt::DefaultRegistry& registry);
    //void evasion(Blackboard& blackboard, entt::DefaultRegistry& registry);
};


#endif //PANDAEXPRESS_DRACULA_AI_SYSTEM_H
