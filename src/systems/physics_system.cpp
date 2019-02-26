//
// Created by cowan on 30/01/19.
//


#include "physics_system.h"
#include <numeric>
#include "components/platform.h"


#include "util/entity_pairs.h"

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::update(Blackboard& blackboard, entt::DefaultRegistry& registry) {

    apply_gravity(blackboard, registry);
    check_collisions(blackboard, registry);
    apply_velocity(blackboard, registry);
}

void PhysicsSystem::apply_gravity(Blackboard &blackboard, entt::DefaultRegistry &registry){
    /***
     * Applying gravity to objects that can walk on platforms
     ***/

    auto view = registry.view<ObeysGravity, Interactable, Transform, Velocity>();

    for (auto entity: view) {

        auto& transform = view.get<Transform>(entity);
        auto& walkable = view.get<Interactable>(entity);
        auto& velocity = view.get<Velocity>(entity);
        auto& gravity  = view.get<ObeysGravity>(entity);
        if (!walkable.grounded) {
            velocity.y_velocity += gravity.gravityFactor * blackboard.delta_time;
        } else{
            velocity.y_velocity=0.f;
        }
    }

    /***
     * Applying gravity to objects that can't walk on platforms
     ***/

    auto viewNonWalkable = registry.view<ObeysGravity, Transform, Velocity>();

    for (auto entity: viewNonWalkable) {
        auto& transform = viewNonWalkable.get<Transform>(entity);
        auto& velocity = viewNonWalkable.get<Velocity>(entity);
        auto& gravity  = viewNonWalkable.get<ObeysGravity>(entity);

        velocity.y_velocity += gravity.gravityFactor * GRAVITY * blackboard.delta_time;
    }

}



void PhysicsSystem::apply_velocity(Blackboard &blackboard, entt::DefaultRegistry &registry) {

    auto view = registry.view<Velocity, Transform>();


    for (auto entity: view) {
        auto& transform = view.get<Transform>(entity);
        auto& velocity = view.get<Velocity>(entity);
        transform.x += velocity.x_velocity * blackboard.delta_time;
        transform.y += velocity.y_velocity * blackboard.delta_time;

    }
}

void PhysicsSystem::check_collisions(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    // check all dynamic phys objects
    // against all other phys objects


    auto dynamic_view = registry.view<Interactable, Collidable, Transform, Velocity>();

    auto static_view = registry.view<Collidable, Transform>();

    int i = registry.alive();

    auto recorded_collisions = entity_pair_set();

    for (auto d_entity : dynamic_view) {
        auto& interactible = dynamic_view.get<Interactable>(d_entity);
        bool was_grounded = interactible.grounded;
        interactible.grounded = false;

        auto collisions = std::vector<CollisionEntry>();

        for (auto s_entity: static_view) {
            // if the entities are the same
            if (d_entity == s_entity) {
                continue;
            }

            float time, x_norm, y_norm;

            auto& dc = dynamic_view.get<Collidable>(d_entity);
            auto& dp = dynamic_view.get<Transform>(d_entity);
            auto& dv = dynamic_view.get<Velocity>(d_entity);

            auto& sc = static_view.get<Collidable>(s_entity);
            auto& sp = static_view.get<Transform>(s_entity);

            //sets time and normals (if applicable) of collision
            swept_collision(
                dc, dp, dv,
                sc, sp,
                blackboard.delta_time,
                time, x_norm, y_norm
            );

            if (time == 1) {
                // no collision occurred
                continue;
            }
            else {
                //time = std::max<float>(time - 0.01f, 0);

                //if (collision_)

                if (registry.has<Platform>(s_entity)) {
                    if (y_norm == -1 && x_norm == 0) {
                        interactible.grounded = true;
                    }

                    // movement is restricted!
                    float remaining_time = 1 - time;
                    float dot_product = (dv.x_velocity * y_norm + dv.y_velocity * x_norm) * remaining_time;
                    dv.x_velocity = dot_product * y_norm;
                    dv.y_velocity = dot_product * x_norm;

                    //dv.x_velocity *= time;
                    //dv.y_velocity *= time;
                }

            }
        }

        //TODO: move entity
    }
}

