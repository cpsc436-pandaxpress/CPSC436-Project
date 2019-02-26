//
// Created by Becca Roth on 2019-02-22.
//

#ifndef PANDAEXPRESS_GHOST_MOVEMENT_SYSTEM_H
#define PANDAEXPRESS_GHOST_MOVEMENT_SYSTEM_H


class ghost_movement_system {

};
#include "system.h"
#include "components/ghost.h"

class GhostMovementSystem : public System {
public:
    GhostMovementSystem();
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry);
};


#endif //PANDAEXPRESS_GHOST_MOVEMENT_SYSTEM_H
