//
// Created by cowan on 14/02/19.
//

#include <components/obeys_gravity.h>
#include <components/health.h>
#include <components/interactable.h>
#include <components/causes_damage.h>
#include <components/velocity.h>
#include <components/platform.h>
#include "climbing_scene.h"

ClimbingScene::ClimbingScene(Blackboard &blackboard, SceneManager &scene_manager) :
        Scene(scene_manager),
        platforms(),
        sprite_transform_system(),
        sprite_render_system(),
        physics_system(),
        player_movement_system(),
        collision_system() {
    init_scene(blackboard);
    gl_has_errors();
}


void ClimbingScene::init_scene(Blackboard &blackboard) {
    blackboard.randNumGenerator.init(0);
    blackboard.camera.set_position(CAMERA_START_X, CAMERA_START_Y);
    blackboard.camera.compose();
    last_placed_x = PLATFORM_START_X;
    last_placed_x_floating = PLATFORM_START_X;

    for (int i = 0; i < 10; i++) {
        auto platform = registry_.create();

        auto texture = blackboard.textureManager.get_texture("platform1");
        auto shader = blackboard.shader_manager.get_shader("sprite");
        float scale = 100.0f / texture.width();
        registry_.assign<Transform>(platform, PLATFORM_START_X, PLATFORM_START_Y - texture.height() * scale * 3 * i , 0., scale, scale);
        registry_.assign<Sprite>(platform, texture, shader);
        registry_.assign<Platform>(platform);
        registry_.assign<Collidable>(platform, texture.width() * scale, texture.height() * scale);

        platforms.push(platform);
    }

    create_panda(blackboard);
}

void ClimbingScene::create_panda(Blackboard &blackboard) {
    panda_entity = registry_.create();

    auto texture = blackboard.textureManager.get_texture("panda");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    float scale = 0.3f;
    registry_.assign<Transform>(panda_entity, PANDA_START_X, PANDA_START_Y, 0., scale, scale);
    registry_.assign<Sprite>(panda_entity, texture, shader);
    registry_.assign<Panda>(panda_entity);
    registry_.assign<ObeysGravity>(panda_entity);
    registry_.assign<Health>(panda_entity, 1);
    registry_.assign<Interactable>(panda_entity);
    registry_.assign<CausesDamage>(panda_entity, false, true, 1);
    registry_.assign<Velocity>(panda_entity, 0.f, 0.f);
    registry_.assign<Collidable>(panda_entity, texture.width() * scale, texture.height() * scale);
}

void ClimbingScene::update(Blackboard &blackboard) {
    vec2 cam_size = blackboard.camera.size();
    vec2 cam_position = blackboard.camera.position();
    blackboard.camera.set_position(cam_position.x,
                                   cam_position.y - CAMERA_SPEED * blackboard.delta_time);
    blackboard.camera.compose();

    auto &transform = registry_.get<Transform>(panda_entity);
    auto &panda = registry_.get<Panda>(panda_entity);
    auto &panda_collidable = registry_.get<Collidable>(panda_entity);

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

void ClimbingScene::render(Blackboard &blackboard) {
    // update the rendering systems
    sprite_render_system.update(blackboard, registry_);
}

void ClimbingScene::generate_platforms(Blackboard &blackboard) {

}

void ClimbingScene::reset_scene(Blackboard &blackboard) {
    registry_.destroy(panda_entity);
    init_scene(blackboard);
}
