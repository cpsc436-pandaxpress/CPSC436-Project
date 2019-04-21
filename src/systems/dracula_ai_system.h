//
// Created by Kenneth William on 2019-02-24.
//

#ifndef PANDAEXPRESS_DRACULA_AI_SYSTEM_H
#define PANDAEXPRESS_DRACULA_AI_SYSTEM_H

#include "system.h"
#include "util/selector_node.h"
#include "util/ai_nodes.h"
#include "components/dracula.h"
#include "components/chases.h"
#include "components/evades.h"
#include "components/panda.h"
#include "components/food.h"
#include "components/transform.h"
#include "components/velocity.h"
#include "components/interactable.h"
#include "components/health.h"
#include "a_star_system.h"

class DraculaAISystem: public System {
    private:
        SelectorNode root;
        AINodes::CheckHealth* checkHealth;
        AINodes::CheckPandaDeath* checkPandaDeath;
        AStarSystem a_star_system;

    public:
    DraculaAISystem(Blackboard& blackboard, entt::DefaultRegistry& registry);
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;
    int getPandaHealth(Blackboard& blackboard, entt::DefaultRegistry& registry);
    int getDraculaHealth(Blackboard& blackboard, entt::DefaultRegistry& registry);
    void evasion(Blackboard& blackboard, entt::DefaultRegistry& registry);
};


#endif //PANDAEXPRESS_DRACULA_AI_SYSTEM_H
