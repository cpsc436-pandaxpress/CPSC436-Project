//
// Created by cowan on 30/01/19.
//

#ifndef PANDAEXPRESS_PHYSICS_SYSTEM_H
#define PANDAEXPRESS_PHYSICS_SYSTEM_H


#include <Box2D.h>
#include <unordered_map>
#include <unordered_set>
#include "system.h"
#include "components/obeys_gravity.h"
#include "components/collidable.h"
#include "components/interactable.h"
#include "components/velocity.h"
#include "components/transform.h"

static const int BREAD_KILL_POINTS = 50;
static const int LLAMA_KILL_POINTS = 150;

typedef std::pair<uint32_t, uint32_t> uint_pair;

struct PairHash {
    inline std::size_t operator()(const uint_pair& val) const {
        auto a = val.first;
        auto b = val.second;
        auto c = a + b;
        return c * (c + 1) / 2 + a;
    }
};

struct CollisionEntry {
    uint32_t e1, e2;
    vec2 normal, d_velocity;
    float time;

    // normal will be on e1
    CollisionEntry(
        uint32_t e1,
        uint32_t e2,
        vec2 normal,
        float time
    ) :
        e1(e1),
        e2(e2),
        normal(normal),
        time(time)
    {}
};

class PhysicsSystem : public System, b2ContactListener, b2ContactFilter {
private:
    static constexpr float GRAVITY = 2500.f;
    static constexpr float METER = 100.f;
    b2World world_;
    std::vector<CollisionEntry> collisions_;
    std::unordered_map<uint32_t, b2Body* > body_lookup_;

public:

    PhysicsSystem();
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;

    /// Called when two fixtures begin to touch.
    virtual void BeginContact(b2Contact* contact) override;

    /// Called when two fixtures cease to touch.
    virtual void EndContact(b2Contact* contact) override;

    virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override;

private:

    void maintain(entt::DefaultRegistry& registry);
    void handle_collisions(entt::DefaultRegistry& registry);
    void set_transforms(entt::DefaultRegistry& registry);
    b2Body* create_body_for(void* data, const Collidable& collidable, const Transform& transform, bool is_static, bool use_circle);

    void apply_gravity(Blackboard &blackboard, entt::DefaultRegistry &registry);
    void apply_velocity(Blackboard &blackboard, entt::DefaultRegistry &registry);

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

    float pix_to_meters(float pixels) {
        return pixels / METER;
    }

    float meters_to_pix(float meters) {
        return meters * METER;
    }
};


#endif //PANDAEXPRESS_PHYSICS_SYSTEM_H
