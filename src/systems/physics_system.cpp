//
// Created by cowan on 30/01/19.
//


#include "physics_system.h"
#include <numeric>
#include <components/panda.h>
#include <components/causes_damage.h>
#include <components/health.h>
#include <components/food.h>
#include <components/jacko.h>
#include <components/chases.h>
#include <components/bread.h>
#include <components/llama.h>
#include <graphics/text.h>
#include <components/label.h>
#include "components/platform.h"
#include <graphics/cave_entrance.h>


#include "util/entity_pairs.h"
#include "util/scene_helper.h"

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
    /***
     * Applying gravity to objects that can't walk on platforms
     ***/

    auto viewNonWalkable = registry.view<ObeysGravity, Transform, Velocity>();

    for (auto entity: viewNonWalkable) {

        auto& transform = viewNonWalkable.get<Transform>(entity);
        auto& velocity = viewNonWalkable.get<Velocity>(entity);
        auto& gravity  = viewNonWalkable.get<ObeysGravity>(entity);


        if (registry.has<Interactable>(entity)) {
            auto& interactible = view.get<Interactable>(entity);
            velocity.y_velocity += gravity.gravityFactor * GRAVITY * blackboard.delta_time;
        }
        else {
            velocity.y_velocity += gravity.gravityFactor * GRAVITY * blackboard.delta_time;
         }
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

    auto recorded_collisions = entity_pair_set();

    for (auto d_entity : dynamic_view) {
        auto& interactible = dynamic_view.get<Interactable>(d_entity);

        interactible.grounded = false;

        auto no_collisions = false;

        // check for collisions and adjust velocity
        // until no more collisions
        while (!no_collisions) {
            auto collisions = std::vector<CollisionEntry>();

            auto &dc = dynamic_view.get<Collidable>(d_entity);
            auto &dp = dynamic_view.get<Transform>(d_entity);
            auto &dv = dynamic_view.get<Velocity>(d_entity);

            for (auto s_entity: static_view) {
                // if the entities are the same
                if (d_entity == s_entity) {
                    continue;
                }
                //if the entities already collided this frame
                if (ordered_pair_check(recorded_collisions, d_entity, s_entity)) {
                    continue;
                }

                float time, x_norm, y_norm;

                auto &sc = static_view.get<Collidable>(s_entity);
                auto &sp = static_view.get<Transform>(s_entity);
                auto null_v = Velocity(0, 0);
                auto& sv = null_v;
                if (registry.has<Velocity>(s_entity)) {
                    sv = registry.get<Velocity>(s_entity);
                }

                //sets time and normals (if applicable) of collision

                swept_collision(
                    dc, dp, dv,
                    sc, sp, sv,
                    blackboard.delta_time,
                    time, x_norm, y_norm
                );

                if (time == 1) {
                    if (static_collision(dc, dp, sc, sp, 0)) {
                        time = 0;
                        x_norm = 0;
                        y_norm = 0;
                    }
                }

                collisions.emplace_back(
                    s_entity,
                    vec2{x_norm, y_norm},
                    time
                );
            }

            //sort collisions by first-occurring
            auto sorted_collisions = std::vector<CollisionEntry>();

            for (auto entry : collisions) {
                if (entry.time == 1) {
                    // no collision occurred
                    continue;
                }
                auto inserted = false;
                for (auto iter = sorted_collisions.begin(); iter != sorted_collisions.end(); iter++) {
                    if (entry.time <= iter->time) {
                        sorted_collisions.insert(iter, entry);
                        inserted = true;
                        break;
                    }
                }
                if (!inserted) {

                    sorted_collisions.push_back(entry);
                }
            }

            for (auto entry : sorted_collisions) {
                if (registry.has<Platform>(entry.entity)) {

                    recorded_collisions.insert(uint_pair(d_entity, entry.entity));

                    if (entry.normal.x == 0 && entry.normal.y == 0) {
                        // static collision; ignore for platforms
                        continue;
                    }

                    auto& platform = registry.get<Platform>(entry.entity);

                    if (platform.one_way) {
                        if (entry.normal.y != -1) {
                            continue;
                        }
                        interactible.grounded = true;
                    }
                    else {
                        if (entry.normal.y == -1) {
                            interactible.grounded = true;
                        }
                    }

                    // movement is restricted!
                    float remaining_time = 1 - entry.time;
                    float dot_product = (dv.x_velocity * entry.normal.y + dv.y_velocity * entry.normal.x) * remaining_time;
                    dv.x_velocity = dv.x_velocity * entry.time + dot_product * entry.normal.y;
                    dv.y_velocity = dv.y_velocity * entry.time + dot_product * entry.normal.x;

                    // stop at first blocking collision
                    break;

                }
                else {
                    //handle non-blocking collisions
                    recorded_collisions.insert(uint_pair(d_entity, entry.entity));


                    // check for causing damage to the panda
                    if ( registry.has<CausesDamage>(entry.entity)
                        && registry.has<Panda>(d_entity)
                    ) {
                        auto& cd = registry.get<CausesDamage>(entry.entity);
                        auto& health = registry.get<Health>(d_entity);
                        auto& panda = registry.get<Panda>(d_entity);
                        auto& transform = registry.get<Transform>(d_entity);
                        if (entry.normal.x == 0 && entry.normal.y == 0) {
                            panda.hurt = true;
                        }
                        else if (cd.normal_matches_mask(entry.normal.x, entry.normal.y)) {
                            panda.hurt = true;
                        }
                    }
                    else if ( registry.has<CausesDamage>(d_entity)
                              && registry.has<Panda>(entry.entity)
                        ) {
                        auto& cd = registry.get<CausesDamage>(d_entity);
                        auto& health = registry.get<Health>(entry.entity);
                        auto& panda = registry.get<Panda>(entry.entity);
                        auto& transform = registry.get<Transform>(entry.entity);

                        if (entry.normal.x == 0 && entry.normal.y == 0) {
                            panda.hurt = true;
                        }
                        if (cd.normal_matches_mask(-entry.normal.x, -entry.normal.y)) {
                            panda.hurt = true;
                        }
                    }

                    // check for the panda causing damage
                    if ( registry.has<Health>(entry.entity)
                         && registry.has<Panda>(d_entity)
                    ) {
                        auto& cd = registry.get<CausesDamage>(d_entity);
                        auto& panda = registry.get<Panda>(d_entity);
                        auto& transform = registry.get<Transform>(d_entity);
                        auto& health = registry.get<Health>(entry.entity);
                        if (cd.normal_matches_mask(-entry.normal.x, -entry.normal.y)
                        && !panda.invincible){
                            //do damage
                            health.health_points -= cd.hp;

                            if (entry.normal.x != 0) {
                                dv.x_velocity = 700 * entry.normal.x;
                            }
                            if (entry.normal.y != 0) {
                                dv.y_velocity = 700 * entry.normal.y;
                            }

                            if (registry.has<Jacko>(entry.entity)) {
                                // panda is hitting jacko
                                auto& jacko = registry.get<Jacko>(entry.entity);
                                auto& chases = registry.get<Chases>(entry.entity);
                                if (health.health_points <= 0) {
                                    registry.remove<Interactable>(entry.entity);
                                    registry.remove<Chases>(entry.entity);
                                    registry.assign<ObeysGravity>(entry.entity);
                                }
                                else {
                                    chases.evading = true;
                                }
                            }
                            //else if to exclude jacko from normal dying stuff
                            else if (health.health_points <= 0) {
                                //normal way to kill stuff
                                if (registry.has<Interactable>(entry.entity)) {
                                    registry.remove<Interactable>(entry.entity);
                                }
                                if (registry.has<Bread>(entry.entity)) {
                                    blackboard.score += BREAD_KILL_POINTS;
                                    std::string str = "+" + std::to_string(BREAD_KILL_POINTS);
                                    create_label_text(blackboard, registry,
                                                      vec2{transform.x, transform.y - 100.f},
                                                      str.c_str());
                                } else if (registry.has<Llama>(entry.entity)) {
                                    blackboard.score += LLAMA_KILL_POINTS;
                                    std::string str = "+" + std::to_string(LLAMA_KILL_POINTS);
                                    create_label_text(blackboard, registry,
                                                      vec2{transform.x, transform.y - 100.f},
                                                      str.c_str());
                                }
                            }
                        }
                    }

                    //check for food
                    if ( registry.has<Food>(entry.entity)) {
                        if (registry.has<Panda>(d_entity)) {
                            auto &panda = registry.get<Panda>(d_entity);
                            auto &health = registry.get<Health>(d_entity);
                            if (panda.alive && health.health_points < health.max_health) {
                                health.health_points++;
                            }
                            registry.destroy(entry.entity);

                        } else if (registry.has<Food>(entry.entity) && registry.has<Jacko>(d_entity)) {
                            auto &health = registry.get<Health>(d_entity);
                            if (health.health_points < health.max_health) {
                                health.health_points++;
                            }
                            registry.destroy(entry.entity);
                        }
                    }

                    /*if ( registry.has<CaveEntrance>(entry.entity)) {
                        if (registry.has<Panda>(d_entity)) {
                            blackboard.camera.transition_ready = true;
                        }
                    }*/
                }
            }

            if (sorted_collisions.empty()) {
                no_collisions = true;
            }
        }

    }
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
    const Velocity& s_velocity,
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
//    float d_vx = d_velocity.x_velocity * dt;
//    float d_vy = d_velocity.y_velocity * dt;


    float d_vx = (d_velocity.x_velocity - s_velocity.x_velocity) * dt;
    float d_vy = (d_velocity.y_velocity - s_velocity.y_velocity) * dt;

    // s for static; the unmoving box
    float s_left = s_position.x - s_collider.width / 2;
    float s_right = s_position.x + s_collider.width / 2;
    float s_top = s_position.y - s_collider.height / 2;
    float s_bot = s_position.y + s_collider.height / 2;



    //first check broadphase
    float d_min_x = std::min<float>(d_left, d_left + d_vx);
    float d_max_x = std::max<float>(d_right, d_right + d_vx);
    float d_min_y = std::min<float>(d_top, d_top + d_vy);
    float d_max_y = std::max<float>(d_bot, d_bot + d_vy);

    if (   d_min_x > s_right
        || d_max_x < s_left
        || d_min_y > s_bot
        || d_max_y < s_top
    ) {
        time = 1;
        x_norm = 0;
        y_norm = 0;
        return;
    }

    // find the distance between the objects on the near and far sides for both x and y
    float x_inv_entry, y_inv_entry, x_inv_exit, y_inv_exit;

    if (d_vx >= 0) {
        x_inv_entry = s_left - d_right;
        x_inv_exit = s_right - d_left;
    }
    else {
        x_inv_entry = s_right - d_left;
        x_inv_exit = s_left - d_right;
    }

    if (d_vy >= 0) {
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
        || (x_entry < 0.0f && y_entry < 0.0f)
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
        if (x_entry > y_entry) {
            if (abs(y_inv_entry) < 1) {
                x_norm = 0;
                y_norm = 0;
                time = 1;
                return;
            }
            else if (x_inv_entry == 0.0f) {
                if (d_vx < 0) {
                    x_norm = 1;
                }
                else {
                    x_norm = -1;
                }
                y_norm = 0;
            }
            else if (x_inv_entry < 0.0f)
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
        else {
            if (abs(x_inv_entry) < 1) {
                x_norm = 0;
                y_norm = 0;
                time = 1;
                return;
            }
            else if (y_inv_entry == 0.0f) {
                if (d_vy < 0) {
                    y_norm = 1;
                }
                else {
                    y_norm = -1;
                }
                x_norm = 0;
            }
            else if (y_inv_entry < 0.0f)
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

bool PhysicsSystem::static_collision(
    const Collidable &d_collider,
    const Transform &d_position,
    const Collidable &s_collider,
    const Transform &s_position,
    float buffer
) {
    float d_left = d_position.x - d_collider.width / 2;
    float d_right = d_position.x + d_collider.width / 2;
    float d_top = d_position.y - d_collider.height / 2;
    float d_bot = d_position.y + d_collider.height / 2;


    float s_left = s_position.x - s_collider.width / 2;
    float s_right = s_position.x + s_collider.width / 2;
    float s_top = s_position.y - s_collider.height / 2;
    float s_bot = s_position.y + s_collider.height / 2;


    bool no_collide =
           d_left > s_right + buffer
        || s_left > d_right + buffer
        || d_bot < s_top + buffer
        || s_bot < d_top + buffer;

    return !no_collide;
}
