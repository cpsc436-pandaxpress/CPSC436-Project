//
// Created by Prayansh Srivastava on 2019-02-11.
//

#include "level_system.h"

LevelSystem::LevelSystem() : rng_(Random(4)),
                             platform_entities_(),
                             chunks_(),
                             available_entities_(),
                             obstacle_entities_() {

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
        case 3: {
            auto texture = blackboard.textureManager.get_texture("bread");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto scale = static_cast<float>(CELL_WIDTH / texture.width()/2);
            auto bread = createEntity(registry);
            registry.assign<Transform>(bread, x, y, 0., scale, scale);
            registry.assign<Sprite>(bread, texture, shader);
            registry.assign<Bread>(bread);
            registry.assign<CausesDamage>(bread, false, true, 1);
            registry.assign<Health>(bread,1);
            registry.assign<Velocity>(bread, -BREAD_SPEED, 0.f);
            registry.assign<Interactable>(bread);
            registry.assign<Collidable>(bread, texture.width() * scale,
                                        texture.height() * scale);
            registry.assign<ObeysGravity>(bread);
            enemy_entities_.push(bread);
        }
            break;
        case 4: {
            auto texture = blackboard.textureManager.get_texture("ghost");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto scale = static_cast<float>(CELL_WIDTH / texture.width());
            auto ghost = createEntity(registry);
            registry.assign<Transform>(ghost, x, y, 0., scale,
                                       scale);
            registry.assign<Sprite>(ghost, texture, shader);
            registry.assign<Ghost>(ghost);
            registry.assign<CausesDamage>(ghost, false, true, 1);
            registry.assign<Health>(ghost,1);
            registry.assign<Velocity>(ghost, -0.f, 0.f);
            registry.assign<Collidable>(ghost, texture.width() * scale,
                                        texture.height() * scale);
            enemy_entities_.push(ghost);
        }
            break;
        case 5: {
            auto texture = blackboard.textureManager.get_texture("llama");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto scale = static_cast<float>(CELL_HEIGHT / texture.height());
            auto llama = createEntity(registry);
            registry.assign<Transform>(llama, x, y - 200, 0., scale,
                                       scale);
            registry.assign<Sprite>(llama, texture, shader);
            registry.assign<Llama>(llama);
            registry.assign<CausesDamage>(llama, false, true, 1);
            registry.assign<Health>(llama,1);
            registry.assign<Velocity>(llama, 0.f, 0.f);
            registry.assign<Interactable>(llama);
            registry.assign<Collidable>(llama, texture.width() * scale,
                                        texture.height() * scale);
            registry.assign<ObeysGravity>(llama);
            enemy_entities_.push(llama);
        }
            break;
        case 6: {
            auto texture = blackboard.textureManager.get_texture("stalagmite2");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto scale = static_cast<float>(CELL_WIDTH / texture.width());
            auto stalagmite2 = createEntity(registry);
            registry.assign<Obstacle>(stalagmite2);
            registry.assign<Transform>(stalagmite2, x, y, 0., scale,
                                       scale);
            registry.assign<Sprite>(stalagmite2, texture, shader);
            registry.assign<Collidable>(stalagmite2, texture.width() * scale,
                                        texture.height() * scale);
            obstacle_entities_.push(stalagmite2);
        }
            break;
        case 7: {
            auto texture = blackboard.textureManager.get_texture("stalagmite");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto scale = static_cast<float>(CELL_WIDTH / texture.width());
            auto stalagmite = createEntity(registry);
            registry.assign<Obstacle>(stalagmite);
            registry.assign<CausesDamage>(stalagmite, false, true, 1);
            registry.assign<Transform>(stalagmite, x, y, 0., scale,
                                       scale);
            registry.assign<Sprite>(stalagmite, texture, shader);
            registry.assign<Collidable>(stalagmite, texture.width() * scale,
                                        texture.height() * scale);

            obstacle_entities_.push(stalagmite);
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

void LevelSystem::generateProjectile(float x, float y, Blackboard &blackboard, entt::DefaultRegistry &registry) {
    auto texture = blackboard.textureManager.get_texture("spit");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto scale = static_cast<float>(CELL_WIDTH / texture.width()/ 5);
    auto projectile = createEntity(registry);
    registry.assign<Transform>(projectile, x, y - 30, 0., scale,
                               scale);
    registry.assign<Sprite>(projectile, texture, shader);
    registry.assign<Spit>(projectile);
    registry.assign<CausesDamage>(projectile, false, true, 1);
    registry.assign<Health>(projectile,1);
    registry.assign<Velocity>(projectile, PROJECTILE_SPEED_X, PROJECTILE_SPEED_Y);
    registry.assign<Interactable>(projectile);
    registry.assign<Collidable>(projectile, texture.width() * scale,
                                texture.height() * scale);
    projectile_entities_.push(projectile);
}