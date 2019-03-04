//
// Created by Becca Roth on 2019-03-03.
//

#ifndef PANDAEXPRESS_ENEMY_SYSTEM_H
#define PANDAEXPRESS_ENEMY_SYSTEM_H
#include "system.h"
#include "util/constants.h"
#include "components/ghost.h"
#include "components/bread.h"
#include "components/llama.h"
#include "components/spit.h"
#include "systems/ghost_movement_system.h"
#include "systems/level_system.h"
#include "components/velocity.h"
#include "components/transform.h"
#include "components/collidable.h"
#include "components/timer.h"

class EnemySystem {
private:
    GhostMovementSystem ghost_movement_system;
    const float BREAD_SPEED = 50.f;
    const float PROJECTILE_SPEED_X = -300.f;
    const float PROJECTILE_SPEED_Y = 10.f;
    const std::string SPIT_TIMER_LABEL = "spit";

    void generateProjectile(float x, float y, bool spit_left, Blackboard &blackboard, entt::DefaultRegistry &registry);


public:
    EnemySystem();
    virtual void update(Blackboard& blackboard, entt::DefaultRegistry& registry, SceneID sceneid);
};


#endif //PANDAEXPRESS_ENEMY_SYSTEM_H
