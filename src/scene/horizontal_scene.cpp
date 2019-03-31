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
#include <components/timer.h>
#include <graphics/health_bar.h>
#include <graphics/cave.h>
#include <graphics/text.h>
#include <graphics/fade_overlay.h>
#include <components/score.h>
#include <components/layer.h>
#include "horizontal_scene.h"
#include "util/constants.h"

HorizontalScene::HorizontalScene(Blackboard &blackboard, SceneManager &scene_manager) :
        Scene(scene_manager),
        level_system(),
        sprite_render_system(),
        sprite_transform_system(),
        background_transform_system(HORIZONTAL_SCENE_ID),
        background_render_system(),
        physics_system(),
        player_movement_system(HORIZONTAL_SCENE_ID),
        enemy_system(),
        player_animation_system(HORIZONTAL_SCENE_ID),
        panda_dmg_system(),
        falling_platform_system(),
        enemy_animation_system(),
        health_bar_render_system(),
        cave_render_system(),
        health_bar_transform_system(),
        text_render_system(),
        text_transform_system(),
        score_system(HORIZONTAL_SCENE_ID),
        pause_menu_transform_system() {
    init_scene(blackboard);
    gl_has_errors("horizontal_scene");
}

void HorizontalScene::update(Blackboard &blackboard) {
    auto &panda = registry_.get<Panda>(panda_entity);
    auto &fadeOverlay = registry_.get<FadeOverlay>(fade_overlay_entity);
    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_ESCAPE) && pause_horizontal) {
        blackboard.camera.set_position(0, 0);
        reset_scene(blackboard);
        registry_.destroy(pause_menu_entity);
        change_scene(MAIN_MENU_SCENE_ID);
        pause_horizontal = false;
        fadeOverlay.set_alpha(0.f);
        fadeOverlay.set_pause(false);
        return;
    } else if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_ESCAPE) && !pause_horizontal) {
        pause_horizontal = true;
        fadeOverlay.set_pause(true);
        create_pause_menu(blackboard);
    } else if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_RETURN) && pause_horizontal) {
        pause_horizontal = false;
        fadeOverlay.set_pause(false);
        fadeOverlay.set_alpha(0.f);
        registry_.destroy(pause_menu_entity);
    } else if (!panda.alive) {
        fade_overlay_system.update(blackboard, registry_);
    }
    if (!pause_horizontal) {
        if (panda.alive && !panda.dead) {
            update_camera(blackboard);
            fadeOverlay.set_alpha(0.f);
            background_transform_system.update(blackboard, registry_);
            player_movement_system.update(blackboard, registry_);
        }
        update_panda(blackboard);

        level_system.update(blackboard, registry_);
        physics_system.update(blackboard, registry_);
        panda_dmg_system.update(blackboard, registry_);
        sprite_transform_system.update(blackboard, registry_);
        enemy_system.update(blackboard, registry_, HORIZONTAL_SCENE_ID);
        health_bar_transform_system.update(blackboard, registry_);
        player_animation_system.update(blackboard, registry_);
        score_system.update(blackboard, registry_);
        text_transform_system.update(blackboard, registry_);
        timer_system.update(blackboard, registry_);
        falling_platform_system.update(blackboard, registry_);
        enemy_animation_system.update(blackboard, registry_);
    } else {
        fade_overlay_system.update(blackboard, registry_);
        pause_menu_transform_system.update(blackboard, registry_);
    }
}

