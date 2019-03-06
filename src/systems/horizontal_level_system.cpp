//
// Created by Prayansh Srivastava on 2019-02-15.
//

#include <util/constants.h>
#include <util/csv_reader.h>
#include <components/transform.h>
#include <components/collidable.h>
#include <iostream>
#include <components/timer.h>
#include "horizontal_level_system.h"


HorizontalLevelSystem::HorizontalLevelSystem(): LevelSystem() {
    init();
}

void HorizontalLevelSystem::init(){
    LevelSystem::init();
    last_col_generated_ = last_col_loaded_ = FIRST_COL_X;
}

void HorizontalLevelSystem::load_next_chunk() {
    std::string level_path = levels_path("");
    int levelN = rng_.nextInt(0, 8);
    std::string levelFile = level_path + "level_" + std::to_string(levelN) + ".csv";
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

void HorizontalLevelSystem::generate_next_chunk(Blackboard &blackboard,
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

void HorizontalLevelSystem::destroy_entities(entt::DefaultRegistry &registry) {
    registry.destroy<Platform>();
    registry.destroy<Llama>();
    registry.destroy<Spit>();
    registry.destroy<Bread>();
    registry.destroy<Ghost>();
    registry.destroy<Obstacle>();
    while (!chunks_.empty()) {
        chunks_.front().clear();
        chunks_.pop();
    }
}

void HorizontalLevelSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    float max_x =
            blackboard.camera.position().x + blackboard.camera.size().x; // some distance off camera
    float min_x =
            blackboard.camera.position().x - blackboard.camera.size().x; // some distance off camera
    while (last_col_loaded_ < max_x) {
        load_next_chunk();
    }
    destroy_off_screen(registry, min_x);
    generate_next_chunk(blackboard, registry);
    update_projectiles(blackboard, registry);
}

void HorizontalLevelSystem::destroy_off_screen(entt::DefaultRegistry &registry, float x) {
    auto platforms = registry.view<Platform, Transform>();
    for (uint32_t entity: platforms) {
        auto &transform = platforms.get<Transform>(entity);
        if (transform.x < x) {
            registry.destroy(entity);
        }
    }

    auto llamas = registry.view<Llama, Transform>();
    for (uint32_t entity: llamas) {
        auto &transform = llamas.get<Transform>(entity);
        if (transform.x < x) {
            registry.destroy(entity);
        }
    }

    auto spits = registry.view<Spit, Transform>();
    for (uint32_t entity: spits) {
        auto &transform = spits.get<Transform>(entity);
        if (transform.x < x) {
            registry.destroy(entity);
        }
    }

    auto breads = registry.view<Bread, Transform>();
    for (uint32_t entity: breads) {
        auto &transform = breads.get<Transform>(entity);
        if (transform.x < x) {
            registry.destroy(entity);
        }
    }

    auto ghosts = registry.view<Ghost, Transform>();
    for (uint32_t entity: ghosts) {
        auto &transform = ghosts.get<Transform>(entity);
        if (transform.x < x) {
            registry.destroy(entity);
        }
    }

    auto obstacles = registry.view<Obstacle, Transform>();
    for (uint32_t entity: obstacles) {
        auto &transform = obstacles.get<Transform>(entity);
        if (transform.x < x) {
            registry.destroy(entity);
        }
    }
}

void HorizontalLevelSystem::update_projectiles(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    vec2 cam_position = blackboard.camera.position();
    vec2 cam_size = blackboard.camera.size();

    auto llama_view = registry.view<Llama, Transform, Collidable, Timer>();
    for (auto llama_entity : llama_view) {
        auto& llama = llama_view.get<Llama>(llama_entity);
        auto& la_transform = llama_view.get<Transform>(llama_entity);
        auto& la_collidable = llama_view.get<Collidable>(llama_entity);
        auto& la_timer = llama_view.get<Timer>(llama_entity);
        if (!llama.alive || (la_transform.x + la_collidable.width / 2 > cam_position.x + cam_size.x / 2))
            break;

        if (la_transform.y > 500)
            llama.alive = false;

        if(la_timer.is_done(SPIT_TIMER_LABEL)) {
            generateProjectile(la_transform.x, la_transform.y, blackboard, registry);
            la_timer.reset_watch(SPIT_TIMER_LABEL);
        }
    }
}
