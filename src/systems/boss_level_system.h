//
// Created by Prayansh Srivastava on 2019-02-15.
//


#ifndef PANDAEXPRESS_BOSS_LEVEL_SYSTEM_H
#define PANDAEXPRESS_BOSS_LEVEL_SYSTEM_H

#include "level/level_system.h"

class BossLevelSystem : public LevelSystem {
    void load_next_chunk();

    void generate_next_chunk(Blackboard &blackboard, entt::DefaultRegistry &registry);

    const float FIRST_COL_X = -200;
    float last_col_generated_, last_col_loaded_;

public:

    BossLevelSystem();

    void init();

    void update(Blackboard &blackboard, entt::DefaultRegistry &registry);

    void destroy_entities(entt::DefaultRegistry &registry);

    void destroy_off_screen(entt::DefaultRegistry &registry, float x);

    void update_falling_platforms(Blackboard &blackboard, entt::DefaultRegistry &registry);
};

#endif //PANDAEXPRESS_BOSS_LEVEL_SYSTEM_H