//
// Created by Avery Brown on 2019-04-13.
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
#include <components/vape.h>
#include <graphics/fade_overlay.h>
#include <components/hud_element.h>
#include "story_intro_jungle.h"
#include "util/constants.h"

std::string const StoryIntroJungleScene::JUNGLE_SCENE_END_LABEL = "end_scene";

StoryIntroJungleScene::StoryIntroJungleScene(Blackboard &blackboard, SceneManager &scene_manager) :
        GameScene(scene_manager),
        sprite_transform_system(),
        story_animation_system(),
        timer_system(),
        physics_system(),
        fade_overlay_system(),
        pause_menu_transform_system(),
        render_system()
{
    init_scene(blackboard);
    gl_has_errors();
}

void StoryIntroJungleScene::update(Blackboard &blackboard) {

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
        change_scene(STORY_EASY_JUNGLE_SCENE_ID);
    }

    auto &fadeOverlay = registry_.get<FadeOverlay>(fade_overlay_entity);

    if (!pause) {
        story_animation_system.update(blackboard, registry_);
        sprite_transform_system.update(blackboard, registry_);
        timer_system.update(blackboard, registry_);
        scene_timer.update(blackboard.delta_time);
        physics_system.update(blackboard, registry_);
        if (endScene || (!endScene && fadeOverlay.alpha() > 0.f)) {
            fade_overlay_system.update(blackboard, registry_);
        }
        if (story_animation_system.pandaGetsVape == 1) {
            create_strobe_effect(blackboard);
        }
    } else {
        pause_menu_transform_system.update(blackboard, registry_);
    }

    if (scene_timer.exists(SCENE_END_LABEL) && scene_timer.is_done(SCENE_END_LABEL)) {
        scene_timer.remove(SCENE_END_LABEL);
        endScene = true;
    }

    if (scene_timer.exists(SKIP_SCENE_LABEL) && scene_timer.is_done(SKIP_SCENE_LABEL)) {
        scene_timer.remove(SKIP_SCENE_LABEL);
        auto &velocity = registry_.get<Velocity>(skip_entity);
        velocity.x_velocity = SKIP_SPEED;
    }

    if ((endScene && !pause) || (!endScene && fadeOverlay.alpha() > 0.f && !pause)) {
        fade_overlay_system.update(blackboard, registry_);
    }

    if (fadeOverlay.alpha() > 1.6f) {
        reset_scene(blackboard);
        change_scene(STORY_EASY_JUNGLE_SCENE_ID);
    }

    update_strobe_effect(blackboard);

}

void StoryIntroJungleScene::render(Blackboard &blackboard) {
    render_system.update(blackboard, registry_);
}

void StoryIntroJungleScene::init_scene(Blackboard &blackboard) {
    endScene = false;

    create_background(blackboard);
    create_panda(blackboard);
    create_skip_message(blackboard);
    create_fade_overlay(blackboard);
    create_vape(blackboard);
    create_kelly(blackboard);
    auto &fadeOverlay = registry_.get<FadeOverlay>(fade_overlay_entity);
    fadeOverlay.set_alpha(1.2);

    if (!scene_timer.exists(SCENE_END_LABEL)) {
        scene_timer.save_watch(SCENE_END_LABEL, SCENE_END);
    }

    if (!scene_timer.exists(SKIP_SCENE_LABEL)) {
        scene_timer.save_watch(SKIP_SCENE_LABEL, SKIP_SCENE);
    }

}

void StoryIntroJungleScene::reset_scene(Blackboard &blackboard) {
    registry_.destroy(panda_entity);
    registry_.destroy(kelly_entity);
    if (story_animation_system.pandaGetsVape == 0) {
        registry_.destroy(vape_entity);
    }
    registry_.destroy(skip_entity);
    registry_.destroy(background_entity);
    registry_.destroy<FadeOverlay>();
    if (scene_timer.exists(SCENE_END_LABEL) && !scene_timer.is_done(SCENE_END_LABEL)) {
        scene_timer.remove(SCENE_END_LABEL);
    }
    if (scene_timer.exists(STROBE_LABEL) && !scene_timer.is_done(STROBE_LABEL)) {
        scene_timer.remove(STROBE_LABEL);
    }
    if (scene_timer.exists(SKIP_SCENE_LABEL) && !scene_timer.is_done(SKIP_SCENE_LABEL)) {
        scene_timer.remove(SKIP_SCENE_LABEL);
    }
    init_scene(blackboard);
}

