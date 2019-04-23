//
// Created by cowan on 14/02/19.
//

#include "vertical_scene.h"
#include "util/constants.h"
#include <algorithm>

VerticalScene::VerticalScene(Blackboard &blackboard, SceneManager &scene_manager) :
        GameScene(scene_manager),
        level_system(),
        sprite_transform_system(),
        physics_system(),
        player_movement_system(SKY_TYPE),
        player_animation_system(SKY_TYPE),
        panda_dmg_system(),
        falling_platform_system(),
        background_transform_system(SKY_TYPE),
        enemy_system(),
        enemy_animation_system(),
        text_transform_system(),
        score_system(SKY_TYPE),
        pause_menu_transform_system(),
        transition_system(SKY_TYPE),
        hud_transform_system(),
        label_system(),
        render_system(),
        powerup_system()
{
    high_score_ = 0;
    init_scene(blackboard);
    gl_has_errors("vertical_scene");
}


void VerticalScene::init_scene(Blackboard &blackboard) {
    blackboard.randNumGenerator.init(0);
    blackboard.camera.set_position(CAMERA_START_X, CAMERA_START_Y);
    blackboard.camera.compose();
    blackboard.time_multiplier = DEFAULT_SPEED_MULTIPLIER;
    create_background(blackboard);
    create_panda(blackboard);
    if (mode_ == ENDLESS) {
        create_score_text(blackboard);
        create_high_score_text(blackboard, high_score_);
        physics_system.set_story(false);
    } else if (mode_ == STORY_EASY || mode_ == STORY_HARD) {
        timer_entity = registry_.create();
        auto& timer = registry_.assign<Timer>(timer_entity);
        timer.save_watch(END_TIMER_LABEL, END_TIMER_LENGTH);
        create_lives_text(blackboard);
        physics_system.set_story(true);
    }
    create_fade_overlay(blackboard);
    auto &fadeOverlay = registry_.get<FadeOverlay>(fade_overlay_entity);
    fadeOverlay.set_alpha(1.0);
    level_system.init(mode_, registry_);
    blackboard.post_process_shader = std::make_unique<Shader>(blackboard.shader_manager.get_shader("sprite"));
}

void VerticalScene::update(Blackboard &blackboard) {
    auto &panda = registry_.get<Panda>(panda_entity);
    auto &interactable = registry_.get<Interactable>(panda_entity);
    auto &transform = registry_.get<Transform>(panda_entity);
    auto &panda_collidable = registry_.get<Collidable>(panda_entity);
    auto &fadeOverlay = registry_.get<FadeOverlay>(fade_overlay_entity);

    if (blackboard.camera.transition_ready) {
        if (fadeOverlay.alpha() < 0.9f) {
            fade_overlay_system.update(blackboard, registry_);
        } else {
            go_to_next_scene(blackboard);
            return;
        }
    }

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
    }

    if (!pause) {
        if (panda.alive && !panda.dead) {
            if (!blackboard.camera.in_transition){
                update_camera(blackboard);
                score_system.update(blackboard, registry_);
            }
            player_movement_system.update(blackboard, registry_);
        } else if (!panda.alive && interactable.grounded) {
            fade_overlay_system.update(blackboard, registry_);
        }

        if (fadeOverlay.alpha() > 0.f) {
            fade_overlay_system.update(blackboard, registry_);
        }

        if (mode_ == STORY_EASY || mode_ == STORY_HARD)
            check_end_timer();

        update_panda(blackboard);

        background_transform_system.update(blackboard, registry_);
        level_system.update(blackboard, registry_);
        physics_system.update(blackboard, registry_);
        enemy_system.update(blackboard, registry_, SKY_TYPE);
        sprite_transform_system.update(blackboard, registry_);
        health_bar_transform_system.update(blackboard, registry_);
        label_system.update(blackboard, registry_);
        text_transform_system.update(blackboard, registry_);
        player_animation_system.update(blackboard, registry_);
        enemy_animation_system.update(blackboard, registry_);
        timer_system.update(blackboard, registry_);
        falling_platform_system.update(blackboard, registry_);
        transition_system.update(blackboard, registry_);
        powerup_system.update(blackboard, registry_);
        hud_transform_system.update(blackboard, registry_); // should run last
        high_score_ = std::max<int>(high_score_, (int)blackboard.score);

        if (!blackboard.camera.transition_ready) {
            panda_dmg_system.update(blackboard, registry_);
        }
    } else {
        pause_menu_transform_system.update(blackboard, registry_);
    }
}

void VerticalScene::render(Blackboard &blackboard) {
    // update the rendering systems
    if (mode_ == STORY_HARD) {
        blackboard.window.colorScreen(vec3{105.f, 74.f, 189.f});
    } else {
        blackboard.window.colorScreen(vec3{74.f, 105.f, 189.f});
    }
    render_system.update(blackboard, registry_);
}

void VerticalScene::reset_scene(Blackboard &blackboard) {
    cleanup();
    blackboard.camera.in_transition = false;
    blackboard.camera.transition_ready = false;
    blackboard.score = 0;
    blackboard.soundManager.changeBackgroundMusic(blackboard.soundManager.currentStage);
    init_scene(blackboard);
}

void VerticalScene::cleanup() {
    level_system.destroy_entities(registry_);
    for (uint32_t e: bg_entities) {
        registry_.destroy(e);
    }
    bg_entities.clear();
    if (registry_.valid(timer_entity))
        registry_.destroy(timer_entity);
    GameScene::cleanup();
}

