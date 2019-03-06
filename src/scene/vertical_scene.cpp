//
// Created by cowan on 14/02/19.
//

#include <components/obeys_gravity.h>
#include <components/health.h>
#include <components/interactable.h>
#include <components/causes_damage.h>
#include <components/velocity.h>
#include <components/platform.h>
#include <graphics/font.h>
#include <graphics/text.h>
#include <components/score.h>
#include "vertical_scene.h"
#include "util/constants.h"

VerticalScene::VerticalScene(Blackboard &blackboard, SceneManager &scene_manager) :
        Scene(scene_manager),
        level_system(),
        sprite_transform_system(),
        sprite_render_system(),
        physics_system(),
        player_movement_system(VERTICAL_SCENE_ID),
        player_animation_system(VERTICAL_SCENE_ID),
        collision_system(),
        text_transform_system(),
        text_render_system(),
        score_system(VERTICAL_SCENE_ID) {
    init_scene(blackboard);
    gl_has_errors();
}


void VerticalScene::init_scene(Blackboard &blackboard) {
    blackboard.randNumGenerator.init(0);
    blackboard.camera.set_position(CAMERA_START_X, CAMERA_START_Y);
    blackboard.camera.compose();
    create_panda(blackboard);
    create_score_text(blackboard);
    level_system.init();
}

void VerticalScene::create_panda(Blackboard &blackboard) {
    panda_entity = registry_.create();

    auto texture = blackboard.texture_manager.get_texture("panda_sprites");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 75.0 / texture.height();
    float scaleX = 75.0 / texture.width();
    registry_.assign<Transform>(panda_entity, PANDA_START_X, PANDA_START_Y, 0., scaleX, scaleY);
    registry_.assign<Sprite>(panda_entity, texture, shader, mesh);
    registry_.assign<Panda>(panda_entity);
    registry_.assign<ObeysGravity>(panda_entity);
    registry_.assign<Health>(panda_entity, 1);
    registry_.assign<Interactable>(panda_entity);
    registry_.assign<CausesDamage>(panda_entity, false, true, 1);
    registry_.assign<Velocity>(panda_entity, 0.f, 0.f);
    registry_.assign<Collidable>(panda_entity, texture.width() * scaleX, texture.height() * scaleY);
}

void VerticalScene::update(Blackboard &blackboard) {
    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_ESCAPE)) {
        blackboard.camera.set_position(0, 0);
        reset_scene(blackboard);
        change_scene(MAIN_MENU_SCENE_ID);
        return;
    }

    vec2 cam_size = blackboard.camera.size();
    vec2 cam_position = blackboard.camera.position();
    blackboard.camera.set_position(cam_position.x,
                                   cam_position.y - CAMERA_SPEED * blackboard.delta_time);
    blackboard.camera.compose();

    auto &transform = registry_.get<Transform>(panda_entity);
    auto &panda = registry_.get<Panda>(panda_entity);
    auto &panda_collidable = registry_.get<Collidable>(panda_entity);

    if (transform.y - panda_collidable.height / 2 > cam_position.y + cam_size.y / 2 || !panda.alive) {
        reset_scene(blackboard);
    } else if (transform.x + panda_collidable.width / 2 > cam_position.x + cam_size.x / 2) {
        transform.x = cam_position.x + cam_size.x / 2 - panda_collidable.width / 2;
    } else if (transform.x - panda_collidable.width / 2 < cam_position.x - cam_size.x / 2) {
        transform.x = cam_position.x - cam_size.x / 2 + panda_collidable.width / 2;
    }

    level_system.update(blackboard, registry_);
    player_movement_system.update(blackboard, registry_);
    collision_system.update(blackboard, registry_);
    physics_system.update(blackboard, registry_);
    sprite_transform_system.update(blackboard, registry_);
    score_system.update(blackboard, registry_);
    text_transform_system.update(blackboard, registry_);
    player_animation_system.update(blackboard, registry_);
    timer_system.update(blackboard, registry_);
}

void VerticalScene::render(Blackboard &blackboard) {
    // update the rendering systems
    sprite_render_system.update(blackboard, registry_);
    text_render_system.update(blackboard, registry_);
}

void VerticalScene::reset_scene(Blackboard &blackboard) {
    registry_.destroy(panda_entity);
    level_system.destroy_entities(registry_);
    registry_.destroy(score_entity);
    init_scene(blackboard);
}

void VerticalScene::create_score_text(Blackboard &blackboard) {
    auto shader = blackboard.shader_manager.get_shader("text");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    FontType font = FontType();
    font.load(fonts_path("TitilliumWeb-Bold.ttf"), 48);

    score_entity = registry_.create();
    std::string textVal = "SCORE: 0";
    auto &text = registry_.assign<Text>(score_entity, shader, mesh, font, textVal);
    registry_.assign<Transform>(score_entity, 0., 0., 0., 1.f, 1.f);
    registry_.assign<Score>(score_entity);
}
