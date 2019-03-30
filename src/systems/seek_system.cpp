//
// Created by Kenneth William on 2019-03-29.
//

#include "seek_system.h"
#include <iostream>
#include "components/collidable.h"
#include "components/velocity.h"
#include "components/seeks.h"
#include "components/timer.h"

using namespace std;

SeekSystem::SeekSystem() {}


void SeekSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {

    auto seeker_view = registry.view<Seeks, Velocity, Transform, Timer>();

    for (auto entity: seeker_view) {
        float horizontalCenter;
        float verticalCenter;
        float maxBounceDist = 30;

        auto& velocity = seeker_view.get<Velocity>(entity);
        auto& seeks  = seeker_view.get<Seeks>(entity);
        auto& timer  = seeker_view.get<Timer>(entity);
        auto& transform  = seeker_view.get<Transform>(entity);

        if(seeks.seekList.size()>0){
            Coordinates* target = seeks.seekList[0];
            if(!seeks.goingVertical && !seeks.goingHorizontal){
                if(abs(target->x-transform.x) > abs(target->y-transform.y) ){
                    seeks.goingHorizontal=true;
                    seeks.goingVertical=false;
                    verticalCenter=transform.y;
                }else{
                    seeks.goingVertical=true;
                    seeks.goingHorizontal=false;
                    horizontalCenter=transform.x;
                }
            }


            if(abs(target->x - transform.x) < 1 && seeks.goingHorizontal){
                seeks.seekList.erase(seeks.seekList.begin());
                seeks.goingHorizontal=false;
                seeks.goingVertical=false;

            }else if(abs(target->y - transform.y) < 1 && seeks.goingVertical){
                seeks.seekList.erase(seeks.seekList.begin());
                seeks.goingHorizontal=false;
                seeks.goingVertical=false;
            }else{

                if(seeks.goingHorizontal){
                    if (target->x < transform.x) {
                        velocity.x_velocity = -seeks.seek_speed;
                    } else {
                        velocity.x_velocity = seeks.seek_speed;
                    }
                    velocity.y_velocity= seeks.bounce_speed;
                    if(abs(transform.y-verticalCenter)>maxBounceDist){
                        seeks.bounce_speed= -seeks.bounce_speed;
                    }
                }else if(seeks.goingVertical) {
                    if (target->y < transform.y) {
                        velocity.y_velocity = -seeks.seek_speed;
                    } else {
                        velocity.y_velocity = seeks.seek_speed;
                    }
                    velocity.x_velocity= seeks.bounce_speed;
                    if(abs(transform.x-horizontalCenter)>maxBounceDist){
                        seeks.bounce_speed= -seeks.bounce_speed;
                    }
                }
/*
                if(goingHorizontal){
                    velocity.y_velocity= 800;
                    if(abs(transform.y-verticalCenter)>maxBounceDist){
                        velocity.y_velocity= -velocity.y_velocity;
                    }
                }else{
                    velocity.x_velocity= 800;
                    if(abs(transform.x-horizontalCenter)>maxBounceDist){
                        velocity.x_velocity= -velocity.x_velocity;
                    }
                }
                */
            }
        }else{
            if(timer.watch_exists("batTimer")){
                if(timer.is_done("batTimer")){
                    registry.destroy(entity);
                }
            }else{
                timer.save_watch("batTimer", 1.);
                velocity.x_velocity=0;
                velocity.y_velocity=0;
                seeks.goingHorizontal=false;
                seeks.goingHorizontal=false;
            }

        }

    }

}