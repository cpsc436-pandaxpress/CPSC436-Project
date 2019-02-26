//
// Created by Kenneth William on 2019-02-23.
//

#ifndef PANDAEXPRESS_CHASE_SYSTEM_H
#define PANDAEXPRESS_CHASE_SYSTEM_H

#include "system.h"
#include "components/panda.h"
#include "components/transform.h"
#include "components/collidable.h"

class ChaseSystem : public System {
public:
    ChaseSystem();
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;
};


#endif //PANDAEXPRESS_CHASE_SYSTEM_H
