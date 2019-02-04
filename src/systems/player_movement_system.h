//
// Created by Kenneth William on 2019-01-31.
//

#ifndef PANDAEXPRESS_MOVEABLE_H
#define PANDAEXPRESS_MOVEABLE_H

#include "system.h"
#include "components/panda.h"

class PlayerMovementSystem : public System {
public:
    PlayerMovementSystem();
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;

private:
    const float PANDA_SPEED = 600.f;
    const float PANDA_JUMP_SPEED = 600.f;

    float time_since_jump = 0.f;
    bool holding_jump = false;

};


#endif //PANDAEXPRESS_MOVEABLE_H
