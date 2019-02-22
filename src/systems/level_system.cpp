//
// Created by Prayansh Srivastava on 2019-02-11.
//

#include "level_system.h"

LevelSystem::LevelSystem() : rng_(Random(4)),
                             platform_entities_(),
                             chunks_(),
                             available_entities_() {

}

void LevelSystem::generateEntity(int value, float x, float y,
                                 Blackboard &blackboard, entt::DefaultRegistry &registry) {
    switch (value) {
        case 1: {
            auto texture = blackboard.textureManager.get_texture(
                    (rng_.nextInt(0, 100) % 2 == 0) ? "platform1" : "platform2");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto scale = static_cast<float>(CELL_WIDTH / texture.width());
            auto platform = createEntity(registry);
            registry.assign<Platform>(platform);
            registry.assign<Transform>(platform, x, y, 0., scale,
                                       scale);
            registry.assign<Sprite>(platform, texture, shader);
            registry.assign<Collidable>(platform, texture.width() * scale,
                                        texture.height() * scale);
            platform_entities_.push(platform);
        }
            break;
        default:
            break;
    }
}

uint32_t LevelSystem::createEntity(entt::DefaultRegistry &registry) {
    if (!available_entities_.empty()) {
        uint32_t e = available_entities_.front();
        available_entities_.pop();
        return e;
    }
    return registry.create();
}

void LevelSystem::makeAvailable(const uint32_t e, entt::DefaultRegistry &registry) {
    if (registry.has<Platform>(e)) {
        registry.remove<Transform>(e);
        registry.remove<Sprite>(e);
        registry.remove<Collidable>(e);
        registry.remove<Platform>(e);
    }
    available_entities_.push(e);
}