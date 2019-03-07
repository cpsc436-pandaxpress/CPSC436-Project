//
// Created by Kenneth William on 2019-03-06.
//

#ifndef PANDAEXPRESS_FALLING_PLATFORM_SYSTEM_H
#define PANDAEXPRESS_FALLING_PLATFORM_SYSTEM_H

#include <util/blackboard.h>
#include <entt/entity/registry.hpp>
#include <components/obeys_gravity.h>
#include <components/interactable.h>
#include <components/falling_platform.h>
#include <components/causes_damage.h>
#include <components/velocity.h>
#include <components/transform.h>
#include <components/platform.h>
#include <components/jacko.h>
#include <components/chases.h>
#include <components/timer.h>

class FallingPlatformSystem {
public:

    void update(Blackboard& blackboard, entt::DefaultRegistry& registry);
private:
    bool goingLeft = false;
};


#endif //PANDAEXPRESS_FALLING_PLATFORM_SYSTEM_H
