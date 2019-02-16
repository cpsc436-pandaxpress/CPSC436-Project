//
// Created by Prayansh Srivastava on 2019-02-12.
//

#include <graphics/background.h>
#include <components/obeys_gravity.h>
#include <components/health.h>
#include <components/interactable.h>
#include <components/causes_damage.h>
#include <components/velocity.h>
#include "horizontal_scene.h"

HorizontalScene::HorizontalScene(Blackboard &blackboard, SceneManager &scene_manager) :
        Scene(scene_manager),
        level_system(),
        sprite_render_system(),
        sprite_transform_system(),
        background_transform_system(),
        background_render_system(),
        physics_system(),
        player_movement_system(),
        collision_system()
{
    init_scene(blackboard);
    gl_has_errors();
}

void HorizontalScene::update(Blackboard &blackboard) {
    vec2 cam_position = blackboard.camera.position();
    blackboard.camera.set_position(cam_position.x + CAMERA_SPEED * blackboard.delta_time,
                                   cam_position.y);
    blackboard.camera.compose();
    level_system.update(blackboard, registry_);
    background_transform_system.update(blackboard, registry_);
    player_movement_system.update(blackboard, registry_);
    collision_system.update(blackboard, registry_);
    physics_system.update(blackboard, registry_);
    sprite_transform_system.update(blackboard, registry_);
}

void HorizontalScene::render(Blackboard &blackboard) {
    background_render_system.update(blackboard, registry_); // render background first
    sprite_render_system.update(blackboard, registry_);
}

void HorizontalScene::reset_scene(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    level_system.destroy_entities(registry);
    init_scene(blackboard);
}

void HorizontalScene::init_scene(Blackboard &blackboard) {
    blackboard.randNumGenerator.init(0);
    blackboard.camera.set_position(CAMERA_START_X, CAMERA_START_Y);
    blackboard.camera.compose();
    create_background(blackboard);
    create_panda(blackboard);
}

void HorizontalScene::create_panda(Blackboard &blackboard) {
    panda_entity = registry_.create();

    auto texture = blackboard.textureManager.get_texture("panda");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    float scaleY = 100.0 / texture.height();
    float scaleX = 100.0 / texture.width();
    registry_.assign<Transform>(panda_entity, PANDA_START_X, PANDA_START_Y, 0., scaleX, scaleY);
    registry_.assign<Sprite>(panda_entity, texture, shader);
    registry_.assign<Panda>(panda_entity);
    registry_.assign<ObeysGravity>(panda_entity);
    registry_.assign<Health>(panda_entity, 1);
    registry_.assign<Interactable>(panda_entity);
    registry_.assign<CausesDamage>(panda_entity, false, true, 1);
    registry_.assign<Velocity>(panda_entity, 0.f, 0.f);
    registry_.assign<Collidable>(panda_entity, texture.width() * scaleX, texture.height() * scaleY);
}

void HorizontalScene::create_background(Blackboard &blackboard) {
    auto texture = blackboard.textureManager.get_texture("bg");
    auto shader = blackboard.shader_manager.get_shader("sprite");

    bg_entity = registry_.create();
    auto &bg = registry_.assign<Background>(bg_entity, texture, shader);
    bg.set_pos1(0.0f, 0.0f);
    bg.set_pos2(blackboard.camera.size().x, 0.0f);
    bg.set_rotation_rad(0.0f);
    bg.set_scale(blackboard.camera.size().x / texture.width(),
                 blackboard.camera.size().y / texture.height());
}
