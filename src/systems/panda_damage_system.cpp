//
// Created by Prayansh Srivastava on 2019-03-04.
//

#include <components/panda.h>
#include <components/health.h>
#include <components/timer.h>
#include <components/velocity.h>
#include <components/interactable.h>
#include "panda_damage_system.h"

PandaDamageSystem::PandaDamageSystem() {

}

void PandaDamageSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    auto view = registry.view<Panda, Health, Timer, Velocity, Interactable>();

    for (auto entity: view) {
        //get the sprite
        auto &panda = view.get<Panda>(entity);
        auto &timer = view.get<Timer>(entity);
        auto &health = view.get<Health>(entity);
        auto &velocity = view.get<Velocity>(entity);
        auto &interactable = view.get<Interactable>(entity);
//        printf("Panda Hurt: %d, hurt: %d, invincible: %d\n", health.healthPoints,
//               (panda.hurt) ? 1 : -1, (panda.invincible) ? 1 : -1);
        if(panda.recovering && interactable.grounded){
            panda.recovering = false;
        }
        if (panda.hurt && !panda.invincible) {
            // Do all damage calcs here
            health.healthPoints--;
            // Make Panda Bounce TODO
            velocity.x_velocity = -100.f;// tmp reaction
            velocity.y_velocity = -1000.f;// tmp reaction
            interactable.grounded = false;

            // Prevent Player control until hit ground
            panda.recovering = true;

            // Make invincible
            panda.invincible = true;
            timer.save_watch(DMG_TIMER_LABEL, DMG_INVINCIBLE_TIMER);
        }
        // Reset Panda Invincibility timer
        if (timer.status(DMG_TIMER_LABEL) == DONE) {
            panda.invincible = false;
            timer.remove(DMG_TIMER_LABEL);
        }

        if (health.healthPoints < 0) {
            panda.alive = false;
        }
        panda.hurt = false; // Clear DMG flag
    }
}
