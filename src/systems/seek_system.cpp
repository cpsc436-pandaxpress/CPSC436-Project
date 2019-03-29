//
// Created by Kenneth William on 2019-03-29.
//

#include "seek_system.h"
#include <iostream>
#include "components/collidable.h"
#include "components/velocity.h"
#include "components/seeks.h"

using namespace std;

SeekSystem::SeekSystem() {}


void SeekSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {

    auto seeker_view = registry.view<Seeks, Velocity, Transform>();

    for (auto entity: seeker_view) {

        auto& velocity = seeker_view.get<Velocity>(entity);
        auto& seeks  = seeker_view.get<Seeks>(entity);
        auto& transform  = seeker_view.get<Transform>(entity);

        if(seeks.seekList.size()>0){
            Coordinates* target = seeks.seekList[0];
            if(abs(target->x - transform.x) < 1 && abs(target->y-transform.y) <1){
                seeks.seekList.erase(seeks.seekList.begin());
            }else{
                if (target->x < transform.x) {
                    velocity.x_velocity = -seeks.seek_speed;
                } else if (target->x > transform.x) {
                    velocity.x_velocity = seeks.seek_speed;
                }

                if (target->y < transform.y) {
                    velocity.y_velocity = -seeks.seek_speed;
                } else if (target->y > transform.y) {
                    velocity.y_velocity = seeks.seek_speed;
                }
            }
        }else{
            registry.destroy(entity);
        }

    }

}