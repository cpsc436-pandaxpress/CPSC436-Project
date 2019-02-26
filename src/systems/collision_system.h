//
// Created by Kenneth William on 2019-01-31.
//

#ifndef PANDAEXPRESS_COLLISION_SYSTEM_H
#define PANDAEXPRESS_COLLISION_SYSTEM_H
#include "system.h"
#include "components/panda.h"
#include "components/transform.h"
#include "components/collidable.h"


class CollisionSystem : public System {
public:
    CollisionSystem();
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;

};

#endif //PANDAEXPRESS_COLLISION_SYSTEM_H
