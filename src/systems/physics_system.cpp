//
// Created by cowan on 30/01/19.
//
#include "components/obeys_gravity.h"
#include "components/collidable.h"
#include "components/interactable.h"
#include "components/velocity.h"
#include "physics_system.h"
#include "components/panda.h"
#include "components/transform.h"
#include <iostream>
using namespace std;


PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::update(Blackboard& blackboard, entt::DefaultRegistry& registry) {

    applyGravity(blackboard, registry);
    applyVelocity(blackboard, registry);

}

void PhysicsSystem::applyGravity(Blackboard& blackboard, entt::DefaultRegistry& registry){



    /***
     * Applying gravity to objects that can walk on platforms
     ***/

    auto view = registry.view<ObeysGravity, Interactable, Transform, Velocity>();

    for (auto entity: view) {

        auto& transform = view.get<Transform>(entity);
        auto& walkable = view.get<Interactable>(entity);
        auto& velocity = view.get<Velocity>(entity);
        auto& gravity  = view.get<ObeysGravity>(entity);
        if (! walkable.grounded) {
            velocity.y_velocity += gravity.gravityConstant;
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

        velocity.y_velocity += gravity.gravityConstant;






    }

}

void PhysicsSystem::applyVelocity(Blackboard& blackboard, entt::DefaultRegistry& registry) {

    auto view = registry.view<Velocity, Transform>();


    for (auto entity: view) {
        auto& transform = view.get<Transform>(entity);
        auto& velocity = view.get<Velocity>(entity);
        transform.x += velocity.x_velocity;
        transform.y += velocity.y_velocity;

    }


}