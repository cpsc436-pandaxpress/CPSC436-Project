//
// Created by cowan on 30/01/19.
//

#ifndef PANDAEXPRESS_PHYSICS_SYSTEM_H
#define PANDAEXPRESS_PHYSICS_SYSTEM_H

#include "system.h"

class PhysicsSystem : public System {
public:
    PhysicsSystem();
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;

private:
    const float GRAVITY = 0.002;
};


#endif //PANDAEXPRESS_PHYSICS_SYSTEM_H
