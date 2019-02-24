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


        //    auto chasedPosition = registry.get<Transform>(chases.target);


        for (auto entity: panda_view) {
            auto &pandaTransform = panda_view.get<Transform>(entity);
            if (pandaTransform.x < transform.x) {
                velocity.x_velocity = -20;
            } else if (pandaTransform.x > transform.x) {
                velocity.x_velocity = 20;
            }

            if (pandaTransform.y < transform.y) {
                velocity.y_velocity = -20;
            } else if (pandaTransform.y > transform.y) {
                velocity.y_velocity = 20;
            }
        }
    }
}