void VerticalScene::go_to_next_scene(Blackboard &blackboard) {
    auto &health = registry_.get<Health>(panda_entity);
    blackboard.story_health = health.health_points;
    if (mode_ == STORY_EASY) {
        blackboard.camera.set_position(0, 0);
        cleanup();
        blackboard.camera.in_transition = false;
        blackboard.camera.transition_ready = false;
        change_scene(BOSS_SCENE_ID, true);
        init_scene(blackboard);
    } else if (mode_ == STORY_HARD) {
        blackboard.camera.set_position(0, 0);
        cleanup();
        blackboard.camera.in_transition = false;
        blackboard.camera.transition_ready = false;
        change_scene(DRACULA_BOSS_SCENE_ID, true);
        init_scene(blackboard);
    }
}

void VerticalScene::create_background(Blackboard &blackboard) {
    // This order matters for rendering
    auto tex1 = blackboard.texture_manager.get_texture("clouds1");
    auto tex2 = blackboard.texture_manager.get_texture("clouds2");
    auto tex3 = blackboard.texture_manager.get_texture("horizon");
    // end order
    auto shader = blackboard.shader_manager.get_shader("sprite");
    if (mode_ == STORY_HARD) {
        shader = blackboard.shader_manager.get_shader("recolor");
    }
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    auto bg_entity1 = registry_.create();
    auto &bg = registry_.assign<Background>(bg_entity1, tex1, shader, mesh, -1);
    bg.set_pos1(200.0f, 0.0f);
    bg.set_pos2(200.0f, -blackboard.camera.size().y);
    bg.set_rotation_rad(0.0f);
    bg.set_scale(blackboard.camera.size().x / tex1.width(),
                 blackboard.camera.size().y / tex1.height());
    bg_entities.push_back(bg_entity1);
    registry_.assign<Layer>(bg_entity1, BACKGROUND_LAYER + 2);

    auto bg_entity2 = registry_.create();
    auto &bg2 = registry_.assign<Background>(bg_entity2, tex2, shader, mesh, 1);
    bg2.set_pos1(-200.0f, 0.0f);
    bg2.set_pos2(-200.f, -blackboard.camera.size().y);
    bg2.set_rotation_rad(0.0f);
    bg2.set_scale(blackboard.camera.size().x / tex2.width(),
                  blackboard.camera.size().y / tex2.height());
    bg_entities.push_back(bg_entity2);
    registry_.assign<Layer>(bg_entity2, BACKGROUND_LAYER + 1);

    auto bg_entity0 = registry_.create();
    auto &bg0 = registry_.assign<Background>(bg_entity0, tex3, shader, mesh, 0, false);
    bg0.set_pos1(0.0f, 0.0f);
    bg0.set_rotation_rad(0.0f);
    bg0.set_scale(blackboard.camera.size().x / tex3.width(),
                  blackboard.camera.size().y / tex3.height());
    bg_entities.push_back(bg_entity0);
    registry_.assign<Layer>(bg_entity0, BACKGROUND_LAYER);
}

void VerticalScene::set_mode(SceneMode mode, Blackboard &blackboard) {
    Scene::set_mode(mode, blackboard);
    reset_scene(blackboard);
}

void VerticalScene::set_high_score(int value) {
    high_score_ = value;
}

int VerticalScene::get_high_score() {
    return high_score_;
}

void VerticalScene::update_camera(Blackboard &blackboard) {
    vec2 cam_position = blackboard.camera.position();
    blackboard.camera.set_position(cam_position.x,
            cam_position.y - CAMERA_SPEED * blackboard.delta_time
    );
    blackboard.camera.compose();
}

void VerticalScene::update_panda(Blackboard &blackboard) {
    vec2 cam_position = blackboard.camera.position();
    vec2 cam_size = blackboard.camera.size();
    auto &transform = registry_.get<Transform>(panda_entity);
    auto &panda = registry_.get<Panda>(panda_entity);
    auto &panda_collidable = registry_.get<Collidable>(panda_entity);

    if (transform.y - panda_collidable.height / 2 > cam_position.y + cam_size.y / 2 ||
        panda.dead) {
        if (mode_ == ENDLESS) {
            reset_scene(blackboard);
        } else if (blackboard.story_lives > 1) {
            blackboard.story_lives -= 1;
            blackboard.story_health = MAX_HEALTH;
            reset_scene(blackboard);
        } else {
            blackboard.story_health = MAX_HEALTH;
            blackboard.story_lives = MAX_LIVES;
            blackboard.camera.set_position(0, 0);
            reset_scene(blackboard);
            change_scene(MAIN_MENU_SCENE_ID);
            return;
        }
    } else if (transform.x + panda_collidable.width / 2 > cam_position.x + cam_size.x / 2) {
        transform.x = cam_position.x + cam_size.x / 2 - panda_collidable.width / 2;
    } else if (transform.x - panda_collidable.width / 2 < cam_position.x - cam_size.x / 2) {
        transform.x = cam_position.x - cam_size.x / 2 + panda_collidable.width / 2;
    }
}

void VerticalScene::check_end_timer() {
    auto& timer = registry_.get<Timer>(timer_entity);
    if (timer.exists(END_TIMER_LABEL) && timer.is_done(END_TIMER_LABEL)) {
        level_system.generate_end_level();
        timer.remove(END_TIMER_LABEL);
    }
}
