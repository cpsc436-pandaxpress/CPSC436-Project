//
// Created by Prayansh Srivastava on 2019-02-15.
//

#include <util/constants.h>
#include <util/csv_reader.h>
#include <components/transform.h>
#include <components/collidable.h>
#include <components/timer.h>
#include "boss_level_system.h"

BossLevelSystem::BossLevelSystem() : LevelSystem() {

}


void BossLevelSystem::init(entt::DefaultRegistry &registry)  {
    LevelSystem::init(registry);
    //level_ = Level::load_from_path("jacko_level.csv");
    level_ = Level::load_from_path("dracula_level.csv");

    generated_ = false;
}

void BossLevelSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    if (!generated_) {
        generate_level(blackboard, registry);
        generated_ = true;
    }
}

void BossLevelSystem::generate_level(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    for (size_t i = 0; i < level_.width(); i++) {
        float x = FIRST_COL_X + (float) CELL_WIDTH * i;
        for (size_t j = 0; j < level_.height(); j++) {
            float y = FIRST_ROW_Y + (float) CELL_HEIGHT * j;

            generateEntity(level_.get_tile_at(i, j), x, y, blackboard, registry, STORY_EASY);
        }
    }
}