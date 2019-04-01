//
// Created by Rebecca Roth on 2019-02-22.
//

#ifndef PANDAEXPRESS_GHOST_MOVEMENT_SYSTEM_H
#define PANDAEXPRESS_GHOST_MOVEMENT_SYSTEM_H

#include "system.h"
#include "util/constants.h"
#include "components/ghost.h"

class GhostMovementSystem{
public:
    GhostMovementSystem();
    virtual void update(Blackboard &blackboard, entt::DefaultRegistry &registry, SceneType scene_type);
};


#endif //PANDAEXPRESS_GHOST_MOVEMENT_SYSTEM_H