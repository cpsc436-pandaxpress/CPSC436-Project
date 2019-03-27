//
// Created by alex on 29/01/19.
//

#include <components/bread.h>
#include <components/obstacle.h>
#include <components/panda.h>
#include <components/collidable.h>
#include <components/obeys_gravity.h>
#include <components/health.h>
#include <components/velocity.h>
#include <components/interactable.h>
#include <components/platform.h>
#include <components/causes_damage.h>
#include <graphics/background.h>
#include "test_scene.h"
#include "components/transform.h"
#include <algorithm>

TestScene::TestScene(Blackboard &blackboard, SceneManager &scene_manager) :
        Scene(scene_manager),
        platforms(),
        enemies(),
        sprite_transform_system(),
        sprite_render_system(),
        physics_system(),
        player_movement_system(),
        obstacles(),
        background_render_system(),
        background_transform_system() {
    init_scene(blackboard);
    gl_has_errors("test_scene");
}


void TestScene::init_scene(Blackboard &blackboard) {
    blackboard.randNumGenerator.init(0);
    blackboard.camera.set_position(CAMERA_START_X, CAMERA_START_Y);
    blackboard.camera.compose();
    last_placed_x = PLATFORM_START_X;
    last_placed_x_floating = PLATFORM_START_X;
    last_rock_x = blackboard.camera.size().x;
    last_bread_x = BREAD_START_X;

    create_background(blackboard);
    create_panda(blackboard);
    create_bread(blackboard);
}

void TestScene::update(Blackboard &blackboard) {
    generate_platforms(blackboard);
    generate_obstacles(blackboard);
    generate_floating_platforms(blackboard);

    update_camera(blackboard);
    update_panda(blackboard);

    if (blackboard.camera.position().x >= last_bread_x) {
        create_bread(blackboard);
    }

    background_transform_system.update(blackboard, registry_);
    player_movement_system.update(blackboard, registry_);
    physics_system.update(blackboard, registry_);
    sprite_transform_system.update(blackboard, registry_);
}

void TestScene::update_camera(Blackboard &blackboard) {
    vec2 cam_position = blackboard.camera.position();

    auto &panda_transform = registry_.get<Transform>(panda_entity);
    float y_offset = std::min(0.f, panda_transform.y + MAX_CAMERA_Y_DIFF);

    blackboard.camera.set_position(cam_position.x + CAMERA_SPEED * blackboard.delta_time,
                                   y_offset);
    blackboard.camera.compose();
}

void TestScene::update_panda(Blackboard &blackboard) {
    vec2 cam_position = blackboard.camera.position();
    vec2 cam_size = blackboard.camera.size();

    auto &transform = registry_.get<Transform>(panda_entity);
    auto &panda = registry_.get<Panda>(panda_entity);
    auto &panda_collidable = registry_.get<Collidable>(panda_entity);

    if (transform.x + panda_collidable.width < cam_position.x - cam_size.x / 2 ||
        transform.y - panda_collidable.height > cam_position.y + cam_size.y / 2 || !panda.alive) {
        reset_scene(blackboard);
    } else if (transform.x + panda_collidable.width / 2 > cam_position.x + cam_size.x / 2) {
        transform.x = cam_position.x + cam_size.x / 2 - panda_collidable.width / 2;
    }
}

void TestScene::render(Blackboard &blackboard) {
    // update the rendering systems
    background_render_system.update(blackboard, registry_); // render background first
    sprite_render_system.update(blackboard, registry_);
}

void TestScene::create_panda(Blackboard &blackboard) {
    panda_entity = registry_.create();

    auto texture = blackboard.textureManager.get_texture("panda");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    float scale = 0.3f;
    registry_.assign<Transform>(panda_entity, PANDA_START_X, PANDA_START_Y, 0., scale, scale);
    registry_.assign<Sprite>(panda_entity, texture, shader, mesh);
    registry_.assign<Panda>(panda_entity);
    registry_.assign<ObeysGravity>(panda_entity);
    registry_.assign<Health>(panda_entity, 1);
    registry_.assign<Interactable>(panda_entity);
    registry_.assign<CausesDamage>(panda_entity, PANDA_DMG_MASK, 1);
    registry_.assign<Velocity>(panda_entity, 0.f, 0.f);
    registry_.assign<Collidable>(panda_entity, texture.width() * scale, texture.height() * scale);

}

void TestScene::generate_platforms(Blackboard &blackboard) {
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    float max_x =
            blackboard.camera.position().x + blackboard.camera.size().x; // some distance off camera
    while (last_placed_x < max_x) {
        auto texture = blackboard.textureManager.get_texture(
                (blackboard.randNumGenerator.nextInt(0, 100) % 2 == 0) ? "platform1" : "platform2");
        float scale = 100.0f / texture.width();
        if (platforms.size() > MAX_PLATFORMS) {//reuse
            auto platform = platforms.front();
            platforms.pop();
            registry_.replace<Transform>(platform, last_placed_x, PLATFORM_START_Y, 0.f, scale,
                                         scale);
            platforms.push(platform);
        } else {
            auto platform = registry_.create();
            registry_.assign<Platform>(platform);
            registry_.assign<Transform>(platform, last_placed_x, PLATFORM_START_Y, 0., scale,
                                        scale);
            registry_.assign<Sprite>(platform, texture, shader, mesh);
            registry_.assign<Collidable>(platform, texture.width() * scale,
                                         texture.height() * scale);

            platforms.push(platform);
        }
        last_placed_x += texture.width() * scale;
    }
}

