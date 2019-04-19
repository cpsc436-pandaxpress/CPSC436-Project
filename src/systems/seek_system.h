//
// Created by Kenneth William on 2019-03-29.
//

#ifndef PANDAEXPRESS_SEEK_SYSTEM_H
#define PANDAEXPRESS_SEEK_SYSTEM_H

#include "system.h"
#include "components/panda.h"
#include "components/transform.h"
#include "components/collidable.h"

class SeekSystem : public System {
public:
    SeekSystem();
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;
};



#endif //PANDAEXPRESS_SEEK_SYSTEM_H
