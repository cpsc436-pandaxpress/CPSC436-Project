//
// Created by Avery Brown on 2019-04-19.
//

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
#include "story_end_scene.h"
#include "util/constants.h"

std::string const StoryEndScene::END_SCENE_END_LABEL = "end_scene";

StoryEndScene::StoryEndScene(Blackboard &blackboard, SceneManager &scene_manager) :
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
    blackboard.story_health = MAX_HEALTH;
    blackboard.story_lives = MAX_LIVES;
}

void StoryEndScene::update(Blackboard &blackboard) {

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
        fade_overlay_system.update(blackboard, registry_);
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

    if (scene_timer.exists(END_SCENE_END_LABEL) && scene_timer.is_done(END_SCENE_END_LABEL)) {
        scene_timer.remove(END_SCENE_END_LABEL);
        endScene = true;
    }

    auto &velocity = registry_.get<Velocity>(skip_entity);
    auto &transform = registry_.get<Transform>(skip_entity);

    if (scene_timer.exists(SKIP_SCENE_LABEL) && scene_timer.is_done(SKIP_SCENE_LABEL)) {
        scene_timer.remove(SKIP_SCENE_LABEL);
        auto &velocity = registry_.get<Velocity>(skip_entity);
        velocity.x_velocity = SKIP_SPEED;
    } else {
        if (transform.x < 570.f) {
            velocity.x_velocity = 0.f;
        }
    }

    if (fadeOverlay.alpha() > 2.0f) {
        reset_scene(blackboard);
        change_scene(MAIN_MENU_SCENE_ID);
    }

}

void StoryEndScene::render(Blackboard &blackboard) {
    render_system.update(blackboard, registry_);
}

void StoryEndScene::init_scene(Blackboard &blackboard) {
    endScene = false;

    create_background(blackboard);
    create_panda(blackboard);
    create_kelly(blackboard);
    create_skip_message(blackboard);
    create_fade_overlay(blackboard);
    auto &fadeOverlay = registry_.get<FadeOverlay>(fade_overlay_entity);
    fadeOverlay.set_alpha(1.0);

    if (!scene_timer.exists(END_SCENE_END_LABEL)) {
        scene_timer.save_watch(END_SCENE_END_LABEL, END_SCENE_END);
    }

    if (!scene_timer.exists(SKIP_SCENE_LABEL)) {
        scene_timer.save_watch(SKIP_SCENE_LABEL, SKIP_SCENE);
    }
    blackboard.story_health = 3;
    blackboard.story_lives = 3;
}

void StoryEndScene::reset_scene(Blackboard &blackboard) {
    registry_.destroy(skip_entity);
    registry_.destroy(kelly_entity);
    registry_.destroy<FadeOverlay>();
    registry_.destroy(background_entity);
    if (story_animation_system.pandaHugging == 0) {
        registry_.destroy(panda_entity);
    }
    if (scene_timer.exists(END_SCENE_END_LABEL) && !scene_timer.is_done(END_SCENE_END_LABEL)) {
        scene_timer.remove(END_SCENE_END_LABEL);
    }
    if (scene_timer.exists(SKIP_SCENE_LABEL) && !scene_timer.is_done(SKIP_SCENE_LABEL)) {
        scene_timer.remove(SKIP_SCENE_LABEL);
    }
    init_scene(blackboard);
}

void StoryEndScene::create_panda(Blackboard &blackboard) {
    panda_entity = registry_.create();
    auto texture = blackboard.texture_manager.get_texture("story_ending_panda");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 330.0f / texture.height();
    float scaleX = 360.0f / texture.width();
    registry_.assign<Transform>(panda_entity, PANDA_POS_X, PANDA_POS_Y, 0., scaleX, scaleY);
    registry_.assign<Sprite>(panda_entity, texture, shader, mesh);
    registry_.assign<Panda>(panda_entity);
    registry_.assign<Velocity>(panda_entity, 200.f, 0.f);
    registry_.assign<Timer>(panda_entity);
    registry_.assign<Layer>(panda_entity, PANDA_LAYER);
}

void StoryEndScene::create_kelly(Blackboard &blackboard) {
    kelly_entity = registry_.create();
    auto texture = blackboard.texture_manager.get_texture("story_end_kelly");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 550.0f / texture.height();
    float scaleX = 800.0f / texture.width();
    registry_.assign<Transform>(kelly_entity, KELLY_POS_X, KELLY_POS_Y, 0., scaleX, scaleY);
    registry_.assign<Sprite>(kelly_entity, texture, shader, mesh);
    registry_.assign<Kelly>(kelly_entity);
    registry_.assign<Layer>(kelly_entity, PANDA_LAYER);
}


void StoryEndScene::create_background(Blackboard &blackboard) {
    auto texture_background = blackboard.texture_manager.get_texture("story_end_background");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    auto cam_size = blackboard.camera.size();

    background_entity = registry_.create();
    auto &background = registry_.assign<Sprite>(background_entity, texture_background, shader, mesh);
    registry_.assign<Layer>(background_entity, BACKGROUND_LAYER);
    background.set_size((int)cam_size.x, (int)cam_size.y);
    background.set_pos(0, 0);

}

void StoryEndScene::create_skip_message(Blackboard &blackboard) {
    skip_entity = registry_.create();

    auto texture = blackboard.texture_manager.get_texture("skip_scene");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 80.0f / texture.height();
    float scaleX = 400.0f / texture.width();
    registry_.assign<Transform>(skip_entity, SKIP_POS_X, SKIP_POS_Y, 0., scaleX, scaleY);
    registry_.assign<Sprite>(skip_entity, texture, shader, mesh);
    registry_.assign<Velocity>(skip_entity, -SKIP_SPEED, 0.f);
    registry_.assign<Layer>(skip_entity, OVERLAY_LAYER);
}