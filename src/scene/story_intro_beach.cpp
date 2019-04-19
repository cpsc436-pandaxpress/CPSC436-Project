//
// Created by Avery Brown on 2019-04-09.
//


#include <graphics/background.h>
#include <components/hearts.h>
#include <components/transform.h>
#include <components/jacko.h>
#include <components/panda.h>
#include <components/kelly.h>
#include <components/timer.h>
#include <components/pause_menu.h>
#include <components/timer.h>
#include <components/layer.h>
#include <graphics/fade_overlay.h>
#include <components/hud_element.h>
#include "story_intro_beach.h"
#include "util/constants.h"

std::string const StoryIntroBeachScene::BEACH_SCENE_END_LABEL = "end_scene";

StoryIntroBeachScene::StoryIntroBeachScene(Blackboard &blackboard, SceneManager &scene_manager) :
        GameScene(scene_manager),
        sprite_transform_system(),
        story_animation_system(),
        timer_system(),
        physics_system(),
        fade_overlay_system(),
        pause_menu_transform_system(),
        render_system(),
        background_transform_system(STORY_TYPE)
{
    init_scene(blackboard);
    gl_has_errors();
}

void StoryIntroBeachScene::update(Blackboard &blackboard) {

    if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_ESCAPE)) {
        if (pause) {
            pause = false;
            registry_.destroy(pause_menu_entity);
        } else {
            pause = true;
            create_pause_menu(blackboard);
        }
    } else if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_RETURN) && pause) {
        blackboard.camera.set_position(0, 0);
        reset_scene(blackboard);
        registry_.destroy(pause_menu_entity);
        change_scene(MAIN_MENU_SCENE_ID);
        pause = false;
        return;
    } else if (blackboard.input_manager.key_just_pressed(SDL_SCANCODE_RETURN) && !pause) {
        reset_scene(blackboard);
        change_scene(STORY_JUNGLE_INTRO_SCENE_ID);
    }

    auto &fadeOverlay = registry_.get<FadeOverlay>(fade_overlay_entity);

    if (!pause) {
        story_animation_system.update(blackboard, registry_);
        sprite_transform_system.update(blackboard, registry_);
        timer_system.update(blackboard, registry_);
        scene_timer.update(blackboard.delta_time);
        physics_system.update(blackboard, registry_);
        background_transform_system.update(blackboard, registry_);
        if (endScene || (!endScene && fadeOverlay.alpha() > 0.f)) {
            fade_overlay_system.update(blackboard, registry_);
        }
    } else {
        pause_menu_transform_system.update(blackboard, registry_);
    }

    if (scene_timer.exists(BEACH_SCENE_END_LABEL) && scene_timer.is_done(BEACH_SCENE_END_LABEL)) {
        scene_timer.remove(BEACH_SCENE_END_LABEL);
        endScene = true;
    }

    if (scene_timer.exists(SKIP_SCENE_LABEL) && scene_timer.is_done(SKIP_SCENE_LABEL)) {
        scene_timer.remove(SKIP_SCENE_LABEL);
        auto &velocity = registry_.get<Velocity>(skip_entity);
        velocity.x_velocity = SKIP_SPEED;
    }

    if (fadeOverlay.alpha() > 1.6f) {
        reset_scene(blackboard);
        change_scene(STORY_JUNGLE_INTRO_SCENE_ID);
    }

}

void StoryIntroBeachScene::render(Blackboard &blackboard) {
    render_system.update(blackboard, registry_);
}

void StoryIntroBeachScene::init_scene(Blackboard &blackboard) {
    endScene = false;

    create_background(blackboard);
    create_panda(blackboard);
    create_kelly(blackboard);
    create_hearts(blackboard);
    create_jacko(blackboard);
    create_skip_message(blackboard);
    create_fade_overlay(blackboard);
    auto &fadeOverlay = registry_.get<FadeOverlay>(fade_overlay_entity);
    fadeOverlay.set_alpha(1.0);

    if (!scene_timer.exists(BEACH_SCENE_END_LABEL)) {
        scene_timer.save_watch(BEACH_SCENE_END_LABEL, BEACH_SCENE_END);
    }

    if (!scene_timer.exists(SKIP_SCENE_LABEL)) {
        scene_timer.save_watch(SKIP_SCENE_LABEL, SKIP_SCENE);
    }
}

void StoryIntroBeachScene::reset_scene(Blackboard &blackboard) {
    registry_.destroy(panda_entity);
    registry_.destroy(skip_entity);
    if (!story_animation_system.jackoGrabsKelly) {
        registry_.destroy(kelly_entity);
        registry_.destroy(hearts_entity);
    }
    registry_.destroy(jacko_entity);
    for (uint32_t e: bg_entities) {
        registry_.destroy(e);
    }
    bg_entities.clear();
    registry_.destroy<FadeOverlay>();
    if (scene_timer.exists(BEACH_SCENE_END_LABEL) && !scene_timer.is_done(BEACH_SCENE_END_LABEL)) {
        scene_timer.remove(BEACH_SCENE_END_LABEL);
    }
    if (scene_timer.exists(SKIP_SCENE_LABEL) && !scene_timer.is_done(SKIP_SCENE_LABEL)) {
        scene_timer.remove(SKIP_SCENE_LABEL);
    }
    init_scene(blackboard);
}

