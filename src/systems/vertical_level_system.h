//
// Created by cowan on 17/02/19.
//

#ifndef PANDAEXPRESS_VERTICAL_LEVEL_SYSTEM_H
#define PANDAEXPRESS_VERTICAL_LEVEL_SYSTEM_H


#include <util/blackboard.h>
#include <entt/entity/registry.hpp>
#include <components/timer.h>
#include "level_system.h"

class VerticalLevelSystem : public LevelSystem {
private:
    void load_next_chunk();
    void load_next_chunk(int level);

    void generate_next_chunk(Blackboard &blackboard, entt::DefaultRegistry &registry);

    void destroy_off_screen(entt::DefaultRegistry &registry, float max_y);

    const float FIRST_ROW_Y = 300.f;
    const float COL_X_OFFSET = -750.f;
    const int MIN_DIFFICULTY = 3;
    const int MAX_DIFFICULTY = 11;
    const float LEVEL_UP_INTERVAL = 10;
    const std::string LEVEL_UP_LABEL = "level_up";

    float last_row_generated_, last_row_loaded_;
    int difficulty;

    Timer difficulty_timer;

public:

    VerticalLevelSystem();

    void init();

    void update(Blackboard &blackboard, entt::DefaultRegistry &registry);

    void destroy_entities(entt::DefaultRegistry &registry);

    void update_projectiles(Blackboard &blackboard, entt::DefaultRegistry &registry);
};


#endif //PANDAEXPRESS_VERTICAL_LEVEL_SYSTEM_H