bool check_broadphase(
    const Collidable& d_collider,
    const Transform& d_position,
    const Velocity& d_velocity,
    const Collidable& s_collider,
    const Transform& s_position,
    float dt
) {
    return true; //TODO
}

// accepts the relevant components
// "returns" by setting values at referenced locations (time, x_norm, y_norm)
// "time" is a float that, if in range [0, 1] represents the fraction of the step the dynamic object
//    can go before colliding with the static object
//    ( if time is returned as 1, then the dynamic object does NOT collide)
//  if collision WILL happen, populates x_norm and y_norm with the normal vector
//  normal will be with respect to the dynamic collider
void PhysicsSystem::swept_collision(
    const Collidable& d_collider,
    const Transform& d_position,
    const Velocity& d_velocity,
    const Collidable& s_collider,
    const Transform& s_position,
    float dt,
    float& time,
    float& x_norm,
    float& y_norm
) {
    // code here adapted from
    // https://www.gamedev.net/articles/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084

    // d for dynamic; the moving box
    float d_left = d_position.x - d_collider.width / 2;
    float d_right = d_position.x + d_collider.width / 2;
    float d_top = d_position.y - d_collider.height / 2;
    float d_bot = d_position.y + d_collider.height / 2;
    float d_vx = d_velocity.x_velocity * dt;
    float d_vy = d_velocity.y_velocity * dt;

    // s for static; the unmoving box
    float s_left = s_position.x - s_collider.width / 2;
    float s_right = s_position.x + s_collider.width / 2;
    float s_top = s_position.y - s_collider.height / 2;
    float s_bot = s_position.y + s_collider.height / 2;

    // find the distance between the objects on the near and far sides for both x and y
    float x_inv_entry, y_inv_entry, x_inv_exit, y_inv_exit;

    if (d_vx > 0) {
        x_inv_entry = s_left - d_right;
        x_inv_exit = s_right - d_left;
    }
    else {
        x_inv_entry = s_right - d_left;
        x_inv_exit = s_left - d_right;
    }

    if (d_vy > 0) {
        y_inv_entry = s_top - d_bot;
        y_inv_exit = s_bot - d_top;
    }
    else {
        y_inv_entry = s_bot - d_top;
        y_inv_exit = s_top - d_bot;
    }

    // find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
    float x_entry, y_entry, x_exit, y_exit;

    if (d_vx == 0) {
        x_entry = -std::numeric_limits<float>::infinity();
        x_exit = std::numeric_limits<float>::infinity();
    }
    else {
        x_entry = x_inv_entry / d_vx;
        x_exit = x_inv_exit / d_vx;
    }

    if (d_vy == 0) {
        y_entry = -std::numeric_limits<float>::infinity();
        y_exit = std::numeric_limits<float>::infinity();
    }
    else {
        y_entry = y_inv_entry / d_vy;
        y_exit = y_inv_exit / d_vy;
    }

    // find the earliest/latest times of collision
    float entry_time = std::max(x_entry, y_entry);
    float exit_time = std::min(x_exit, y_exit);

    // if there was no collision
    if (   entry_time > exit_time
        || x_entry < 0.0f && y_entry < 0.0f
        || x_entry > 1.0f
        || y_entry > 1.0f
    ) {
        x_norm = 0;
        y_norm = 0;
        time = 1;
        return;
    }

    // otherwise, there WAS a collision
    else {
        // calculate normal of collided surface
        if (x_entry > y_entry)
        {
            if (x_inv_entry < 0.0f)
            {
                x_norm = 1.0f;
                y_norm = 0.0f;
            }
            else
            {
                x_norm = -1.0f;
                y_norm = 0.0f;
            }
        }
        else
        {
            if (y_inv_entry < 0.0f)
            {
                x_norm = 0.0f;
                y_norm = 1.0f;
            }
            else
            {
                x_norm = 0.0f;
                y_norm = -1.0f;
            }
        }

        // return the time of collision
        time = entry_time;
        return;
    }
}
