//
// Created by Kenneth William on 2019-01-31.
//

#ifndef PANDAEXPRESS_MOVEABLE_H
#define PANDAEXPRESS_MOVEABLE_H

#include "system.h"
#include "components/panda.h"

class playerMovementSystem : public System {
public:
    playerMovementSystem();
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;

private:
    const float PANDA_SPEED = 400.f;
    const float PANDA_JUMP_SPEED = 600.f;
};


#endif //PANDAEXPRESS_MOVEABLE_H
