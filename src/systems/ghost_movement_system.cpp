//
// Created by Becca Roth on 2019-02-22.
//

#include "ghost_movement_system.h"
#include "physics_system.h"
#include "components/ghost.h"
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
            }
        }
        // Waiting state
        else if (ghost.onScreen && ghost.waiting){
            if (ghost.waittime < 0){
                ghost.waiting = false;
            }
            else {
                gh_velocity.x_velocity = 150;
                if (ghost.waittime % 10 == 0) {
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
                ghost.waittime--;
            }
        }
        // Curve to swoop at player
        else if (ghost.onScreen && !ghost.waiting){
            gh_velocity.x_velocity = -100;
            gh_velocity.y_velocity = 100;
        }
    }
}
