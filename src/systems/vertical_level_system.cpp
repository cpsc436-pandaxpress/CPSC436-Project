//
// Created by cowan on 17/02/19.
//

#include <util/csv_reader.h>
#include <util/constants.h>
#include "vertical_level_system.h"
#include <iostream>
#include <components/timer.h>

VerticalLevelSystem::VerticalLevelSystem() : LevelSystem() {

}

void VerticalLevelSystem::init() {
    LevelSystem::init();
    last_row_generated_ = last_row_loaded_ = FIRST_ROW_Y;
}

void VerticalLevelSystem::load_next_chunk() {
    std::string level_path = levels_path("");
    int levelN = rng_.nextInt(0, 6);
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
        last_row_loaded_ -= CELL_HEIGHT;
        chunks_.push(row);
    }
}

void VerticalLevelSystem::generate_next_chunk(Blackboard &blackboard,
                                              entt::DefaultRegistry &registry) {
    float off_screen = blackboard.camera.position().y - blackboard.camera.size().x;
    while (last_row_generated_ > off_screen && !chunks_.empty()) {
        std::vector<int> col = chunks_.front();
        float x = COL_X_OFFSET;
        for (int c:col) {
            generateEntity(c, x, last_row_generated_, blackboard, registry);
            x += CELL_WIDTH;
        }
        last_row_generated_ -= CELL_HEIGHT;
        chunks_.pop();
    }
}

void VerticalLevelSystem::destroy_entities(entt::DefaultRegistry &registry) {
    registry.destroy<Platform>();
    registry.destroy<Llama>();
    registry.destroy<Spit>();
    registry.destroy<Bread>();

    while (!chunks_.empty()) {
        chunks_.front().clear();
        chunks_.pop();
    }
}

void VerticalLevelSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    float max_y =
            blackboard.camera.position().y + blackboard.camera.size().y; // some distance off camera
    float min_y =
            blackboard.camera.position().y - blackboard.camera.size().y; // some distance off camera
    while (last_row_loaded_ > min_y) {
        load_next_chunk();
    }
    destroy_off_screen(registry, max_y);
    generate_next_chunk(blackboard, registry);
    update_projectiles(blackboard, registry);
}

void VerticalLevelSystem::destroy_off_screen(entt::DefaultRegistry &registry, float max_y) {
    auto platforms = registry.view<Platform, Transform>();
    for (uint32_t entity: platforms) {
        auto &transform = platforms.get<Transform>(entity);
        if (transform.y > max_y) {
            registry.destroy(entity);
        }
    }

    auto llamas = registry.view<Llama, Transform>();
    for (uint32_t entity: llamas) {
        auto &transform = llamas.get<Transform>(entity);
        if (transform.y > max_y) {
            registry.destroy(entity);
        }
    }

    auto spits = registry.view<Spit, Transform>();
    for (uint32_t entity: spits) {
        auto &transform = spits.get<Transform>(entity);
        if (transform.y > max_y) {
            registry.destroy(entity);
        }
    }
}

void VerticalLevelSystem::update_projectiles(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    auto llama_view = registry.view<Llama, Transform, Timer>();
    for (auto llama_entity : llama_view) {
        auto& llama = llama_view.get<Llama>(llama_entity);
        auto& la_transform = llama_view.get<Transform>(llama_entity);
        auto& la_timer  = llama_view.get<Timer>(llama_entity);
        if (!llama.alive)
            break;

        if(la_timer.is_done(SPIT_TIMER_LABEL)) {
            generateProjectile(la_transform.x, la_transform.y, blackboard, registry);
            la_timer.reset_watch(SPIT_TIMER_LABEL);
        }
    }
}
