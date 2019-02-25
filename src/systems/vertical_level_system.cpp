//
// Created by cowan on 17/02/19.
//

#include <util/csv_reader.h>
#include <util/constants.h>
#include "vertical_level_system.h"
#include <iostream>

VerticalLevelSystem::VerticalLevelSystem(): LevelSystem() {
    last_row_placed_ = FIRST_ROW_Y;
}

void VerticalLevelSystem::load_next_chunk() {
    std::string level_path = levels_path("");
    int levelN = rng_.nextInt(0, 4);
    std::string levelFile = level_path + "vlevel_" + std::to_string(levelN) + ".csv";
    CSVReader reader(levelFile);
    std::vector<std::vector<int>> dataList = reader.getData();
    for (int i = dataList.size() - 1; i >= 0; i--) {
        auto line = dataList[i];
        std::vector<int> row;
        row.reserve(line.size());
        for (int j = 0; j < line.size(); j++) {
            row.push_back(dataList[i][j]);
        }
        chunks_.push(row);
    }
}

void VerticalLevelSystem::generate_next_chunk(Blackboard &blackboard,
                                                entt::DefaultRegistry &registry) {
    while (!chunks_.empty()) {
        std::vector<int> col = chunks_.front();
        float x = COL_X_OFFSET;
        for (int c:col) {
            generateEntity(c, x, last_row_placed_, blackboard, registry);
            x += CELL_WIDTH;
        }
        last_row_placed_ -= CELL_HEIGHT;
        chunks_.pop();
    }
}

void VerticalLevelSystem::destroy_entities(entt::DefaultRegistry &registry) {
    registry.destroy<Platform>();
    registry.destroy<Llama>();
    registry.destroy<Spit>();
    registry.destroy<Bread>();
    last_row_placed_ = FIRST_ROW_Y;
}

void VerticalLevelSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    float max_y =
            blackboard.camera.position().y + blackboard.camera.size().y; // some distance off camera
    float min_y =
            blackboard.camera.position().y - blackboard.camera.size().y; // some distance off camera
    if (last_row_placed_ > min_y) {
        load_next_chunk();
    }
    destroy_off_screen(registry, max_y);
    generate_next_chunk(blackboard, registry);
}

void VerticalLevelSystem::destroy_off_screen(entt::DefaultRegistry &registry, float y) {
    auto view = registry.view<Platform, Transform>();
    for (uint32_t entity: view) {
        auto &transform = view.get<Transform>(entity);
        if (transform.y > y) {
            registry.destroy(entity);
        }
    }
}