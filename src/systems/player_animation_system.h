//
// Created by Avery Brown on 2019-02-25.
//

#ifndef PANDAEXPRESS_PLAYER_ANIMATION_SYSTEM_H
#define PANDAEXPRESS_PLAYER_ANIMATION_SYSTEM_H
#include "system.h"
#include "components/panda.h"

class PlayerAnimationSystem : public System {
public:
    PlayerAnimationSystem();
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;

private:
    const vec2 standRuv1 = {0, 0};
    const vec2 standRuv2 = {0.32, 0.25};
    const vec2 walkR1uv1 = {0.33, 0};
    const vec2 walkR1uv2 = {0.65, 0.25};
    const vec2 walkR2uv1 = {0.66, 0};
    const vec2 walkR2uv2 = {1, 0.25};
    const vec2 walkR3uv1 = {0, 0.26};
    const vec2 walkR3uv2 = {0.32, 0.50};
    const vec2 walkR4uv1 = {0.66, 0.26};
    const vec2 walkR4uv2 = {1, 0.50};
    const vec2 walkL1uv1 = {0, 0.51};
    const vec2 walkL1uv2 = {0.32, 0.75};
    const vec2 walkL2uv1 = {0.325, 0.51};
    const vec2 walkL2uv2 = {0.66, 0.75};
    const vec2 standLuv1 = {0.66, 0.50};
    const vec2 standLuv2 = {1, 0.75};
    const vec2 jumpR1uv1 = {0, 0.75};
    const vec2 jumpR1uv2 = {0.32, 1};
    const vec2 jumpRfallinguv1 = {0.33, 0.75};
    const vec2 jumpRfallinguv2 = {0.65, 1};
    const vec2 jumpLfallinguv1 = {0.33, 0.26};
    const vec2 jumpLfallinguv2 = {0.66, 0.50};
    const vec2 jumpL1uv1 = {0.66, 0.75};
    const vec2 jumpL1uv2 = {1, 1};

    bool holding_jump = false;
    float time_since_jump = 0.f;
    bool direction_left = false;


};

#endif //PANDAEXPRESS_PLAYER_ANIMATION_SYSTEM_H
