//
// Created by Prayansh Srivastava on 2019-02-11.
//

#include <components/timer.h>
#include <components/layer.h>
#include "level_system.h"

LevelSystem::LevelSystem() : rng_(Random(4)),
                             chunks_() {
    init();
}

void LevelSystem::init() {
    rng_.init(STORY_SEED);
}

void LevelSystem::generateEntity(char value, float x, float y,
                                 Blackboard &blackboard, entt::DefaultRegistry &registry) {
    switch (value) {
        case '1': {
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
            registry.assign<Layer>(platform, TERRAIN_LAYER);
        }
            break;
        case '3': {
            generate_bread(true, x, y, blackboard, registry);
        }
            break;
        case '4': {
            auto texture = blackboard.texture_manager.get_texture("ghost");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto mesh = blackboard.mesh_manager.get_mesh("sprite");
            float scaleY = 70.0f / texture.height();
            float scaleX = 85.0f / texture.width();
            auto ghost = registry.create();
            registry.assign<Transform>(ghost, x, y, 0., scaleX,
                                       scaleY);
            registry.assign<Sprite>(ghost, texture, shader, mesh);
            registry.assign<Ghost>(ghost);
            registry.assign<CausesDamage>(ghost, ALL_DMG_MASK, 1);
            registry.assign<Health>(ghost,1);
            registry.assign<Velocity>(ghost, -0.f, 0.f);
            registry.assign<Collidable>(ghost, texture.width() * scaleX,
                                        texture.height() * scaleY);
            registry.assign<Layer>(ghost, ENEMY_LAYER);
        }
            break;
        case '5': {
            auto texture = blackboard.texture_manager.get_texture("llama");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto mesh = blackboard.mesh_manager.get_mesh("sprite");
            float scaleY = 150.0f / texture.height();
            float scaleX = 150.0f / texture.width();
            auto llama = registry.create();
            registry.assign<Transform>(llama, x, y - 200, 0., scaleX,
                                       scaleY);
            registry.assign<Sprite>(llama, texture, shader, mesh);
            registry.assign<Llama>(llama);
            registry.assign<CausesDamage>(llama,TOP_VULNERABLE_MASK, 1);
            registry.assign<Health>(llama,1);
            registry.assign<Velocity>(llama, 0.f, 0.f);
            registry.assign<Interactable>(llama);
            registry.assign<Collidable>(llama, texture.width() * scaleX - 150.f,
                                        texture.height() * scaleY - 10.f);
            registry.assign<ObeysGravity>(llama);
            registry.assign<Layer>(llama, ENEMY_LAYER);
            auto& timer = registry.assign<Timer>(llama);
            timer.save_watch(SPIT_TIMER_LABEL, 2.3f);
        }
            break;
        case '6': {
            auto texture = blackboard.texture_manager.get_texture("stalagmite");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto mesh = blackboard.mesh_manager.get_mesh("sprite");
            auto scale = static_cast<float>(CELL_WIDTH / texture.width());
            auto stalagmite2 = registry.create();
            registry.assign<Obstacle>(stalagmite2);
            registry.assign<CausesDamage>(stalagmite2, ALL_DMG_MASK, 1);
            //
            //
            // registry.assign<Platform>(stalagmite2, false);
            registry.assign<Transform>(stalagmite2, x, y, 0., scale,
                                       scale*1.8f);
            registry.assign<Sprite>(stalagmite2, texture, shader, mesh);
            registry.assign<Collidable>(stalagmite2, texture.width() * scale,
                                        texture.height() * scale*1.8);
            registry.assign<Layer>(stalagmite2, TERRAIN_LAYER);

            break;
        }
        case '7': {
            auto texture = blackboard.texture_manager.get_texture("stalagmite");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto mesh = blackboard.mesh_manager.get_mesh("sprite");
            auto scale = static_cast<float>(CELL_WIDTH*0.5f / texture.width());
            auto stalagmite = registry.create();
            registry.assign<Obstacle>(stalagmite);
            registry.assign<CausesDamage>(stalagmite, ALL_DMG_MASK, 1);
            registry.assign<Transform>(stalagmite, x, y - CELL_HEIGHT*0.75f + PLATFORM_HEIGHT, 0., scale*2.f,
                                       scale);
            registry.assign<Sprite>(stalagmite, texture, shader, mesh);
            registry.assign<Collidable>(stalagmite, texture.width() * scale*2.f,
                                        texture.height() * scale);
            registry.assign<Layer>(stalagmite, TERRAIN_LAYER);

        }
            break;
        case '8': {
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
            registry.assign<Timer>(falling_platform);
            registry.assign<Layer>(falling_platform, TERRAIN_LAYER);

        }
            break;
        case 'a': {
            auto cave = registry.create();
            auto shaderCave = blackboard.shader_manager.get_shader("cave");
            auto meshCave = blackboard.mesh_manager.get_mesh("cave");
            registry.assign<Transform>(cave, 100, 200, 0., 80, 80);
            registry.assign<Interactable>(cave);
            float heightCave = 750.f;
            float widthCave = 750.f;
            vec2 sizeCave = {widthCave, heightCave};
            vec2 scaleCave = {-80, 80};
            auto &caveE = registry.assign<Cave>(cave, meshCave, shaderCave, sizeCave, scaleCave);
            caveE.set_pos(550, -550);
            //printf("Rendering Cave (%f, %f)\n", x, y);
        }
            break;
        case '9': {
            generate_bread(false, x, y, blackboard, registry);
        }
            break;
        case 'b': {
            auto texture = blackboard.texture_manager.get_texture(
                    (blackboard.randNumGenerator.nextInt(0, 100) % 2 == 0) ? "platform1" : "platform2");
            auto shader = blackboard.shader_manager.get_shader("sprite");
            auto mesh = blackboard.mesh_manager.get_mesh("sprite");
            auto scaleX = static_cast<float>(CELL_WIDTH / texture.width());
            auto scaleY = static_cast<float>(CELL_HEIGHT / texture.height());
            auto platform = registry.create();
            registry.assign<Platform>(platform, false);
            registry.assign<Transform>(platform, x, y, 0., scaleX,
                                       scaleY);
            registry.assign<Sprite>(platform, texture, shader, mesh);
            registry.assign<Collidable>(platform, texture.width() * scaleX,
                                        texture.height() * scaleY);
        }

        default:
            break;
    }
}

