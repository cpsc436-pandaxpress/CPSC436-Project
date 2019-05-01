//
// Created by Kenneth William on 2019-03-29.
//

#include "seek_system.h"
#include <math.h>
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

        auto& velocity = seeker_view.get<Velocity>(entity);
        auto& seeks  = seeker_view.get<Seeks>(entity);
        auto& timer  = seeker_view.get<Timer>(entity);
        auto& transform  = seeker_view.get<Transform>(entity);
        if(seeks.seekList.size()>0){
            Coordinates target = seeks.seekList[0];
            if(seeks.batDirection==Seeks::WAITING) {

                if (abs(target.x - transform.x) > abs(target.y - transform.y)) {
                    if (target.x > transform.x) {
                        seeks.batDirection = Seeks::RIGHT;
                    } else {
                        seeks.batDirection = Seeks::LEFT;
                    }
                } else {
                    if (target.y > transform.y) {
                        seeks.batDirection = Seeks::DOWN;
                    } else {
                        seeks.batDirection = Seeks::UP;
                    }
                }
            }


            if((transform.x - target.x) < 5 && seeks.batDirection==Seeks::LEFT){

                seeks.seekList.erase(seeks.seekList.begin());
                seeks.batDirection=Seeks::WAITING;
                velocity.y_velocity=0;
                velocity.x_velocity=0;

            }else if((target.x - transform.x) < 5 && seeks.batDirection==Seeks::RIGHT){

                seeks.seekList.erase(seeks.seekList.begin());
                seeks.batDirection=Seeks::WAITING;
                velocity.y_velocity=0;
                velocity.x_velocity=0;
            }else if((target.y - transform.y) < 5 && (seeks.batDirection==Seeks::DOWN)){

                seeks.seekList.erase(seeks.seekList.begin());
                seeks.batDirection=Seeks::WAITING;
                velocity.y_velocity=0;
                velocity.x_velocity=0;
            }else if((transform.y - target.y) < 5 && (seeks.batDirection==Seeks::UP)){

            seeks.seekList.erase(seeks.seekList.begin());
            seeks.batDirection=Seeks::WAITING;
            velocity.y_velocity=0;
            velocity.x_velocity=0;
            }else{

                if(seeks.batDirection==Seeks::LEFT){
                    velocity.x_velocity = -seeks.seek_speed;
                    velocity.y_velocity = 0;
                    transform.y = transform.y + sin(transform.x/50)*0.3f;
                    transform.x_scale = abs(transform.x_scale);
                }else if(seeks.batDirection==Seeks::RIGHT){
                    velocity.x_velocity = seeks.seek_speed;
                    velocity.y_velocity = 0;
                    transform.y = transform.y + sin(transform.x/50)*0.3f;
                    transform.x_scale = -abs(transform.x_scale);
                }else if(seeks.batDirection==Seeks::UP) {
                    velocity.y_velocity = -seeks.seek_speed;
                    velocity.x_velocity = 0;
                    transform.x= transform.x + sin(transform.y/50)*0.3f;
                    transform.set_angle_degrees(90);
                }else if(seeks.batDirection==Seeks::DOWN) {
                    velocity.y_velocity = seeks.seek_speed;
                    velocity.x_velocity = 0;
                    transform.x= transform.x + sin(transform.y/50)*0.3f;
                    transform.set_angle_degrees(-90);
                }

                }


        }else{
            if(timer.watch_exists("batTimer")){
                velocity.x_velocity=0;
                velocity.y_velocity=0;

                if(timer.is_done("batTimer")){
                    registry.destroy(entity);
                }
            }else{
                timer.save_watch("batTimer", 1.f);
                seeks.batDirection=Seeks::WAITING;
            }
            seeks.seekList.clear();
            seeks.seekList.shrink_to_fit();
        }


    }

}