//
// Created by Prayansh Srivastava on 2019-02-11.
//

#include <components/timer.h>
#include <components/layer.h>
#include <components/new_entrance.h>
#include <components/food.h>
#include <components/powerup.h>
#include "level_system.h"

LevelSystem::LevelSystem() : rng_(Random(4)),
                             chunks_() {
}

void LevelSystem::init(entt::DefaultRegistry &registry) {
    destroy_entities(registry);
}

void LevelSystem::generateEntity(char value, float x, float y,
                                 Blackboard &blackboard, entt::DefaultRegistry &registry, SceneMode mode) {
    switch (value) {
        case '1': {
            generate_platform(true, x, y, blackboard, registry);
        }
            break;
        case '3': {
            generate_bread(true, x, y, blackboard, registry);
        }
            break;
        case '4': {
            generate_ghost(x, y, blackboard, registry);
        }
            break;
        case '5': {
            generate_llama(x, y, blackboard, registry);
        }
            break;
        case '6': {
            generate_spike(true, true, x, y, blackboard, registry);
        }
            break;
        case '7': {
            generate_spike(false, true, x, y, blackboard, registry);
        }
            break;
        case '8': {
            generate_falling_platform(x, y, blackboard, registry);

        }
            break;
        case 'a': {
            if (mode == STORY_EASY || mode == STORY_HARD)
                generate_cave(x, y, blackboard, registry);
        }
            break;
        case '9': {
            generate_bread(false, x, y, blackboard, registry);
        }
            break;
        case 'b': {
            generate_platform(false, x, y, blackboard, registry);
        }
            break;
        case 'f': {
           generate_food(x, y, blackboard, registry);
        }
            break;
        case 'r': {
            generate_spike(false, false, x, y, blackboard, registry);
        }
            break;

        case 's': {
            generate_shield(x, y, blackboard, registry);
        }
            break;
        case 'v': {
            generate_vial(x, y, blackboard, registry);
        }
            break;
        case 'w': {
            generate_dirt(x, y, blackboard, registry);
        }
            break;
        case 'z': {
            generate_grass(x, y, blackboard, registry);
        }
            break;
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
    registry.assign<Health>(bread, 1);
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
    registry.destroy<NewEntrance>();
    registry.destroy<Food>();

    while (!chunks_.empty()) {
        chunks_.front().clear();
        chunks_.pop();
    }
}

void LevelSystem::generate_platform(bool one_way, float x, float y, Blackboard &blackboard,
                                    entt::DefaultRegistry &registry) {
    float height = one_way ? PLATFORM_HEIGHT : (float) CELL_HEIGHT;
    y = one_way ? y - (float) CELL_HEIGHT / 2 + PLATFORM_HEIGHT / 2 : y;
    auto texture = blackboard.texture_manager.get_texture(
            (blackboard.randNumGenerator.nextInt(0, 100) % 2 == 0) ? "platform1"
                                                                   : "platform2");;
    if (!one_way) {
        texture = blackboard.texture_manager.get_texture(
                (blackboard.randNumGenerator.nextInt(0, 100) % 2 == 0) ? "solid_block_1" : "solid_block_2");
    }
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    auto scaleX = static_cast<float>(CELL_WIDTH / texture.width());
    auto scaleY = static_cast<float>(height / texture.width());
    auto platform = registry.create();
    registry.assign<Platform>(platform, one_way);
    registry.assign<Transform>(platform, x, y, 0.,
                               scaleX,
                               scaleY);
    registry.assign<Sprite>(platform, texture, shader, mesh);
    registry.assign<Collidable>(platform, texture.width() * scaleX,
                                texture.height() * scaleY);
    registry.assign<Layer>(platform, TERRAIN_LAYER);
}

void LevelSystem::generate_ghost(float x, float y, Blackboard &blackboard, entt::DefaultRegistry &registry) {
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
    registry.assign<Health>(ghost, 1);
    registry.assign<Velocity>(ghost, -0.f, 0.f);
    registry.assign<Collidable>(ghost, texture.width() * scaleX,
                                texture.height() * scaleY);
    registry.assign<Layer>(ghost, ENEMY_LAYER + 1);
}

void LevelSystem::generate_llama(float x, float y, Blackboard &blackboard, entt::DefaultRegistry &registry) {
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
    registry.assign<CausesDamage>(llama, TOP_VULNERABLE_MASK, 1);
    registry.assign<Health>(llama, 1);
    registry.assign<Velocity>(llama, 0.f, 0.f);
    registry.assign<Interactable>(llama);
    registry.assign<Collidable>(llama, texture.width() * scaleX - 90.f,
                                texture.height() * scaleY - 10.f);
    registry.assign<ObeysGravity>(llama);
    registry.assign<Layer>(llama, ENEMY_LAYER);
    auto& timer = registry.assign<Timer>(llama);
    timer.save_watch(SPIT_TIMER_LABEL, 2.3f);
}

void LevelSystem::generate_spike(bool tall, bool floating, float x, float y, Blackboard &blackboard,
        entt::DefaultRegistry &registry) {
    auto texture = blackboard.texture_manager.get_texture("stalagmite");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    auto scaleX = static_cast<float>(CELL_WIDTH / texture.width());
    auto scaleY = scaleX * 1.8;
    if (!tall) {
        if (floating) {
            scaleY = scaleX * 0.3;
            y = y - (float) CELL_HEIGHT * 0.65 + PLATFORM_HEIGHT;
        } else {
            scaleY = scaleX * 0.6;
            y = y - (float) CELL_HEIGHT * 0.40 + PLATFORM_HEIGHT;
        }
    }
    auto stalagmite = registry.create();
    registry.assign<Obstacle>(stalagmite);
    registry.assign<CausesDamage>(stalagmite, BOTTOM_VULNERABLE_MASK, 1);
    registry.assign<Platform>(stalagmite, false);
    registry.assign<Transform>(stalagmite, x, y, 0., scaleX, scaleY);
    registry.assign<Sprite>(stalagmite, texture, shader, mesh);
    registry.assign<Collidable>(stalagmite, texture.width() * scaleX,
                                texture.height() * scaleY);
    registry.assign<Layer>(stalagmite, TERRAIN_LAYER);
}

void LevelSystem::generate_falling_platform(float x, float y, Blackboard &blackboard, entt::DefaultRegistry &registry) {
    auto texture = blackboard.texture_manager.get_texture(
            (blackboard.randNumGenerator.nextInt(0, 100) % 2 == 0) ? "falling_blocks_1"
                                                                   : "falling_blocks_2");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    auto scaleX = static_cast<float>(CELL_WIDTH / texture.width());
    auto scaleY = static_cast<float>(PLATFORM_HEIGHT / texture.width());
    auto falling_platform = registry.create();

    registry.assign<Platform>(falling_platform, false, true);
    registry.assign<Transform>(falling_platform, x,
                               y - CELL_HEIGHT / 2 + PLATFORM_HEIGHT / 2, 0., scaleX,
                               scaleY);
    registry.assign<Sprite>(falling_platform, texture, shader, mesh);
    registry.assign<Collidable>(falling_platform, texture.width() * scaleX,
                                texture.height() * scaleY);

    registry.assign<Velocity>(falling_platform, 0.f, 0.f);
    registry.assign<Timer>(falling_platform);
    registry.assign<Layer>(falling_platform, TERRAIN_LAYER);
    auto platform = registry.get<Platform>(falling_platform);
    platform.falling=true;

}

void LevelSystem::generate_cave(float x, float y, Blackboard &blackboard, entt::DefaultRegistry &registry) {
    auto cave = registry.create();
    auto shaderCave = blackboard.shader_manager.get_shader("cave");
    auto meshCave = blackboard.mesh_manager.get_mesh("cave");
    registry.assign<Transform>(cave, x, y, 0., 80, 80);
    registry.assign<Interactable>(cave);
    float heightCave = 750.f;
    float widthCave = 750.f;
    vec2 sizeCave = {widthCave, heightCave};
    vec2 scaleCave = {-80, 80};
    auto &caveE = registry.assign<Cave>(cave, meshCave, shaderCave, sizeCave, scaleCave, false);
    caveE.set_pos(x, y - heightCave);
    registry.assign<Layer>(cave, TERRAIN_LAYER - 4);

    auto new_entrance_entity = registry.create();
    auto texture = blackboard.texture_manager.get_texture("cave_entrance");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    float heightCave_entrance = 2 * 80;
    float widthCave_entrance = 2 * 80;
    registry.assign<NewEntrance>(new_entrance_entity);
    registry.assign<Transform>(new_entrance_entity, x + 380, y - 35, 0.f, 1, 1);
    registry.assign<Interactable>(new_entrance_entity);
    registry.assign<Collidable>(new_entrance_entity, heightCave_entrance, widthCave_entrance);
    registry.assign<Layer>(new_entrance_entity, TERRAIN_LAYER - 2);
    registry.assign<Sprite>(new_entrance_entity, texture, shader, mesh);
}

void LevelSystem::generate_food(float x, float y, Blackboard &blackboard, entt::DefaultRegistry &registry) {
    auto burger = registry.create();
    auto texture = blackboard.texture_manager.get_texture("burger");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    auto scaleX = static_cast<float>(CELL_WIDTH * 0.5f / texture.width());
    auto scaleY = static_cast<float>(CELL_HEIGHT * 0.5f / texture.height());
    registry.assign<Food>(burger);
    registry.assign<Sprite>(burger, texture, shader, mesh);
    registry.assign<Transform>(burger, x, y, 0., scaleX, scaleY);
    registry.assign<Interactable>(burger);
    registry.assign<ObeysGravity>(burger);
    registry.assign<Velocity>(burger);
    registry.assign<Collidable>(burger, texture.width() * scaleX,
                                texture.height() * scaleY);
    registry.assign<Layer>(burger, ITEM_LAYER);
}

void LevelSystem::generate_shield(float x, float y, Blackboard &blackboard, entt::DefaultRegistry &registry) {
    auto shield = registry.create();
    auto texture = blackboard.texture_manager.get_texture("shield");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    const float scale = 0.8f;
    const float y_offset = 10.f;

    registry.assign<Powerup>(shield, SHIELD_POWERUP);
    registry.assign<Sprite>(shield, texture, shader, mesh);
    registry.assign<Transform>(shield, x, y + y_offset, 0, scale, scale);
    registry.assign<Interactable>(shield);
    registry.assign<Collidable>(shield, texture.width() * scale, texture.height() * scale);
    registry.assign<Layer>(shield, ITEM_LAYER);
}

void LevelSystem::generate_vial(float x, float y, Blackboard &blackboard,
                                entt::DefaultRegistry &registry) {
    auto vial = registry.create();
    auto texture = blackboard.texture_manager.get_texture("vial");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    auto scaleX = static_cast<float>((CELL_HEIGHT / 3.0f)  / texture.width());
    auto scaleY = static_cast<float>(CELL_HEIGHT / texture.height());
    registry.assign<Powerup>(vial, VAPE_POWERUP);
    registry.assign<Sprite>(vial, texture, shader, mesh);
    registry.assign<Transform>(vial, x, y, 0.785f, scaleX, scaleY); // rotate by PI/4
    registry.assign<Interactable>(vial);
    registry.assign<Collidable>(vial, texture.width() * scaleX,
                                texture.height() * scaleY);
    registry.assign<Layer>(vial, ITEM_LAYER);
}

void LevelSystem::generate_dirt(float x, float y, Blackboard &blackboard,
                                entt::DefaultRegistry &registry) {
    auto dirt = registry.create();
    auto texture = blackboard.texture_manager.get_texture(
            (blackboard.randNumGenerator.nextInt(0, 100) % 2 == 0) ? "dirt_1"
                                                                   : "dirt_2");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    auto scaleX = static_cast<float>((CELL_WIDTH / texture.width()));
    auto scaleY = static_cast<float>(CELL_HEIGHT*1.8 / texture.height());
    registry.assign<Sprite>(dirt, texture, shader, mesh);
    registry.assign<Transform>(dirt, x, y, 0.f, scaleX, scaleY);
    registry.assign<Interactable>(dirt);
    registry.assign<Platform>(dirt, true);
    registry.assign<Collidable>(dirt, texture.width() * scaleX,
                                texture.height() * scaleY);
    registry.assign<Layer>(dirt, TERRAIN_LAYER - 1);
}

void LevelSystem::generate_grass(float x, float y, Blackboard &blackboard,
                                entt::DefaultRegistry &registry) {
    auto grass = registry.create();
    auto texture = blackboard.texture_manager.get_texture(
            (blackboard.randNumGenerator.nextInt(0, 100) % 2 == 0) ? "grass_1"
                                                                   : "grass_2");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    auto scaleX = static_cast<float>(CELL_WIDTH / texture.width());
    auto scaleY = static_cast<float>(CELL_HEIGHT / texture.width());
    registry.assign<Platform>(grass, false);
    registry.assign<Transform>(grass, x, y, 0.,
                               scaleX,
                               scaleY);
    registry.assign<Sprite>(grass, texture, shader, mesh);
    registry.assign<Collidable>(grass, texture.width() * scaleX,
                                texture.height() * scaleY);
    registry.assign<Layer>(grass, TERRAIN_LAYER);
}