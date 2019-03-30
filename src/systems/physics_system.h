//
// Created by cowan on 30/01/19.
//

#ifndef PANDAEXPRESS_PHYSICS_SYSTEM_H
#define PANDAEXPRESS_PHYSICS_SYSTEM_H

static const float BREAD_KILL_POINTS = 100.f;

static const float LLAMA_KILL_POINTS = 300.f;

#include "system.h"
#include "components/obeys_gravity.h"
#include "components/collidable.h"
#include "components/interactable.h"
#include "components/velocity.h"
#include "components/transform.h"

struct CollisionEntry {
    uint32_t entity;
    vec2 normal, d_velocity;
    float time;


    CollisionEntry(
        uint32_t entity,
        vec2 normal,
        float time
    ) :
        entity(entity),
        normal(normal),
        time(time)
    {}
};

class PhysicsSystem : public System {
private:
    static constexpr float GRAVITY = 2500.f;
public:

    PhysicsSystem();
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;

private:
    void apply_gravity(Blackboard &blackboard, entt::DefaultRegistry &registry);
    void apply_velocity(Blackboard &blackboard, entt::DefaultRegistry &registry);

    //doesn't handle rotation cuz that shit is hard
    void check_collisions(Blackboard &blackboard, entt::DefaultRegistry &registry);
    void swept_collision(
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
    );
    bool static_collision(
        const Collidable &d_collider,
        const Transform &d_position,
        const Collidable &s_collider,
        const Transform &s_position,
        float buffer
    );

    void generate_text(Blackboard &blackboard, entt::DefaultRegistry &registry, vec2 pos,
                       const char *text);
};


#endif //PANDAEXPRESS_PHYSICS_SYSTEM_H