void HorizontalScene::update_panda(Blackboard &blackboard) {
    vec2 cam_position = blackboard.camera.position();
    vec2 cam_size = blackboard.camera.size();

    auto &transform = registry_.get<Transform>(panda_entity);
    auto &panda = registry_.get<Panda>(panda_entity);
    auto &panda_collidable = registry_.get<Collidable>(panda_entity);
    auto &panda_timer = registry_.get<Timer>(panda_entity);

    if (transform.x + panda_collidable.width < cam_position.x - cam_size.x / 2 ||
        transform.y - panda_collidable.height > cam_position.y + cam_size.y / 2 || panda.dead) {
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

void HorizontalScene::render(Blackboard &blackboard) {
    glClearColor(19.f / 256.f, 136.f / 256.f, 126.f / 256.f, 1); // same colour as the top of the background
    glClear(GL_COLOR_BUFFER_BIT);
    background_render_system.update(blackboard, registry_); // render background first
    cave_render_system.update(blackboard, registry_);
    sprite_render_system.update(blackboard, registry_);
    health_bar_render_system.update(blackboard, registry_);
    text_render_system.update(blackboard, registry_);

    auto &panda = registry_.get<Panda>(panda_entity);
    auto &interactable = registry_.get<Interactable>(panda_entity);
    if ((!panda.alive && interactable.grounded) || pause_horizontal) {
        fade_overlay_render_system.update(blackboard, registry_);
    }
}

void HorizontalScene::reset_scene(Blackboard &blackboard) {
    level_system.destroy_entities(registry_);
    registry_.destroy(panda_entity);
    for (uint32_t e: bg_entities) {
        registry_.destroy(e);
    }
    bg_entities.clear();
    registry_.destroy(score_entity);
    registry_.destroy(fade_overlay_entity);
    init_scene(blackboard);
}

void HorizontalScene::init_scene(Blackboard &blackboard) {
    blackboard.randNumGenerator.init(0);
    blackboard.camera.set_position(CAMERA_START_X, CAMERA_START_Y);
    blackboard.camera.compose();
    create_background(blackboard);
    create_panda(blackboard);
    create_score_text(blackboard);
    create_fade_overlay(blackboard);
    level_system.init();
}

void HorizontalScene::create_panda(Blackboard &blackboard) {
    panda_entity = registry_.create();

    auto texture = blackboard.texture_manager.get_texture("panda_sprites");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
    auto sprite = Sprite(texture, shader, mesh);


    float scaleY = 75.0f / texture.height();
    float scaleX = 75.0f / texture.width();
    registry_.assign<Transform>(panda_entity, PANDA_START_X, PANDA_START_Y, 0., scaleX, scaleY);
    registry_.assign<Sprite>(panda_entity, sprite);
    registry_.assign<Panda>(panda_entity);
    registry_.assign<ObeysGravity>(panda_entity);
    registry_.assign<Health>(panda_entity, 3);
    registry_.assign<Interactable>(panda_entity);
    registry_.assign<CausesDamage>(panda_entity, PANDA_DMG_MASK, 1);
    registry_.assign<Velocity>(panda_entity, 0.f, 0.f);
    registry_.assign<Timer>(panda_entity);
    registry_.assign<Collidable>(panda_entity, texture.width() * scaleX, texture.height() * scaleY);
    registry_.assign<Layer>(panda_entity, PANDA_LAYER);

    auto shaderHealth = blackboard.shader_manager.get_shader("health");
    auto meshHealth = blackboard.mesh_manager.get_mesh("health");
    float height = 75.f;
    float width = 750.f;
    vec2 size = {width, height};
    vec2 scale = {0.5, 0.5};
    auto &healthbar = registry_.assign<HealthBar>(panda_entity,
                                                  meshHealth, shaderHealth, size, scale);
}

void HorizontalScene::create_background(Blackboard &blackboard) {
    std::vector<Texture> textures;
    textures.reserve(4);
    // This order matters for rendering
    textures.push_back(blackboard.texture_manager.get_texture("bg_top"));
    textures.push_back(blackboard.texture_manager.get_texture("bg_front"));
    textures.push_back(blackboard.texture_manager.get_texture("bg_middle"));
    textures.push_back(blackboard.texture_manager.get_texture("bg_back"));
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

void HorizontalScene::create_score_text(Blackboard &blackboard) {
    auto shader = blackboard.shader_manager.get_shader("text");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    FontType font = FontType();
    font.load(fonts_path("TitilliumWeb-Bold.ttf"), 64);

    score_entity = registry_.create();
    std::string textVal = "SCORE: 0";
    auto &text = registry_.assign<Text>(score_entity, shader, mesh, font, textVal);
    registry_.assign<Transform>(score_entity, 0., 0., 0., 1.f, 1.f);
    registry_.assign<Score>(score_entity);
}

void HorizontalScene::create_fade_overlay(Blackboard &blackboard) {
    fade_overlay_entity = registry_.create();
    auto shaderFade = blackboard.shader_manager.get_shader("fade");
    auto meshFade = blackboard.mesh_manager.get_mesh("health");
    float height = blackboard.camera.size().y;
    float width = blackboard.camera.size().x;
    vec2 size = {width, height};
    auto &fade = registry_.assign<FadeOverlay>(fade_overlay_entity, meshFade, shaderFade, size);
    registry_.assign<Layer>(fade_overlay_entity, FADE_OVERLAY_LAYER);
}

void HorizontalScene::create_pause_menu(Blackboard &blackboard) {
    pause_menu_entity = registry_.create();

    auto texture = blackboard.texture_manager.get_texture("pause_menu");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    registry_.assign<Sprite>(pause_menu_entity, texture, shader, mesh);
    registry_.assign<Tutorial>(pause_menu_entity);
    registry_.assign<Layer>(pause_menu_entity, PAUSE_MENU_LAYER);
}






