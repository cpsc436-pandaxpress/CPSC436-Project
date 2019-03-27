//
// Created by Prayansh Srivastava on 2019-02-12.
//

#include <graphics/background.h>
#include <components/food.h>
#include <components/obeys_gravity.h>
#include <components/health.h>
#include <components/interactable.h>
#include <components/falling_platform.h>
#include <components/causes_damage.h>
#include <components/velocity.h>
#include <components/jacko.h>
#include <components/chases.h>
#include <components/timer.h>
#include <components/tutorial.h>
#include <components/timer.h>
#include <graphics/health_bar.h>
#include "boss_scene.h"
#include "util/constants.h"

BossScene::BossScene(Blackboard &blackboard, SceneManager &scene_manager) :
        Scene(scene_manager),
        level_system(),
        sprite_render_system(),
        sprite_transform_system(),
        background_transform_system(BOSS_SCENE_ID),
        background_render_system(),
        physics_system(),
        player_movement_system(BOSS_SCENE_ID),
        chase_system(),
        jacko_ai_system(blackboard, registry_),
        player_animation_system(BOSS_SCENE_ID),
        timer_system(),
        panda_dmg_system(),
        falling_platform_system(),
        enemy_animation_system(),
        health_bar_render_system(),
        health_bar_transform_system(),
        a_star_system()
        {
    init_scene(blackboard);
    reset_scene(blackboard); // idk why??? but this is required
    gl_has_errors();
}

void BossScene::update(Blackboard &blackboard) {
    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_ESCAPE)) {
        blackboard.camera.set_position(0, 0);
        reset_scene(blackboard);
        change_scene(MAIN_MENU_SCENE_ID);
        return;
    }

    update_camera(blackboard);
    update_panda(blackboard);

    level_system.update(blackboard, registry_);
    chase_system.update(blackboard, registry_);
    player_movement_system.update(blackboard, registry_);
    physics_system.update(blackboard, registry_);
    panda_dmg_system.update(blackboard, registry_);
    health_bar_transform_system.update(blackboard, registry_);
    jacko_ai_system.update(blackboard, registry_);
    sprite_transform_system.update(blackboard, registry_);
    player_animation_system.update(blackboard, registry_);
    enemy_animation_system.update(blackboard, registry_);
    timer_system.update(blackboard, registry_);
    falling_platform_system.update(blackboard, registry_);
    background_transform_system.update(blackboard, registry_);
    a_star_system.update(blackboard, registry_);
}

void BossScene::render(Blackboard &blackboard) {
    glClearColor(30.f / 256.f, 55.f / 256.f, 153.f / 256.f, 1); // same colour as the top of the background
    glClear(GL_COLOR_BUFFER_BIT);
    background_render_system.update(blackboard, registry_); // render background first
    sprite_render_system.update(blackboard, registry_);
    health_bar_render_system.update(blackboard, registry_);
}

void BossScene::update_panda(Blackboard &blackboard) {
    vec2 cam_position = blackboard.camera.position();
    vec2 cam_size = blackboard.camera.size();

    auto &transform = registry_.get<Transform>(panda_entity);
    auto &panda = registry_.get<Panda>(panda_entity);
    auto &panda_collidable = registry_.get<Collidable>(panda_entity);

    if (transform.y - panda_collidable.height > cam_position.y + cam_size.y / 2 || !panda.alive) {
        reset_scene(blackboard);
    }
}

void BossScene::update_camera(Blackboard &blackboard) {
    auto &panda_transform = registry_.get<Transform>(panda_entity);
    float y_offset = std::min(0.f, panda_transform.y + MAX_CAMERA_Y_DIFF);

    //blackboard.camera.set_position(panda_transform.x, y_offset);
    blackboard.camera.compose();
}

void BossScene::init_scene(Blackboard &blackboard) {
    blackboard.randNumGenerator.init(0);
    blackboard.camera.set_position(CAMERA_START_X, CAMERA_START_Y);
    blackboard.camera.compose();
    create_background(blackboard);
    create_food(blackboard);
    create_jacko(blackboard, burger_entity);
    create_panda(blackboard);
    level_system.init();
}

