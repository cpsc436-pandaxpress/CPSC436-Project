//
// Created by Kenneth William on 2019-02-23.
//

#include "chase_system.h"
#include <iostream>
#include "components/collidable.h"
#include "components/platform.h"
#include "components/velocity.h"
#include "components/interactable.h"
#include "collision_system.h"
#include "components/panda.h"
#include "components/chases.h"
#include "components/transform.h"
#include "components/bread.h"
#include "components/llama.h"
#include "components/spit.h"
#include "components/obstacle.h"
using namespace std;

ChaseSystem::ChaseSystem() {}


void ChaseSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {
    auto chaser_view = registry.view<Chases, Transform, Velocity>();
    auto panda_view = registry.view<Panda, Transform, Velocity>();

    for (auto entity: chaser_view) {
        auto &transform = chaser_view.get<Transform>(entity);
        auto &velocity = chaser_view.get<Velocity>(entity);
        auto &chases = chaser_view.get<Chases>(entity);


        auto chasedPosition = registry.get<Transform>(chases.target);

        if (chasedPosition.x < transform.x) {
            velocity.x_velocity = -40;
        } else if (chasedPosition.x > transform.x) {
            velocity.x_velocity = 40;
        }

        if (chasedPosition.y < transform.y) {
            velocity.y_velocity = -40;
        } else if (chasedPosition.y > transform.y) {
            velocity.y_velocity = 40;
        }

    }
}