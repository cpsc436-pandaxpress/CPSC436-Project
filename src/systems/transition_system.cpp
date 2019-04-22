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
                        if (panda_transform.y >= cave.pos().y + cave.size().y) {
                            blackboard.camera.transition_ready = true;
                        } else {
                            panda_velocity.x_velocity = 0.f;
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
                    if (cave_transform.y < panda_transform.y &&
                            cave_transform.y + 20 > panda_transform.y &&
                            cave.pos().x + cave.size().x / 2 < cam_position.x + cam_size.x / 2 &&
                            cave.pos().x + cave.size().x / 2 <= panda_transform.x &&
                            cave.pos().x + cave.size().x / 2  + 20 >= panda_transform.x) {
                        blackboard.camera.transition_ready = true;
                    }
                }
                if (cave_transform.y > cam_position.y + cave_offset) {
                    blackboard.camera.in_transition = true;
                }
            }
                break;
            case BOSS_TYPE: {
                if (cave.growing){
                    return;
                }
                for (auto panda_entity : panda_view) {
                    auto &panda = panda_view.get<Panda>(panda_entity);
                    auto &panda_transform = panda_view.get<Transform>(panda_entity);
                    auto &panda_velocity = panda_view.get<Velocity>(panda_entity);
                    if (cave_transform.y < panda_transform.y &&
                        cave_transform.y + 20 > panda_transform.y &&
                        cave.pos().x + cave.size().x / 2 < cam_position.x + cam_size.x / 2 &&
                        cave.pos().x + cave.size().x / 2 <= panda_transform.x &&
                        cave.pos().x + cave.size().x / 2  + 20 >= panda_transform.x) {
                        blackboard.camera.transition_ready = true;
                    }
                }
            }
                break;
        }
    }
}