void StoryIntroBeachScene::create_panda(Blackboard &blackboard) {
    panda_entity = registry_.create();
    auto texture = blackboard.texture_manager.get_texture("beach_panda");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 180.0f / texture.height();
    float scaleX = 220.0f / texture.width();
    registry_.assign<Transform>(panda_entity, PANDA_POS_X, PANDA_POS_Y, 0., scaleX, scaleY);
    registry_.assign<Sprite>(panda_entity, texture, shader, mesh);
    registry_.assign<Panda>(panda_entity);
    registry_.assign<Layer>(panda_entity, PANDA_LAYER);
}

void StoryIntroBeachScene::create_kelly(Blackboard &blackboard) {
    kelly_entity = registry_.create();
    auto texture = blackboard.texture_manager.get_texture("beach_kelly");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 250.0f / texture.height();
    float scaleX = 280.0f / texture.width();
    registry_.assign<Transform>(kelly_entity, KELLY_POS_X, KELLY_POS_Y, 0., scaleX, scaleY);
    registry_.assign<Sprite>(kelly_entity, texture, shader, mesh);
    registry_.assign<Kelly>(kelly_entity);
    registry_.assign<Timer>(kelly_entity);
    registry_.assign<Layer>(kelly_entity, PANDA_LAYER);
}

void StoryIntroBeachScene::create_hearts(Blackboard &blackboard) {
    hearts_entity = registry_.create();
    auto texture = blackboard.texture_manager.get_texture("beach_hearts");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 100.0f / texture.height();
    float scaleX = 100.0f / texture.width();
    registry_.assign<Transform>(hearts_entity, HEARTS_POS_X, HEARTS_POS_Y, 0., scaleX, scaleY);
    registry_.assign<Sprite>(hearts_entity, texture, shader, mesh);
    registry_.assign<Hearts>(hearts_entity);
    registry_.assign<Timer>(hearts_entity);
    registry_.assign<Layer>(hearts_entity, PANDA_LAYER);
}

void StoryIntroBeachScene::create_jacko(Blackboard &blackboard) {
    jacko_entity = registry_.create();

    auto texture = blackboard.texture_manager.get_texture("beach_jacko");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 500.0f / texture.height();
    float scaleX = 700.0f / texture.width();
    registry_.assign<Transform>(jacko_entity, JACKO_START_X, JACKO_START_Y, 0., scaleX, scaleY);
    registry_.assign<Sprite>(jacko_entity, texture, shader, mesh);
    registry_.assign<Jacko>(jacko_entity);
    registry_.assign<Velocity>(jacko_entity, 0.f, 0.f);
    registry_.assign<Layer>(jacko_entity, ENEMY_LAYER);
}

void StoryIntroBeachScene::create_background(Blackboard &blackboard) {
    std::vector<Texture> textures;
    textures.reserve(6);
    // This order matters for rendering
    textures.push_back(blackboard.texture_manager.get_texture("beach_front"));
    textures.push_back(blackboard.texture_manager.get_texture("beach_water_1"));
    textures.push_back(blackboard.texture_manager.get_texture("beach_water_2"));
    textures.push_back(blackboard.texture_manager.get_texture("beach_water_3"));
    textures.push_back(blackboard.texture_manager.get_texture("beach_water_4"));
    textures.push_back(blackboard.texture_manager.get_texture("beach_back"));
    // end order
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    int i = 0;
    for (Texture t: textures) {
        auto bg_entity = registry_.create();
        auto &bg = registry_.assign<Background>(bg_entity, t, shader, mesh, i, false);
        registry_.assign<Layer>(bg_entity, BACKGROUND_LAYER - i);
        bg.set_pos1(0.0f, 0.0f);
        bg.set_rotation_rad(0.0f);
        bg.set_scale(blackboard.camera.size().x / t.width(),
                     blackboard.camera.size().y / t.height());
        bg_entities.push_back(bg_entity);
        i++;
    }
}

void StoryIntroBeachScene::create_skip_message(Blackboard &blackboard) {
    skip_entity = registry_.create();

    auto texture = blackboard.texture_manager.get_texture("skip_scene");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 80.0f / texture.height();
    float scaleX = 400.0f / texture.width();
    registry_.assign<Transform>(skip_entity, SKIP_POS_X, SKIP_POS_Y, 0., scaleX, scaleY);
    registry_.assign<Sprite>(skip_entity, texture, shader, mesh);
    registry_.assign<Velocity>(skip_entity, 0.f, 0.f);
    registry_.assign<Layer>(skip_entity, OVERLAY_LAYER);
}