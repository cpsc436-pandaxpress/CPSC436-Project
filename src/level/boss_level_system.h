//
// Created by Prayansh Srivastava on 2019-02-15.
//


#ifndef PANDAEXPRESS_BOSS_LEVEL_SYSTEM_H
#define PANDAEXPRESS_BOSS_LEVEL_SYSTEM_H

#include "level/level_system.h"
#include "scene/scene_mode.h"
#include "level.h"

class BossLevelSystem : public LevelSystem {
private:
    void generate_level(Blackboard &blackboard, entt::DefaultRegistry &registry);

    const float FIRST_COL_X = -800.f;
    const float FIRST_ROW_Y = -400.f;
    Level level_;
    bool generated_;
    SceneMode mode_;

public:

    BossLevelSystem();

    void init() override;

    void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;
};

#endif //PANDAEXPRESS_BOSS_LEVEL_SYSTEM_H