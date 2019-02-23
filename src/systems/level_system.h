//
// Created by Prayansh Srivastava on 2019-02-11.
//

#ifndef PANDAEXPRESS_LEVEL_MANAGER_H
#define PANDAEXPRESS_LEVEL_MANAGER_H
#define CELL_WIDTH 100.0  // Should these be macros and not constants?
#define CELL_HEIGHT 100.0

#include <components/transform.h>
#include <components/collidable.h>
#include <components/platform.h>
#include <components/bread.h>
#include <components/ghost.h>
#include <components/causes_damage.h>
#include <components/health.h>
#include <components/velocity.h>
#include <components/interactable.h>
#include <components/obeys_gravity.h>
#include "util/random.h"
#include "system.h"
#include <queue>

class LevelSystem : public System {
protected:
    Random rng_;
    std::queue<std::vector<int>> chunks_;
    std::queue<uint32_t> platform_entities_;
    std::queue<uint32_t> available_entities_;
    const float BREAD_SPEED = 50.f;

    virtual void load_next_chunk() = 0;

    virtual void generate_next_chunk(Blackboard &blackboard, entt::DefaultRegistry &registry) = 0;

    void generateEntity(int value, float x, float y,
                        Blackboard &blackboard, entt::DefaultRegistry &registry);

    void makeAvailable(const uint32_t e, entt::DefaultRegistry &registry);

    uint32_t createEntity(entt::DefaultRegistry &registry);

public:

    LevelSystem();

    void update(Blackboard &blackboard, entt::DefaultRegistry &registry) override = 0;

    virtual void destroy_entities(entt::DefaultRegistry &registry) = 0;

    virtual void destroy_off_screen(entt::DefaultRegistry &registry, float x) = 0;

};


#endif //PANDAEXPRESS_LEVEL_MANAGER_H
