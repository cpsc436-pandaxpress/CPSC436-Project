//
// Created by Prayansh Srivastava on 2019-02-15.
//

#include <util/constants.h>
#include <util/csv_reader.h>
#include <components/transform.h>
#include <components/collidable.h>
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
    while (!platform_entities_.empty()) {
        uint32_t platform = platform_entities_.front();
        registry.destroy(platform);
        platform_entities_.pop();
    }
    while (!enemy_entities_.empty()) {
        uint32_t enemy = enemy_entities_.front();
        registry.destroy(enemy);
        enemy_entities_.pop();
    }
    while (!projectile_entities_.empty()) {
        uint32_t projectile = projectile_entities_.front();
        registry.destroy(projectile);
        projectile_entities_.pop();
    }
    while (!obstacle_entities_.empty()) {
        uint32_t obstacle = obstacle_entities_.front();
        registry.destroy(obstacle);
        obstacle_entities_.pop();
    }
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
//    destroy_off_screen(registry, min_x); // fixme Do not uncomment, not working right now
    generate_next_chunk(blackboard, registry);
    update_projectiles(blackboard, registry);
}

void HorizontalLevelSystem::destroy_off_screen(entt::DefaultRegistry &registry, float x) {
    auto view = registry.view<Platform, Transform>();
    std::queue<uint32_t> rQueue;
    for (u_int32_t entity: view) {
        auto &transform = view.get<Transform>(entity);
        if (transform.x < x) {
            rQueue.push(entity);
        }
    }
    while (!rQueue.empty()) {
        const uint32_t e = rQueue.front();
        makeAvailable(e, registry);
        rQueue.pop();
    }
}

void HorizontalLevelSystem::update_projectiles(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    vec2 cam_position = blackboard.camera.position();
    vec2 cam_size = blackboard.camera.size();

    auto llama_view = registry.view<Llama, Transform, Collidable>();
    for (auto llama_entity : llama_view) {
        auto& llama = llama_view.get<Llama>(llama_entity);
        auto& la_transform = llama_view.get<Transform>(llama_entity);
        auto& la_collidable = llama_view.get<Collidable>(llama_entity);
        if (!llama.alive || (la_transform.x + la_collidable.width / 2 > cam_position.x + cam_size.x / 2))
            break;

        if (la_transform.y > 500)
            llama.alive = false;

        if(llama.spit_time == 0) {
            generateProjectile(la_transform.x, la_transform.y, blackboard, registry);
            llama.spit_time = PROJECTILE_SPACING;
        } else {
            llama.spit_time--;
        }
    }
}
