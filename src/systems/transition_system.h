//
// Created by Becca Roth on 2019-03-31.
//

#ifndef PANDAEXPRESS_TRANSITION_SYSTEM_H
#define PANDAEXPRESS_TRANSITION_SYSTEM_H


#include "system.h"
#include "util/constants.h"
#include "graphics/cave.h"
#include "components/transform.h"
#include "components/velocity.h"
#include "components/panda.h"

class TransitionSystem {
private:
    float cave_offset = 100.f;
public:
    TransitionSystem();
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry);
};


#endif //PANDAEXPRESS_TRANSITION_SYSTEM_H
