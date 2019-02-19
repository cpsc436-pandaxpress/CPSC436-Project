//
// Created by cowan on 30/01/19.
//

#ifndef PANDAEXPRESS_PHYSICS_SYSTEM_H
#define PANDAEXPRESS_PHYSICS_SYSTEM_H

#include "system.h"

class PhysicsSystem : public System {
private:
    static constexpr float GRAVITY = 2500.f;
public:

    PhysicsSystem();
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;

private:
    void applyGravity(Blackboard& blackboard, entt::DefaultRegistry& registry);
    void applyVelocity(Blackboard& blackboard, entt::DefaultRegistry& registry);
};


#endif //PANDAEXPRESS_PHYSICS_SYSTEM_H
