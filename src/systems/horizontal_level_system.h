//
// Created by Prayansh Srivastava on 2019-02-15.
//
#include "level_system.h"
#include "components/timer.h"

#ifndef PANDAEXPRESS_HORIZONTAL_LEVEL_SYSTEM_H
#define PANDAEXPRESS_HORIZONTAL_LEVEL_SYSTEM_H

#endif //PANDAEXPRESS_HORIZONTAL_LEVEL_SYSTEM_H

class HorizontalLevelSystem : public LevelSystem {
    void load_next_chunk();
    void load_next_chunk(int level);

    void generate_next_chunk(Blackboard &blackboard, entt::DefaultRegistry &registry);

    void destroy_off_screen(entt::DefaultRegistry &registry, float x);

    const float FIRST_COL_X = -200;
    const int MIN_DIFFICULTY = 2;
    const int MAX_DIFFICULTY = 9;
    const int DIFFICULTY_RANGE = 4;
    const float LEVEL_UP_INTERVAL = 10;
    const std::string LEVEL_UP_LABEL = "level_up";

    float last_col_generated_, last_col_loaded_;
    int difficulty;

    Timer difficulty_timer;

    SceneMode mode_;

public:

    HorizontalLevelSystem();

    void init();

    void update(Blackboard &blackboard, entt::DefaultRegistry &registry);

    void destroy_entities(entt::DefaultRegistry &registry);

    void set_mode(SceneMode mode);
};