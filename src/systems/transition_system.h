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
#include "components/jacko.h"
#include "scene/scene.h"

class TransitionSystem {
private:
    float cave_offset = 100.f;
    SceneType scene_type;
public:
    TransitionSystem(SceneType scene_type);
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry);
};


#endif //PANDAEXPRESS_TRANSITION_SYSTEM_H
