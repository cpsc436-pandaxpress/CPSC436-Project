//
// Created by cowan on 17/02/19.
//

#ifndef PANDAEXPRESS_VERTICAL_LEVEL_SYSTEM_H
#define PANDAEXPRESS_VERTICAL_LEVEL_SYSTEM_H


#include <util/blackboard.h>
#include <entt/entity/registry.hpp>
#include "level_system.h"

class VerticalLevelSystem : public LevelSystem {
private:
    void load_next_chunk();

    void generate_next_chunk(Blackboard &blackboard, entt::DefaultRegistry &registry);

    void destroy_off_screen(entt::DefaultRegistry &registry, float max_y);

    const float FIRST_ROW_Y = 300.f;
    const float COL_X_OFFSET = -750.f;

    float last_row_generated_, last_row_loaded_;
public:

    VerticalLevelSystem();

    void init();

    void update(Blackboard &blackboard, entt::DefaultRegistry &registry);

    void destroy_entities(entt::DefaultRegistry &registry);
};


#endif //PANDAEXPRESS_VERTICAL_LEVEL_SYSTEM_H