void TestScene::generate_floating_platforms(Blackboard &blackboard) {
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    float max_x =
            blackboard.camera.position().x + blackboard.camera.size().x; // some distance off camera
    while (last_placed_x_floating < max_x) {
        auto yOffset = blackboard.randNumGenerator.nextInt(0, 400);
        auto texture = blackboard.textureManager.get_texture("platform_center_grass");
        float scale = 200.0f / texture.width();

        if (floating_platforms.size() > MAX_PLATFORMS) {//reuse
            auto floatingPlatform = floating_platforms.front();
            floating_platforms.pop();
            registry_.replace<Transform>(floatingPlatform, last_placed_x_floating,
                                         FLOATING_PLATFORM_START_Y - yOffset, 0.f, scale,
                                         scale);
            floating_platforms.push(floatingPlatform);
        } else {

            auto floating_platform = registry_.create();
            registry_.assign<Platform>(floating_platform);
            registry_.assign<Transform>(floating_platform, last_placed_x_floating,
                                        FLOATING_PLATFORM_START_Y - yOffset, 0., scale,
                                        scale);
            registry_.assign<Sprite>(floating_platform, texture, shader, mesh);
            registry_.assign<Collidable>(floating_platform, texture.width() * scale,
                                         texture.height() * scale);

            floating_platforms.push(floating_platform);
        }
        last_placed_x_floating += texture.width() * 3;
    }
}

void TestScene::create_bread(Blackboard &blackboard) {
    auto bread = registry_.create();
    auto texture = blackboard.textureManager.get_texture("bread");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scale = 1;

    // Spawn bread on right half of the screen
    float next_start_x = last_bread_x
            + blackboard.randNumGenerator.nextInt(0, (int) blackboard.camera.size().x / 2);
    registry_.assign<Transform>(bread, next_start_x, BREAD_START_Y - texture.height(), 0.,
                                scale, scale);
    registry_.assign<Sprite>(bread, texture, shader, mesh);
    registry_.assign<Bread>(bread);
    registry_.assign<CausesDamage>(bread, TOP_VULNERABLE_MASK, 1);
    registry_.assign<Health>(bread, 1);
    registry_.assign<Velocity>(bread, -BREAD_SPEED, 0.f);
    registry_.assign<Collidable>(bread, texture.width() * scale, texture.height() * scale);
    registry_.assign<Interactable>(bread);
    registry_.assign<ObeysGravity>(bread);

    int next_interval = blackboard.randNumGenerator.nextInt(2, 12);
    last_bread_x = next_start_x + (next_interval * 100);
    enemies.push(bread);
}

void TestScene::generate_obstacles(Blackboard &blackboard) {
    float max_x =
            blackboard.camera.position().x + blackboard.camera.size().x;
    while (last_rock_x < max_x) {
        int texturenum = blackboard.randNumGenerator.nextInt(0, 9) % 3;
        auto texture = blackboard.textureManager.get_texture("branch1");;
        if (texturenum == 0) {
            texture = blackboard.textureManager.get_texture("branch2");
        }

        auto shader = blackboard.shader_manager.get_shader("sprite");
        auto mesh = blackboard.mesh_manager.get_mesh("sprite");
        float scale = 0.9;
        auto obstacle_entity = registry_.create();
        registry_.assign<Transform>(obstacle_entity, last_rock_x - 400.f,
                                    PLATFORM_START_Y - 80.f, 0.,
                                    scale, scale);
        registry_.assign<Sprite>(obstacle_entity, texture, shader, mesh);
        registry_.assign<Obstacle>(obstacle_entity);
        registry_.assign<Collidable>(obstacle_entity, texture.width() * scale,
                                     texture.height() * scale);
        registry_.assign<Interactable>(obstacle_entity);
        registry_.assign<ObeysGravity>(obstacle_entity);
        obstacles.push(obstacle_entity);
        last_rock_x += blackboard.camera.size().x;
    }
}

void TestScene::reset_scene(Blackboard &blackboard) {
    registry_.destroy(panda_entity);
    while (!platforms.empty()) {
        uint32_t platform = platforms.front();
        registry_.destroy(platform);
        platforms.pop();
    }
    while (!obstacles.empty()) {
        uint32_t obstacle = obstacles.front();
        obstacles.pop();
        registry_.destroy(obstacle);
    }
    while (!floating_platforms.empty()) {
        uint32_t floating_platform = floating_platforms.front();
        registry_.destroy(floating_platform);
        floating_platforms.pop();
    }
    while (!enemies.empty()) {
        uint32_t enemy = enemies.front();
        registry_.destroy(enemy);
        enemies.pop();
    }
    for (uint32_t e: bg_entities) {
        registry_.destroy(e);
    }
    bg_entities.clear();
    init_scene(blackboard);
}

void TestScene::create_background(Blackboard &blackboard) {
    std::vector<Texture> textures;
    textures.reserve(4);
    // This order matters for rendering
    textures.push_back(blackboard.textureManager.get_texture("bg_top"));
    textures.push_back(blackboard.textureManager.get_texture("bg_front"));
    textures.push_back(blackboard.textureManager.get_texture("bg_middle"));
    textures.push_back(blackboard.textureManager.get_texture("bg_back"));
    // end order
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    int i = 0;
    for (Texture t: textures) {
        auto bg_entity = registry_.create();
        auto &bg = registry_.assign<Background>(bg_entity, t, shader, mesh, i);
        bg.set_pos1(0.0f, 0.0f);
        bg.set_pos2(blackboard.camera.size().x, 0.0f);
        bg.set_rotation_rad(0.0f);
        bg.set_scale(blackboard.camera.size().x / t.width(),
                     blackboard.camera.size().y / t.height());
        bg_entities.push_back(bg_entity);
        i++;
    }
}
