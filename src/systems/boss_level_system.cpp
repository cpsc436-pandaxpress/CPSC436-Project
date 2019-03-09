//
// Created by Prayansh Srivastava on 2019-02-15.
//

#include <util/constants.h>
#include <util/csv_reader.h>
#include <components/transform.h>
#include <components/collidable.h>
#include <components/timer.h>
#include <components/food.h>
#include "boss_level_system.h"

BossLevelSystem::BossLevelSystem() : LevelSystem() {
    init();
}

void BossLevelSystem::init() {
    LevelSystem::init();
    last_col_generated_ = last_col_loaded_ = FIRST_COL_X;
    load_next_chunk(0);
}

void BossLevelSystem::load_next_chunk(int level) {
    std::string level_path = levels_path("");
    std::string levelFile = level_path + "boss_level_" + std::to_string(level) + ".csv";
    CSVReader reader(levelFile);
    std::vector<std::vector<int>> dataList = reader.getData();
    for (int i = 0; i < dataList[0].size(); i++) {
        std::vector<int> col;
        col.reserve(9);
        for (int j = 0; j < 9; j++) {
            col.push_back(dataList[j][i]);
        }
        last_col_loaded_ += CELL_WIDTH;
        chunks_.push(col);
    }
}

// y should range from (-400, 400)
void BossLevelSystem::generate_next_chunk(Blackboard &blackboard,
                                          entt::DefaultRegistry &registry) {
    float off_screen = blackboard.camera.position().x + blackboard.camera.size().x;
    while (last_col_generated_ < off_screen && !chunks_.empty()) { // second condn is safety check
        std::vector<int> col = chunks_.front();
        float y = -400.0f;
        for (int c:col) {
            generateEntity(c, last_col_generated_, y, blackboard, registry);
            y += CELL_HEIGHT;
        }
        last_col_generated_ += CELL_WIDTH;
        chunks_.pop();
    }
}

void BossLevelSystem::destroy_entities(entt::DefaultRegistry &registry) {
    registry.destroy<Food>();
    registry.destroy<Platform>();
}

void BossLevelSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    generate_next_chunk(blackboard, registry);
}