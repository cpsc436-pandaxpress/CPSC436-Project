//
// Created by Becca Roth on 2019-03-31.
//

#include "transition_system.h"

TransitionSystem::TransitionSystem(SceneType scene_type) : scene_type(scene_type) {}

void TransitionSystem::update(Blackboard &blackboard, entt::DefaultRegistry& registry) {
    vec2 cam_position = blackboard.camera.position();
    vec2 cam_size = blackboard.camera.size();

    auto cave_view = registry.view<Cave, Transform>();
    for (auto cave_entity : cave_view) {
        auto &cave = cave_view.get<Cave>(cave_entity);
        auto &cave_transform = cave_view.get<Transform>(cave_entity);
        auto panda_view = registry.view<Panda, Transform, Velocity>();
        switch (scene_type) {
            case JUNGLE_TYPE: {
                for (auto panda_entity : panda_view) {
                    auto &panda = panda_view.get<Panda>(panda_entity);
                    auto &panda_transform = panda_view.get<Transform>(panda_entity);
                    auto &panda_velocity = panda_view.get<Velocity>(panda_entity);
                    if (cave.pos().x + cave.size().x / 2 < cam_position.x + cam_size.x / 2 &&
                        cave.pos().x + cave.size().x / 2 <= panda_transform.x) {
                        panda_velocity.x_velocity = 0.f;
                        if (panda_transform.y >= cave.pos().y + cave.size().y) {
                            blackboard.camera.transition_ready = true;
                        }
                    }
                }
                if (cave.pos().x - cave.size().x < cam_position.x - cam_size.x / 2 + cave_offset) {
                    blackboard.camera.in_transition = true;
                }
            }
                break;
            case SKY_TYPE: {
                for (auto panda_entity : panda_view) {
                    auto &panda = panda_view.get<Panda>(panda_entity);
                    auto &panda_transform = panda_view.get<Transform>(panda_entity);
                    auto &panda_velocity = panda_view.get<Velocity>(panda_entity);
                    if (cave.pos().y + cave.size().y*2 > cam_position.y - cam_size.y) {
                        blackboard.camera.transition_ready = true;
                    }
                    printf("%f\n", cave.pos().y);
                    printf("%f\n", cave.size().y);
                    printf("%f\n", cam_position.y);
                    printf("%f\n", cam_size.y);
                    printf("%f\n", cave.pos().y + cave.size().y*2);
                    printf("%f\n", cam_position.y - cam_size.y);
                }
                if (cave.pos().y - cave.size().y > cam_position.y - cam_size.y / 2 + cave_offset) {
                    blackboard.camera.in_transition = true;
                }
            }
                break;
        }
    }
}

/*void TransitionSystem::runTransition(Blackboard &blackboard, entt::DefaultRegistry& registry) {
    vec2 cam_position = blackboard.camera.position();
    vec2 cam_size = blackboard.camera.size();

    auto cave_view = registry.view<Cave, Transform>();
    for (auto cave_entity : cave_view) {
        auto &cave = cave_view.get<Cave>(cave_entity);
        auto &cave_transform = cave_view.get<Transform>(cave_entity);
        if(cave.pos().x - cave.size().x < cam_position.x - cam_size.x/2 + cave_offset){
            auto panda_view = registry.view<Panda, Velocity>();
            for (auto panda_entity : panda_view) {
                auto &panda = panda_view.get<Panda>(panda_entity);
                auto &panda_velocity = panda_view.get<Velocity>(panda_entity);
                panda_velocity.x_velocity = 0.f;
            }
        }
        if(cave.pos().x - cave.size().x < cam_position.x - cam_size.x/2 + cave_offset){
            blackboard.camera.in_transition = true;
        }
    }
}*/