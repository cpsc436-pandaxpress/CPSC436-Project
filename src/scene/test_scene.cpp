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
#include "test_scene.h"
#include "components/transform.h"


TestScene::TestScene(Blackboard& blackboard, SceneManager& scene_manager) :
    Scene(scene_manager),
    platforms(),
    sprite_transform_system(),
    sprite_render_system(),
    physics_system(),
    player_movement_system(),
    collision_system(),
    obstacles()
{
    init_scene(blackboard);
    gl_has_errors();
}


void TestScene::init_scene(Blackboard &blackboard) {
    srand(0);
    blackboard.camera.set_position(CAMERA_START_X, CAMERA_START_Y);
    blackboard.camera.compose();
    last_placed_x = PLATFORM_START_X;
    last_rock_x = blackboard.camera.size().x;
    create_panda(blackboard);
    create_bread(blackboard);
}

void TestScene::update(Blackboard& blackboard) {
    vec2 cam_size = blackboard.camera.size();
    vec2 cam_position = blackboard.camera.position();
    blackboard.camera.set_position(cam_position.x + CAMERA_SPEED * blackboard.delta_time, cam_position.y);
    blackboard.camera.compose();
    generate_platforms(blackboard);
    generate_obstacles(blackboard);


    auto &transform = registry_.get<Transform>(panda_entity);
    auto &panda = registry_.get<Panda>(panda_entity);
    auto &panda_collidable = registry_.get<Collidable>(panda_entity);
    auto &enemy = registry_.get<Bread>(enemy_entity);
    auto &transform_enemy = registry_.get<Transform>(enemy_entity);

    if (transform.x + panda_collidable.width < cam_position.x - cam_size.x / 2 ||
        transform.y - panda_collidable.height > cam_position.y + cam_size.y / 2 || !panda.alive) {
        reset_scene(blackboard);
    } else if (transform.x + panda_collidable.width / 2 > cam_position.x + cam_size.x / 2) {
        transform.x = cam_position.x + cam_size.x / 2 - panda_collidable.width / 2;
    }

    player_movement_system.update(blackboard, registry_);
    collision_system.update(blackboard, registry_);
    physics_system.update(blackboard, registry_);
    sprite_transform_system.update(blackboard, registry_);
}

void TestScene::render(Blackboard &blackboard) {
    // update the rendering systems
    sprite_render_system.update(blackboard, registry_);

}

void TestScene::create_panda(Blackboard &blackboard) {
    panda_entity = registry_.create();

    auto texture = blackboard.textureManager.get_texture("panda");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    float scale = 0.15f;
    registry_.assign<Transform>(panda_entity, PANDA_START_X, PANDA_START_Y, 0., scale, scale);
    registry_.assign<Sprite>(panda_entity, texture, shader);
    registry_.assign<Panda>(panda_entity);
    registry_.assign<ObeysGravity>(panda_entity);
    registry_.assign<Health>(panda_entity,1);
    registry_.assign<Interactable>(panda_entity);
    registry_.assign<CausesDamage>(panda_entity, false, true, 1);
    registry_.assign<Velocity>(panda_entity,0.f,0.f);
    registry_.assign<Collidable>(panda_entity, texture.width() * scale, texture.height() * scale);

}

void TestScene::generate_platforms(Blackboard &blackboard) {
    auto shader = blackboard.shader_manager.get_shader("sprite");
    float max_x =
            blackboard.camera.position().x + blackboard.camera.size().x; // some distance off camera
    while (last_placed_x < max_x) {
        auto texture = blackboard.textureManager.get_texture(
                (blackboard.randNumGenerator.nextInt(0, 100) % 2 == 0) ? "platform1" : "platform2");
        float scale = 50.0f / texture.width();
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
            registry_.assign<Sprite>(platform, texture, shader);
            registry_.assign<Collidable>(platform, texture.width() * scale, texture.height() * scale);

            platforms.push(platform);
        }
        last_placed_x += texture.width();
    }
}

void TestScene::create_bread(Blackboard &blackboard) {
    enemy_entity = registry_.create();
    auto texture = blackboard.textureManager.get_texture("bread");
    auto shader = blackboard.shader_manager.get_shader("sprite");

    float scale = 0.5;
    registry_.assign<Transform>(enemy_entity, 350., PANDA_START_Y - texture.height(), 0.,
                                scale, scale);
    registry_.assign<Sprite>(enemy_entity, texture, shader);
    registry_.assign<Bread>(enemy_entity);
    registry_.assign<CausesDamage>(enemy_entity, false, true, 1);
    registry_.assign<Health>(enemy_entity,1);
    registry_.assign<Velocity>(enemy_entity, -BREAD_SPEED, 0.f);
    registry_.assign<Collidable>(enemy_entity, texture.width() * scale, texture.height() * scale);
    registry_.assign<Interactable>(enemy_entity);
    registry_.assign<ObeysGravity>(enemy_entity);
}

void TestScene::generate_obstacles(Blackboard &blackboard) {
    float max_x =
            blackboard.camera.position().x + blackboard.camera.size().x;
    while (last_rock_x < max_x) {
        int texturenum = blackboard.randNumGenerator.nextInt(0, 9) % 3;
        auto texture = blackboard.textureManager.get_texture("branch1");;
        if(texturenum == 0){
             texture = blackboard.textureManager.get_texture("branch2");
        }

        auto shader = blackboard.shader_manager.get_shader("sprite");
        float scale = 0.45;
        auto obstacle_entity = registry_.create();
        registry_.assign<Transform>(obstacle_entity, last_rock_x - 400.f,
                                    PLATFORM_START_Y - 80.f, 0.,
                                    scale, scale);
        registry_.assign<Sprite>(obstacle_entity, texture, shader);
        registry_.assign<Obstacle>(obstacle_entity);
        registry_.assign<Collidable>(obstacle_entity, texture.width() * scale, texture.height() * scale);
        registry_.assign<Interactable>(obstacle_entity);
        registry_.assign<ObeysGravity>(obstacle_entity);
        obstacles.push(obstacle_entity);
        last_rock_x += 2*blackboard.camera.size().x;
    }
}

void TestScene::reset_scene(Blackboard &blackboard) {
    registry_.destroy(panda_entity);
    registry_.destroy(enemy_entity);
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
    init_scene(blackboard);
}