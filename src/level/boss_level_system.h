//
// Created by Prayansh Srivastava on 2019-02-15.
//


#ifndef PANDAEXPRESS_BOSS_LEVEL_SYSTEM_H
#define PANDAEXPRESS_BOSS_LEVEL_SYSTEM_H

#include "level/level_system.h"
#include "level.h"

class BossLevelSystem : public LevelSystem {
    void generate_level(Blackboard &blackboard, entt::DefaultRegistry &registry);
    void load_next_chunk(int level);
    void generate_next_chunk(Blackboard &blackboard, entt::DefaultRegistry &registry) override;

    const float FIRST_COL_X = -800.f;
    const float FIRST_ROW_Y = -400.f;
    Level level_;
    bool generated_;

public:

    BossLevelSystem();

    void init();

    void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;

    void destroy_entities(entt::DefaultRegistry &registry);
};

#endif //PANDAEXPRESS_BOSS_LEVEL_SYSTEM_H