void StoryIntroJungleScene::create_panda(Blackboard &blackboard) {
    panda_entity = registry_.create();
    auto texture = blackboard.texture_manager.get_texture("story_jungle_panda");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 1000.0f / texture.height();
    float scaleX = 1170.0f / texture.width();
    registry_.assign<Transform>(panda_entity, PANDA_POS_X, PANDA_POS_Y, 0., scaleX, scaleY);
    registry_.assign<Sprite>(panda_entity, texture, shader, mesh);
    registry_.assign<Panda>(panda_entity);
    registry_.assign<Timer>(panda_entity);
    registry_.assign<Velocity>(panda_entity, 0.f, 0.f);
    registry_.assign<Layer>(panda_entity, PANDA_LAYER);
}

void StoryIntroJungleScene::create_kelly(Blackboard &blackboard) {
    kelly_entity = registry_.create();
    auto texture = blackboard.texture_manager.get_texture("story_jungle_kelly");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 300.0f / texture.height();
    float scaleX = 400.0f / texture.width();
    registry_.assign<Transform>(kelly_entity, KELLY_POS_X, KELLY_POS_Y, 0., scaleX, scaleY);
    registry_.assign<Sprite>(kelly_entity, texture, shader, mesh);
    registry_.assign<Kelly>(kelly_entity);
    registry_.assign<Layer>(kelly_entity, PANDA_LAYER);
}

void StoryIntroJungleScene::create_background(Blackboard &blackboard) {
    auto texture_background = blackboard.texture_manager.get_texture("story_jungle_background");
    auto texture_grass = blackboard.texture_manager.get_texture("story_jungle_grass");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    auto cam_size = blackboard.camera.size();

    background_entity = registry_.create();
    auto &background = registry_.assign<Sprite>(background_entity, texture_background, shader, mesh);
    registry_.assign<Layer>(background_entity, BACKGROUND_LAYER);
    background.set_size((int)cam_size.x, (int)cam_size.y);
    background.set_pos(0, 0);

    grass_entity = registry_.create();
    auto &grass = registry_.assign<Sprite>(grass_entity, texture_grass, shader, mesh);
    registry_.assign<Layer>(grass_entity, OVERLAY_LAYER - 5);
    grass.set_size((int)cam_size.x, (int)cam_size.y);
    grass.set_pos(0, 0);
}


void StoryIntroJungleScene::create_skip_message(Blackboard &blackboard) {
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

void StoryIntroJungleScene::create_vape(Blackboard &blackboard) {
    vape_entity = registry_.create();
    auto texture = blackboard.texture_manager.get_texture("story_jungle_vape");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 750.0f / texture.height();
    float scaleX = 950.0f / texture.width();
    registry_.assign<Transform>(vape_entity, VAPE_POS_X, VAPE_POS_Y, 0., scaleX, scaleY);
    registry_.assign<Sprite>(vape_entity, texture, shader, mesh);
    registry_.assign<Vape>(vape_entity);
    registry_.assign<Velocity>(vape_entity, 0.f, 0.f);
    registry_.assign<Layer>(vape_entity, PANDA_LAYER-1);
}

void StoryIntroJungleScene::create_strobe_effect(Blackboard &blackboard) {
    scene_timer.save_watch("STROBE", STROBE); // 5 second timer for effect
    blackboard.post_process_shader = std::make_unique<Shader>(
            blackboard.shader_manager.get_shader("strobe"));
}

void StoryIntroJungleScene::update_strobe_effect(Blackboard &blackboard) {
    if (scene_timer.exists("STROBE")) {
        float val = ((3*(scene_timer.get_target_time("STROBE") - scene_timer.get_curr_time()) /
                STROBE)); // Ratio of time done (Ranges from [1...0])
        blackboard.post_process_shader->bind();
        blackboard.post_process_shader->set_uniform_float("timeElapsed", val);
        blackboard.post_process_shader->unbind();
        // Setup new timeElapsed Uniform
        if (scene_timer.is_done("STROBE")) {
            blackboard.post_process_shader = std::make_unique<Shader>(
                    blackboard.shader_manager.get_shader("sprite"));
        }
    }
}
