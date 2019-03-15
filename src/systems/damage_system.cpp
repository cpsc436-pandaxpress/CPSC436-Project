//
// Created by Prayansh Srivastava on 2019-03-14.
//

#include <components/health.h>
#include <components/panda.h>
#include <components/timer.h>
#include <components/velocity.h>
#include <components/interactable.h>
#include <components/bread.h>
#include <components/obeys_gravity.h>
#include <components/chases.h>
#include "damage_system.h"

DamageSystem::DamageSystem() {

}

void DamageSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    auto health_views = registry.view<Health>();
    for (auto entity: health_views) {
        auto health = health_views.get(entity);
        if (health.hurt) {
            if (registry.has<Panda>(entity)) {
                handle_panda_damage(entity, blackboard, registry);
            } else if (registry.has<Bread>(entity)) {
                handle_bread_damage(entity, blackboard, registry);
            } else if (registry.has<Bread>(entity)) {
                handle_jacko_damage(entity, blackboard, registry);
            }
            health.hurt = false;
        }
    }
}

void DamageSystem::handle_panda_damage(unsigned int entity, Blackboard &blackboard,
                                       entt::DefaultRegistry &registry) {
    auto &panda = registry.get<Panda>(entity);
    auto &timer = registry.get<Timer>(entity);
    auto &health = registry.get<Health>(entity);
    auto &velocity = registry.get<Velocity>(entity);
    auto &interactable = registry.get<Interactable>(entity);
    if (panda.recovering && interactable.grounded) {
        panda.recovering = false;
    }
    if (health.hurt && !panda.invincible) {
        // Do all damage calcs here
        health.healthPoints--;
        blackboard.soundManager.playSFX(SFX_PANDA_HURT);
        // Make Panda Bounce
        if (panda.facingRight) {
            velocity.x_velocity = -PANDA_DMG_REACTION_X;
        } else {
            velocity.x_velocity = PANDA_DMG_REACTION_X;
        }
        velocity.y_velocity = PANDA_DMG_REACTION_Y;// tmp reaction
        interactable.grounded = false;

        // Prevent Player control until hit ground
        panda.recovering = true;

        // Make invincible
        panda.invincible = true;
        timer.save_watch(PANDA_DMG_TIMER_LABEL, PANDA_DMG_INVINCIBLE_TIMER);
    }
    // Reset Panda Invincibility timer
    if (timer.exists(PANDA_DMG_TIMER_LABEL) && timer.is_done(PANDA_DMG_TIMER_LABEL)) {
        panda.invincible = false;
        timer.remove(PANDA_DMG_TIMER_LABEL);
    }

    if (health.healthPoints <= 0) {
        panda.alive = false;
    }
}

void DamageSystem::handle_bread_damage(unsigned int bread_entity, Blackboard &blackboard,
                                       entt::DefaultRegistry &registry) {
    auto health = registry.get<Health>(bread_entity);
    if (health.healthPoints <= 0) {
        registry.remove<Interactable>(bread_entity);
        auto &sprite = registry.get<Sprite>(bread_entity);
        sprite.set_color(1.0, 0.0, 0.0);
    }
}

void DamageSystem::handle_jacko_damage(unsigned int jacko_entity, Blackboard &blackboard,
                                       entt::DefaultRegistry &registry) {
    auto health = registry.get<Health>(jacko_entity);
    if (health.healthPoints <= 0) {
        registry.remove<Interactable>(jacko_entity);
        registry.remove<Chases>(jacko_entity);
        registry.assign<ObeysGravity>(jacko_entity);
    } else { // Not dead run away from panda!
        auto &chases = registry.get<Chases>(jacko_entity);
        chases.evading = true; // TODO maybe evading should be using a timer?
    }
}