void LevelSystem::generate_bread(bool move_left, float x, float y, Blackboard &blackboard,
                                 entt::DefaultRegistry &registry) {
    auto texture = blackboard.texture_manager.get_texture("bread");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    float scaleY = 75.0f / texture.height();
    float scaleX = 75.0f / texture.width();
    auto bread = registry.create();
    registry.assign<Transform>(bread, x, y, 0., scaleX, scaleY);
    registry.assign<Sprite>(bread, texture, shader, mesh);
    registry.assign<Bread>(bread, move_left);
    registry.assign<CausesDamage>(bread, TOP_VULNERABLE_MASK, 1);
    registry.assign<Health>(bread,1);
    registry.assign<Velocity>(bread, 0.f, 0.f);
    registry.assign<Interactable>(bread);
    registry.assign<Collidable>(bread, texture.width() * scaleX,
                                texture.height() * scaleY);
    registry.assign<ObeysGravity>(bread);
    registry.assign<Layer>(bread, ENEMY_LAYER);
}

/*
 * Contract to destroy anything created in generate_entity()
 * For example projectiles created elsewhere wont be destroyed here and have to be done by the
 * system creating it
*/

void LevelSystem::destroy_entities(entt::DefaultRegistry &registry) {
    registry.destroy<Platform>();
    registry.destroy<Llama>();
    registry.destroy<Ghost>();
    registry.destroy<Bread>();
    registry.destroy<Obstacle>();
    registry.destroy<Cave>();

    while (!chunks_.empty()) {
        chunks_.front().clear();
        chunks_.pop();
    }
}
