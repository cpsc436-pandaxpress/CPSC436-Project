//
// Created by Becca Roth on 2019-02-22.
//

#include "ghost_movement_system.h"
#include "physics_system.h"
#include "components/ghost.h"
#include "components/panda.h"
#include "components/velocity.h"
#include "components/interactable.h"
#include "components/transform.h"
#include "components/obeys_gravity.h"
#include "components/collidable.h"

GhostMovementSystem::GhostMovementSystem() {}

void GhostMovementSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {
    vec2 cam_position = blackboard.camera.position();
    vec2 cam_size = blackboard.camera.size();

    auto ghost_view = registry.view<Ghost, Transform, Velocity, Collidable>();
    for (auto enemy_entity : ghost_view) {
        auto& ghost = ghost_view.get<Ghost>(enemy_entity);
        auto& gh_transform = ghost_view.get<Transform>(enemy_entity);
        auto& gh_velocity = ghost_view.get<Velocity>(enemy_entity);
        auto& gh_collidable = ghost_view.get<Collidable>(enemy_entity);
        // Off screen time - would be better to do with coordinates but I was struggling with it
        if (!ghost.onScreen) {
            if (gh_transform.x + gh_collidable.width / 2 < cam_position.x + cam_size.x / 2) {
                ghost.onScreen = true;
                ghost.waiting = true;
            }
        }
        // Waiting state
        else if (ghost.onScreen && ghost.waiting){
            if (ghost.waittime < 0){
                auto pandas_view = registry.view<Panda, Transform>();
                for (auto panda_entity : pandas_view) {
                    auto &pa_transform = pandas_view.get<Transform>(panda_entity);
                    ghost.aim_x = pa_transform.x;
                    ghost.aim_y = pa_transform.y;
                }
                ghost.waiting = false;
                ghost.start_x = gh_transform.x;
                ghost.start_y = gh_transform.y;
            }
            else {
                gh_velocity.x_velocity = 150;
                if (int(llround(floor(ghost.waittime))) % 2 == 0) {
                    if (ghost.waiting_high && ghost.waiting_left) {
                        gh_transform.x = gh_transform.x + 3;
                        ghost.waiting_left = false;
                        ghost.waiting_right = true;
                    } else if (ghost.waiting_high && ghost.waiting_right) {
                        gh_transform.y = gh_transform.y + 3;
                        ghost.waiting_high = false;
                        ghost.waiting_low = true;
                    } else if (ghost.waiting_low && ghost.waiting_right) {
                        gh_transform.x = gh_transform.x - 3;
                        ghost.waiting_left = true;
                        ghost.waiting_right = false;
                    } else {
                        gh_transform.y = gh_transform.y - 3;
                        ghost.waiting_high = true;
                        ghost.waiting_low = false;
                    }
                }
                ghost.waittime = ghost.waittime - blackboard.delta_time*4;
                printf("waittime: %f\n", ghost.waittime);
            }
        }
        // Curve to swoop at player
        else if (ghost.onScreen && !ghost.waiting){
            if (ghost.swoopTime <= 1){
                float t = ghost.swoopTime;
                float x=(2*t*t*t-3*t*t+1)*ghost.start_x+(-2*t*t*t+3*t*t)*ghost.aim_x+
                  (t*t*t-2*t*t+t)*ghost.start_tangent+(t*t*t-t*t)*ghost.aim_tangent;
                float y=(2*t*t*t-3*t*t+1)*ghost.start_y+(-2*t*t*t+3*t*t)*ghost.aim_y+
                  (t*t*t-2*t*t+1)*ghost.start_tangent+(t*t*t-t*t)*ghost.aim_tangent;
                gh_transform.x = x;
                gh_transform.y = y;
                ghost.swoopTime = ghost.swoopTime + blackboard.delta_time/2;
                printf("x: %f\n", x);
                printf("y: %f\n", y);
                printf("swoopTime: %f\n", ghost.swoopTime);
            }
            else {
                gh_velocity.x_velocity = -150;
                gh_velocity.y_velocity = 30;
            }
        }
    }
}
