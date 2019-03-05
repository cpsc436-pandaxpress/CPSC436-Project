//
// Created by Kenneth William on 2019-01-31.
//

#ifndef PANDAEXPRESS_MOVEABLE_H
#define PANDAEXPRESS_MOVEABLE_H

#include "system.h"
#include "components/panda.h"
#include "scene/scene.h"
#include "components/velocity.h"

class PlayerMovementSystem : public System {
public:
    PlayerMovementSystem(SceneID scene_id);
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry) override;

private:
    const float PANDA_SPEED = 600.f;
    const float PANDA_JUMP_SPEED = 1100.f;
    const float PANDA_OFFSET_SPEED = 200.f;
    const float PANDA_ACCELERATION = 3000.f;

    float time_since_jump = 0.f;
    bool holding_jump = false;
    SceneID scene_id;

    void update_horizontal_scene(Blackboard &blackboard, Velocity &velocity);
    void update_vertical_scene(Blackboard &blackboard, Velocity &velocity);
    void update_boss_scene(Blackboard &blackboard, Velocity &velocity);

};


#endif //PANDAEXPRESS_MOVEABLE_H
