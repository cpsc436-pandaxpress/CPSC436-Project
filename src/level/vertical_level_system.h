//
// Created by cowan on 17/02/19.
//

#ifndef PANDAEXPRESS_VERTICAL_LEVEL_SYSTEM_H
#define PANDAEXPRESS_VERTICAL_LEVEL_SYSTEM_H


#include <util/blackboard.h>
#include <entt/entity/registry.hpp>
#include <components/timer.h>
#include <scene/scene_mode.h>
#include "level_system.h"
#include "level.h"

class VerticalLevelSystem : public LevelSystem {
private:
    void load_next_chunk();
    void load_next_chunk(int level);

    void generate_next_chunk(Blackboard &blackboard, entt::DefaultRegistry &registry);

    void destroy_off_screen(entt::DefaultRegistry &registry, float max_y);

    const float FIRST_ROW_Y = 300.f;
    const float COL_X_OFFSET = -750.f;
    const int MIN_DIFFICULTY_EASY = 3;
    const int MAX_DIFFICULTY_EASY = 9;
    const int MIN_DIFFICULTY_HARD = 15;
    const int MAX_DIFFICULTY_HARD = 20;
    const int DIFFICULTY_RANGE = 2;
    const float LEVEL_UP_INTERVAL = 5;
    const std::string LEVEL_UP_LABEL = "level_up";

    const int END_LEVEL = 50;

    int min_difficulty;
    int max_difficulty;

    float last_row_generated_, last_row_loaded_;
    int difficulty;

    Timer difficulty_timer;

    SceneMode mode_;

    std::unordered_map<int, Level> levels;

public:

    VerticalLevelSystem();

    void init(SceneMode mode, entt::DefaultRegistry &registry);

    void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override;

    void destroy_entities(entt::DefaultRegistry &registry) override;

    void generate_end_level();
};


#endif //PANDAEXPRESS_VERTICAL_LEVEL_SYSTEM_H
