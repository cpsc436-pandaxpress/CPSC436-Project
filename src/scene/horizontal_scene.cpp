//
// Created by Prayansh Srivastava on 2019-02-12.
//

#include <graphics/background.h>
#include <components/obeys_gravity.h>
#include <components/health.h>
#include <components/interactable.h>
#include <components/causes_damage.h>
#include <components/velocity.h>
#include <components/tutorial.h>
#include "horizontal_scene.h"
#include "util/constants.h"

HorizontalScene::HorizontalScene(Blackboard &blackboard, SceneManager &scene_manager) :
        Scene(scene_manager),
        level_system(),
        sprite_render_system(),
        sprite_transform_system(),
        background_transform_system(),
        background_render_system(),
        physics_system(),
        player_movement_system(PlayerMovementSystem(HORIZONTAL_SCENE_ID)),
        collision_system()
{
    init_scene(blackboard);
    create_tutorial(blackboard);
    gl_has_errors();
}

void HorizontalScene::update(Blackboard &blackboard) {
    update_camera(blackboard);
    update_panda(blackboard);
    update_tutorial(blackboard);

    level_system.update(blackboard, registry_);
    background_transform_system.update(blackboard, registry_);
    player_movement_system.update(blackboard, registry_);
    collision_system.update(blackboard, registry_);
    physics_system.update(blackboard, registry_);
    sprite_transform_system.update(blackboard, registry_);
}

void HorizontalScene::update_panda(Blackboard &blackboard) {
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

void HorizontalScene::update_camera(Blackboard &blackboard) {
    vec2 cam_position = blackboard.camera.position();

    auto &panda_transform = registry_.get<Transform>(panda_entity);
    float y_offset = std::min(0.f, panda_transform.y + MAX_CAMERA_Y_DIFF);

    blackboard.camera.set_position(cam_position.x + CAMERA_SPEED * blackboard.delta_time,
                                   y_offset);
    blackboard.camera.compose();
}

void HorizontalScene::update_tutorial(Blackboard &blackboard) {
    float scaleY = 0.25;
    float scaleX = 0.25;
    auto &tutorial_trans = registry_.get<Transform>(tutorial2_entity);

    if (tutorial_trans.x + 100.f < blackboard.camera.position().x - blackboard.camera.size().x / 2.0 ){
        auto &tutorial_trans = registry_.replace<Transform>(tutorial_entity, -1500.f, -200.f, 0.f, scaleX, scaleY);
        auto &tutorial2_trans = registry_.replace<Transform>(tutorial2_entity, -1500.f,  -200.f, 0.f, scaleX, scaleY);
    }
}

void HorizontalScene::render(Blackboard &blackboard) {
    background_render_system.update(blackboard, registry_); // render background first
    sprite_render_system.update(blackboard, registry_);
}

void HorizontalScene::reset_scene(Blackboard &blackboard) {
    level_system.destroy_entities(registry_);
    registry_.destroy(panda_entity);
    for (uint32_t e: bg_entities) {
        registry_.destroy(e);
    }
    bg_entities.clear();
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
    std::vector<Texture> textures;
    textures.reserve(4);
    // This order matters for rendering
    textures.push_back(blackboard.textureManager.get_texture("bg_top"));
    textures.push_back(blackboard.textureManager.get_texture("bg_front"));
    textures.push_back(blackboard.textureManager.get_texture("bg_middle"));
    textures.push_back(blackboard.textureManager.get_texture("bg_back"));
    // end order
    auto shader = blackboard.shader_manager.get_shader("sprite");
    int i = 0;
    for (Texture t: textures) {
        auto bg_entity = registry_.create();
        auto &bg = registry_.assign<Background>(bg_entity, t, shader, i);
        bg.set_pos1(0.0f, 0.0f);
        bg.set_pos2(blackboard.camera.size().x, 0.0f);
        bg.set_rotation_rad(0.0f);
        bg.set_scale(blackboard.camera.size().x / t.width(),
                     blackboard.camera.size().y / t.height());
        bg_entities.push_back(bg_entity);
        i++;
    }
}
void HorizontalScene::create_tutorial(Blackboard &blackboard) {
    tutorial_entity = registry_.create();
    tutorial2_entity = registry_.create();

    auto texture =  blackboard.textureManager.get_texture("tutorial");
    auto texture2 =  blackboard.textureManager.get_texture("tutorial_bread");

    auto shader = blackboard.shader_manager.get_shader("sprite");

    float scaleY = 0.25;
    float scaleX = 0.25;
    registry_.assign<Sprite>(tutorial_entity, texture, shader);
    registry_.assign<Tutorial>(tutorial_entity);
    registry_.assign<Transform>(tutorial_entity, 400.f, -200.f, 0., scaleX, scaleY);

    registry_.assign<Sprite>(tutorial2_entity, texture2, shader);
    registry_.assign<Tutorial>(tutorial2_entity);
    registry_.assign<Transform>(tutorial2_entity, 900.f, -200.f, 0., scaleX, scaleY);

}