void BossScene::reset_scene(Blackboard &blackboard) {
    level_system.destroy_entities(registry_);
    registry_.destroy(panda_entity);
    registry_.destroy(jacko_entity);
    for (uint32_t e: bg_entities) {
        registry_.destroy(e);
    }
    bg_entities.clear();
    init_scene(blackboard);
}


void BossScene::create_panda(Blackboard &blackboard) {
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
    registry_.assign<Health>(panda_entity, 3);
    registry_.assign<Interactable>(panda_entity);
    registry_.assign<CausesDamage>(panda_entity, PANDA_DMG_MASK, 1);
    registry_.assign<Velocity>(panda_entity, 0.f, 0.f);
    registry_.assign<Collidable>(panda_entity, texture.width() * scaleX, texture.height() * scaleY);
    registry_.assign<Timer>(panda_entity);
    auto shaderHealth = blackboard.shader_manager.get_shader("health");
    auto meshHealth = blackboard.mesh_manager.get_mesh("health");
    float height = 75.f;
    float width = 750.f;
    vec2 size = {width, height};
    vec2 scale = {0.5, 0.5};
    auto &healthbar = registry_.assign<HealthBar>(panda_entity,
                                                  meshHealth, shaderHealth, size, scale);
}

void BossScene::create_jacko(Blackboard &blackboard, uint32_t target) {
    jacko_entity = registry_.create();

    auto texture = blackboard.texture_manager.get_texture("jacko");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 200.0 / texture.height();
    float scaleX = 200.0 / texture.width();
    registry_.assign<Transform>(jacko_entity, -300, -300, 0., scaleX, scaleY);
    registry_.assign<Sprite>(jacko_entity, texture, shader, mesh);
    registry_.assign<Jacko>(jacko_entity);
    registry_.assign<Chases>(jacko_entity, target);
    registry_.assign<Health>(jacko_entity, 10);
    registry_.assign<Interactable>(jacko_entity);
    registry_.assign<CausesDamage>(jacko_entity, TOP_VULNERABLE_MASK, 1);
    registry_.assign<Velocity>(jacko_entity, 0.f, 0.f);
    registry_.assign<Collidable>(jacko_entity,
                                 texture.width() * scaleX * 0.75,
                                 texture.height() * scaleY
    );

    auto shaderHealth = blackboard.shader_manager.get_shader("health");
    auto meshHealth = blackboard.mesh_manager.get_mesh("health");
    float height = 75.f;
    float width = 750.f;
    vec2 size = {width, height};
    vec2 scale = {0.3, 0.3};
    auto &healthbar = registry_.assign<HealthBar>(jacko_entity,
                                                  meshHealth, shaderHealth, size, scale);
}

void BossScene::create_food(Blackboard &blackboard) {
    burger_entity = registry_.create();

    auto texture = blackboard.texture_manager.get_texture("burger");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 50.0 / texture.height();
    float scaleX = 50.0 / texture.width();
    registry_.assign<Transform>(burger_entity, 300, 100, 0., scaleX, scaleY);
    registry_.assign<Sprite>(burger_entity, texture, shader, mesh);
    registry_.assign<Food>(burger_entity);
    registry_.assign<Interactable>(burger_entity);
    registry_.assign<ObeysGravity>(burger_entity);
    registry_.assign<Velocity>(burger_entity);
    registry_.assign<Collidable>(burger_entity, texture.width() * scaleX,
                                 texture.height() * scaleY);

}

void BossScene::create_background(Blackboard &blackboard) {
    std::vector<Texture> textures;
    textures.reserve(4);
    // This order matters for rendering
    textures.push_back(blackboard.texture_manager.get_texture("grave_top"));
    textures.push_back(blackboard.texture_manager.get_texture("grave_middle"));
    textures.push_back(blackboard.texture_manager.get_texture("grave_front"));
    textures.push_back(blackboard.texture_manager.get_texture("grave_back"));
    // end order
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    int i = 0;
    int indices[4] = {3, 1, 2, 0};
    for (Texture t: textures) {
        auto bg_entity = registry_.create();
        auto &bg = registry_.assign<Background>(bg_entity, t, shader, mesh, indices[i], false);
        bg.set_pos1(0.0f, 0.0f);
        bg.set_rotation_rad(0.0f);
        bg.set_scale(blackboard.camera.size().x / t.width(),
                     blackboard.camera.size().y / t.height());
        bg_entities.push_back(bg_entity);
        i++;
    }

}





