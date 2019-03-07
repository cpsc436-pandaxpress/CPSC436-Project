//
// Created by Prayansh Srivastava on 2019-02-11.
//

#include <components/timer.h>
#include "level_system.h"

LevelSystem::LevelSystem() : rng_(Random(4)),
                             chunks_() {
    init();
}

void LevelSystem::init() {
    rng_.init(SEED);
}

void LevelSystem::generateEntity(int value, float x, float y,
                                 Blackboard &blackboard, entt::DefaultRegistry &registry) {
    switch (value) {
        case 1: {
            auto texture = blackboard.texture_manager.get_texture(
                    (blackboard.randNumGenerator.nextInt(0, 100) % 2 == 0) ? "platform1" : "platform2");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto mesh = blackboard.mesh_manager.get_mesh("sprite");
            auto scaleX = static_cast<float>(CELL_WIDTH / texture.width());
            auto scaleY = static_cast<float>(PLATFORM_HEIGHT / texture.width());
            auto platform = registry.create();
            registry.assign<Platform>(platform);
            registry.assign<Transform>(platform, x, y - CELL_HEIGHT / 2 + PLATFORM_HEIGHT / 2, 0., scaleX,
                                       scaleY);
            registry.assign<Sprite>(platform, texture, shader, mesh);
            registry.assign<Collidable>(platform, texture.width() * scaleX,
                                        texture.height() * scaleY);
        }
            break;
        case 3: {
            auto texture = blackboard.texture_manager.get_texture("bread");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto mesh = blackboard.mesh_manager.get_mesh("sprite");
            auto scale = static_cast<float>(CELL_WIDTH / texture.width()/2);
            auto bread = registry.create();
            registry.assign<Transform>(bread, x, y, 0., scale, scale);
            registry.assign<Sprite>(bread, texture, shader, mesh);
            registry.assign<Bread>(bread);
            registry.assign<CausesDamage>(bread, false, true, 1);
            registry.assign<Health>(bread,1);
            registry.assign<Velocity>(bread, -BREAD_SPEED, 0.f);
            registry.assign<Interactable>(bread);
            registry.assign<Collidable>(bread, texture.width() * scale,
                                        texture.height() * scale);
            registry.assign<ObeysGravity>(bread);
        }
            break;
        case 4: {
            auto texture = blackboard.texture_manager.get_texture("ghost");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto mesh = blackboard.mesh_manager.get_mesh("sprite");
            auto scale = static_cast<float>(CELL_WIDTH / texture.width());
            auto ghost = registry.create();
            registry.assign<Transform>(ghost, x, y, 0., scale,
                                       scale);
            registry.assign<Sprite>(ghost, texture, shader, mesh);
            registry.assign<Ghost>(ghost);
            registry.assign<CausesDamage>(ghost, false, true, 1);
            registry.assign<Health>(ghost,1);
            registry.assign<Velocity>(ghost, -0.f, 0.f);
            registry.assign<Collidable>(ghost, texture.width() * scale,
                                        texture.height() * scale);
        }
            break;
        case 5: {
            auto texture = blackboard.texture_manager.get_texture("llama");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto mesh = blackboard.mesh_manager.get_mesh("sprite");
            auto scale = static_cast<float>(CELL_HEIGHT / texture.height());
            auto llama = registry.create();
            registry.assign<Transform>(llama, x, y - 200, 0., scale,
                                       scale);
            registry.assign<Sprite>(llama, texture, shader, mesh);
            registry.assign<Llama>(llama);
            registry.assign<CausesDamage>(llama, false, true, 1);
            registry.assign<Health>(llama,1);
            registry.assign<Velocity>(llama, 0.f, 0.f);
            registry.assign<Interactable>(llama);
            registry.assign<Collidable>(llama, texture.width() * scale,
                                        texture.height() * scale);
            registry.assign<ObeysGravity>(llama);
            auto& timer = registry.assign<Timer>(llama);
            timer.save_watch(SPIT_TIMER_LABEL, 3.f);
        }
            break;
        case 6: {
            auto texture = blackboard.texture_manager.get_texture("stalagmite2");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto mesh = blackboard.mesh_manager.get_mesh("sprite");
            auto scale = static_cast<float>(CELL_WIDTH / texture.width());
            auto stalagmite2 = registry.create();
            registry.assign<Obstacle>(stalagmite2);
            registry.assign<Transform>(stalagmite2, x, y, 0., scale,
                                       scale);
            registry.assign<Sprite>(stalagmite2, texture, shader, mesh);
            registry.assign<Collidable>(stalagmite2, texture.width() * scale,
                                        texture.height() * scale);
            break;
        }
        case 7: {
            auto texture = blackboard.texture_manager.get_texture("stalagmite");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto mesh = blackboard.mesh_manager.get_mesh("sprite");
            auto scale = static_cast<float>(CELL_WIDTH / texture.width());
            auto stalagmite = registry.create();
            registry.assign<Obstacle>(stalagmite);
            registry.assign<CausesDamage>(stalagmite, false, true, 1);
            registry.assign<Transform>(stalagmite, x, y, 0., scale,
                                       scale);
            registry.assign<Sprite>(stalagmite, texture, shader, mesh);
            registry.assign<Collidable>(stalagmite, texture.width() * scale,
                                        texture.height() * scale);

        }
            break;
        case 8: {
            auto texture = blackboard.texture_manager.get_texture(
                    (blackboard.randNumGenerator.nextInt(0, 100) % 2 == 0) ? "platform1" : "platform2");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto mesh = blackboard.mesh_manager.get_mesh("sprite");
            auto scaleX = static_cast<float>(CELL_WIDTH / texture.width());
            auto scaleY = static_cast<float>(PLATFORM_HEIGHT / texture.width());
            auto falling_platform = registry.create();

            registry.assign<Platform>(falling_platform);
            registry.assign<Transform>(falling_platform, x, y - CELL_HEIGHT / 2 + PLATFORM_HEIGHT / 2, 0., scaleX,
                                       scaleY);
            registry.assign<Sprite>(falling_platform, texture, shader, mesh);
            registry.assign<Collidable>(falling_platform, texture.width() * scaleX,
                                        texture.height() * scaleY);

            registry.assign<FallingPlatform>(falling_platform);
            registry.assign<Velocity>(falling_platform, 0.f, 0.f);
            auto& timer = registry.assign<Timer>(falling_platform);

        }
            break;
        default:
            break;
    }
}

void LevelSystem::generateProjectile(float x, float y, Blackboard &blackboard, entt::DefaultRegistry &registry) {
    auto texture = blackboard.texture_manager.get_texture("spit");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    auto scale = static_cast<float>(CELL_WIDTH / texture.width()/ 5);
    auto projectile = registry.create();
    registry.assign<Transform>(projectile, x, y - 30, 0., scale,
                               scale);
    registry.assign<Sprite>(projectile, texture, shader, mesh);
    registry.assign<Spit>(projectile);
    registry.assign<CausesDamage>(projectile, false, true, 1);
    registry.assign<Health>(projectile,1);
    registry.assign<Velocity>(projectile, PROJECTILE_SPEED_X, PROJECTILE_SPEED_Y);
    registry.assign<Interactable>(projectile);
    registry.assign<Collidable>(projectile, texture.width() * scale,
                                texture.height() * scale);
}
