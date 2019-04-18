//
// Created by cowan on 14/04/19.
//

#include <components/panda.h>
#include <components/timer.h>
#include "powerup_system.h"

void PowerupSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    auto panda_view = registry.view<Panda, Timer, Sprite>();

    for (auto entity : panda_view) {
        auto& panda = panda_view.get<Panda>(entity);
        auto& timer = panda_view.get<Timer>(entity);
        auto& sprite = panda_view.get<Sprite>(entity);
        while (!panda.powerups.empty()) {
            PowerupType type = panda.powerups.front();
            switch (type) {
                case SHIELD_POWERUP:
                    panda.invincible = true;
                    timer.save_watch(SHIELD_TIMER_LABEL, SHIELD_TIMER_LENGTH);
                    sprite.set_color(72 / 256.f, 219 / 256.f, 251 / 256.f);
                    break;
                case VAPE_POWERUP:
                    blackboard.speed_multiplier *= 0.6f;
                    blackboard.post_process_shader = std::make_unique<Shader>(
                            blackboard.shader_manager.get_shader("wave"));
                    timer.save_watch(VAPE_TIMER_LABEL, VAPE_TIMER_LENGTH);
                    break;
                default:
                    break;
            }
            panda.powerups.pop();
        }

        if (timer.exists(SHIELD_TIMER_LABEL)) {
            int val = (int) (((timer.get_target_time(SHIELD_TIMER_LABEL) - timer.get_curr_time()) /
                        SHIELD_TIMER_LENGTH) * 100);
            if (val > 20) {
                if (val % 2 == 0) {
                    sprite.set_color(72 / 256.f, 219 / 256.f, 251 / 256.f); // blue
                } else if (val % 2 == 1) {
                    sprite.set_color(254 / 256.f, 202 / 256.f, 87 / 256.f); // yellow
                }
            } else {
                if (val % 2 == 0) {
                    sprite.set_color(255 / 256.f, 107 / 256.f, 107 / 256.f); // red
                } else if (val % 2 == 1) {
                    sprite.set_color(254 / 256.f, 202 / 256.f, 87 / 256.f); // yellow
                }
            }
            if (timer.is_done(SHIELD_TIMER_LABEL)) {
                panda.invincible = false;
                timer.remove(SHIELD_TIMER_LABEL);
                sprite.set_color(1.f, 1.f, 1.f);
            }
        }
        if (timer.exists(VAPE_TIMER_LABEL)) {
            float val = (((timer.get_target_time(VAPE_TIMER_LABEL) - timer.get_curr_time()) /
                              VAPE_TIMER_LENGTH));
            blackboard.speed_multiplier = fmax(0.5f, 1 - val);
            if(val < 0.1){
                if((int)(val*100) % 2 == 0){
                    blackboard.post_process_shader = std::make_unique<Shader>(
                            blackboard.shader_manager.get_shader("sprite"));
                } else {
                    blackboard.post_process_shader = std::make_unique<Shader>(
                            blackboard.shader_manager.get_shader("wave"));
                }
            }
            if (timer.is_done(VAPE_TIMER_LABEL)) {
                blackboard.post_process_shader = std::make_unique<Shader>(
                        blackboard.shader_manager.get_shader("sprite"));
                timer.remove(VAPE_TIMER_LABEL);
            }
        }
    }
}