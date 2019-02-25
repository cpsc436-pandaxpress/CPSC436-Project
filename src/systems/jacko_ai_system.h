//
// Created by Kenneth William on 2019-02-24.
//

#ifndef PANDAEXPRESS_JACKO_AI_SYSTEM_H
#define PANDAEXPRESS_JACKO_AI_SYSTEM_H

#include "system.h"
#include "util/selector_node.h"

class JackoAISystem: public System {
    private:
        SelectorNode *root;
    public:
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;
};


#endif //PANDAEXPRESS_JACKO_AI_SYSTEM_H
