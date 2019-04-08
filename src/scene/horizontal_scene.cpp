//
// Created by Prayansh Srivastava on 2019-02-12.
//

#include <graphics/background.h>
#include <graphics/health_bar.h>
#include <graphics/cave.h>
#include <graphics/text.h>
#include <graphics/fade_overlay.h>
#include "horizontal_scene.h"
#include "util/constants.h"
#include <algorithm>

HorizontalScene::HorizontalScene(Blackboard &blackboard, SceneManager &scene_manager) :
        GameScene(scene_manager),
        level_system(),
        sprite_transform_system(),
        background_transform_system(JUNGLE_TYPE),
        physics_system(),
        player_movement_system(JUNGLE_TYPE),
        enemy_system(),
        player_animation_system(JUNGLE_TYPE),
        panda_dmg_system(),
        falling_platform_system(),
        enemy_animation_system(),
        health_bar_transform_system(),
        text_transform_system(),
        score_system(JUNGLE_TYPE),
        pause_menu_transform_system(),
        transition_system(JUNGLE_TYPE),
        hud_transform_system(),
        label_system(),
        render_system()
{
    high_score_ = 0;
    init_scene(blackboard);
    gl_has_errors("horizontal_scene");
}

void HorizontalScene::update(Blackboard &blackboard) {
    auto &panda = registry_.get<Panda>(panda_entity);
    auto &interactable = registry_.get<Interactable>(panda_entity);
    if (blackboard.camera.transition_ready) {
        go_to_next_scene(blackboard);
        return;
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
            if (!blackboard.camera.in_transition) {
                update_camera(blackboard);
                background_transform_system.update(blackboard, registry_);
            }
            player_movement_system.update(blackboard, registry_);
        } else if (!panda.alive && interactable.grounded) {
            fade_overlay_system.update(blackboard, registry_);
        }
        update_panda(blackboard);

        level_system.update(blackboard, registry_);
        physics_system.update(blackboard, registry_);
        panda_dmg_system.update(blackboard, registry_);
        sprite_transform_system.update(blackboard, registry_);
        enemy_system.update(blackboard, registry_, JUNGLE_TYPE);
        health_bar_transform_system.update(blackboard, registry_);
        player_animation_system.update(blackboard, registry_);
        score_system.update(blackboard, registry_);
        text_transform_system.update(blackboard, registry_);
        label_system.update(blackboard, registry_);
        timer_system.update(blackboard, registry_);
        falling_platform_system.update(blackboard, registry_);
        enemy_animation_system.update(blackboard, registry_);
        transition_system.update(blackboard, registry_);
        hud_transform_system.update(blackboard, registry_);// Must run last
        high_score_ = std::max<int>(high_score_, (int) blackboard.score);
    } else {
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
    render_system.update(blackboard, registry_);
}

void HorizontalScene::reset_scene(Blackboard &blackboard) {
    cleanup();
    blackboard.camera.in_transition = false;
    blackboard.camera.transition_ready = false;
    blackboard.score = 0;
    init_scene(blackboard);
}

void HorizontalScene::cleanup() {
    level_system.destroy_entities(registry_);
    for (uint32_t e: bg_entities) {
        registry_.destroy(e);
    }
    bg_entities.clear();
    GameScene::cleanup();
}

void HorizontalScene::go_to_next_scene(Blackboard &blackboard) {
    cleanup();
    blackboard.camera.in_transition = false;
    blackboard.camera.transition_ready = false;
    change_scene(STORY_SKY_SCENE_ID);
    init_scene(blackboard);
}

void HorizontalScene::init_scene(Blackboard &blackboard) {
    blackboard.randNumGenerator.init(0);
    blackboard.camera.set_position(CAMERA_START_X, CAMERA_START_Y);
    blackboard.camera.compose();
    create_background(blackboard);
    create_panda(blackboard);
    if (mode_ == ENDLESS) {
        create_score_text(blackboard);
        create_high_score_text(blackboard, high_score_);
    }
    create_fade_overlay(blackboard);
    level_system.init();
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
        registry_.assign<Layer>(bg_entity, BACKGROUND_LAYER - i);
        bg.set_pos1(0.0f, 0.0f);
        bg.set_pos2(blackboard.camera.size().x, 0.0f);
        bg.set_rotation_rad(0.0f);
        bg.set_scale(blackboard.camera.size().x / t.width(),
                     blackboard.camera.size().y / t.height());
        bg_entities.push_back(bg_entity);
        i++;
    }
}

void HorizontalScene::set_mode(SceneMode mode) {
    Scene::set_mode(mode);
    level_system.set_mode(mode);
}

void HorizontalScene::set_high_score(int value) {
    high_score_ = value;
}

int HorizontalScene::get_high_score() {
    return high_score_;
}





