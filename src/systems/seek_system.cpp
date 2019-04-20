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
            Coordinates* target = seeks.seekList[0];
            if(seeks.batDirection==Seeks::WAITING) {

                if (abs(target->x - transform.x) > abs(target->y - transform.y)) {
                    if (target->x > transform.x) {
                        seeks.batDirection = Seeks::RIGHT;
                    } else {
                        seeks.batDirection = Seeks::LEFT;
                    }
                } else {
                    if (target->y > transform.y) {
                        seeks.batDirection = Seeks::DOWN;
                    } else {
                        seeks.batDirection = Seeks::UP;
                    }
                }
            }


            if(abs(target->x - transform.x) < 3 && (seeks.batDirection==Seeks::LEFT || seeks.batDirection==Seeks::RIGHT)){

                seeks.seekList.erase(seeks.seekList.begin());
                seeks.batDirection=Seeks::WAITING;
                velocity.y_velocity=0;
                velocity.x_velocity=0;

            }else if(abs(target->y - transform.y) < 3 && (seeks.batDirection==Seeks::UP || seeks.batDirection==Seeks::DOWN)){

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

        }
/*
        if(seeks.seekList.size()>0){
            Coordinates* target = seeks.seekList[0];
            if(!seeks.goingVertical && !seeks.goingHorizontal){
                if(abs(target->x-transform.x) > abs(target->y-transform.y) ){
                    seeks.goingHorizontal=true;
                    seeks.goingVertical=false;
                }else{
                    seeks.goingVertical=true;
                    seeks.goingHorizontal=false;
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
                    if (target->x -blackboard.camera.position().x < transform.x - blackboard.camera.position().x) {
                        velocity.x_velocity = -seeks.seek_speed;

                    } else if(target->x -blackboard.camera.position().x > transform.x - blackboard.camera.position().x) {
                        velocity.x_velocity = seeks.seek_speed;

                    }
                    if(abs(target->x -blackboard.camera.position().x - transform.x - blackboard.camera.position().x)<1){
                        velocity.x_velocity=0;
                    }else{
                        velocity.y_velocity=0;
                        transform.y = transform.y + sin(transform.x/50)*0.3f;
                    }


                }else if(seeks.goingVertical) {
                    if (target->y -blackboard.camera.position().y < transform.y-blackboard.camera.position().y) {
                        velocity.y_velocity = -seeks.seek_speed;

                    } else if(target->y -blackboard.camera.position().y > transform.y-blackboard.camera.position().y) {
                        velocity.y_velocity = seeks.seek_speed;

                    }
                    if(abs(target->x -blackboard.camera.position().x - transform.x - blackboard.camera.position().x)<1){
                        velocity.y_velocity=0;
                    }else{
                        velocity.x_velocity=0;
                        transform.x= transform.x + sin(transform.y/50)*0.3f;
                    }

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
                seeks.goingHorizontal=false;
                seeks.goingHorizontal=false;
            }

        }
*/
    }

}