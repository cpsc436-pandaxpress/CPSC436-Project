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
#include "story_intro.h"
#include "util/constants.h"

StoryIntroScene::StoryIntroScene(Blackboard &blackboard, SceneManager &scene_manager) :
        Scene(scene_manager),
        sprite_render_system(),
        sprite_transform_system(),
        story_animation_system(),
        timer_system(),
        fade_overlay_system(),
        fade_overlay_render_system(),
        pause_menu_transform_system(),
        pause_menu_render_system()
{
    init_scene(blackboard);
//    reset_scene(blackboard); // idk why??? but this is required
    gl_has_errors();
}

void StoryIntroScene::update(Blackboard &blackboard) {

//    auto cam_size = blackboard.camera.size();
//    background.set_size((int)cam_size.x, (int)cam_size.y);
//    background.set_pos(0, 0);

//    auto &panda = registry_.get<Panda>(panda_entity);
//    auto &fadeOverlay = registry_.get<FadeOverlay>(fade_overlay_entity);
//    auto &interactable = registry_.get<Interactable>(panda_entity);

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
//        reset_scene(blackboard);
        registry_.destroy(pause_menu_entity);
        change_scene(MAIN_MENU_SCENE_ID);
        pause = false;
        return;
    }

    if (!pause) {
//        if (panda.alive && !panda.dead) {
//            update_camera(blackboard);
//        }
//        update_panda(blackboard);
        story_animation_system.update(blackboard, registry_);
        sprite_transform_system.update(blackboard, registry_);
        timer_system.update(blackboard, registry_);
    }
}

void StoryIntroScene::render(Blackboard &blackboard) {
//    glClearColor(30.f / 256.f, 55.f / 256.f, 153.f / 256.f, 1); // same colour as the top of the background
//    glClear(GL_COLOR_BUFFER_BIT);
    sprite_render_system.update(blackboard, registry_);

    if (pause){
        pause_menu_render_system.update(blackboard, registry_);
    }

}

void StoryIntroScene::update_panda(Blackboard &blackboard) {

}

void StoryIntroScene::init_scene(Blackboard &blackboard) {
//    blackboard.camera.set_position(CAMERA_START_X, CAMERA_START_Y);
//    blackboard.camera.compose();
    create_background(blackboard);
    create_panda(blackboard);
    create_kelly(blackboard);
    create_hearts(blackboard);

    //    create_jacko(blackboard, panda_entity);
//    create_fade_overlay(blackboard);
}
//
//void StoryIntroScene::reset_scene(Blackboard &blackboard) {
//    registry_.destroy(panda_entity);
//    registry_.destroy(jacko_entity);
//    registry_.destroy(fade_overlay_entity);
//    for (uint32_t e: bg_entities) {
//        registry_.destroy(e);
//    }
//    bg_entities.clear();
//    init_scene(blackboard);
//}

//
void StoryIntroScene::create_panda(Blackboard &blackboard) {
    panda_entity = registry_.create();
    auto texture = blackboard.texture_manager.get_texture("beach_panda");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    float scaleY = 200.0f / texture.height();
    float scaleX = 280.0f / texture.width();
    registry_.assign<Transform>(panda_entity, PANDA_POS_X, PANDA_POS_Y, 0., scaleX, scaleY);
    registry_.assign<Sprite>(panda_entity, texture, shader, mesh);
    registry_.assign<Panda>(panda_entity);
    registry_.assign<Timer>(panda_entity);
    registry_.assign<Layer>(panda_entity, PANDA_LAYER);
}

void StoryIntroScene::create_kelly(Blackboard &blackboard) {
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

void StoryIntroScene::create_hearts(Blackboard &blackboard) {
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

//void StoryIntroScene::create_jacko(Blackboard &blackboard, uint32_t target) {
//    jacko_entity = registry_.create();
//
//    auto texture = blackboard.texture_manager.get_texture("jacko");
//    auto shader = blackboard.shader_manager.get_shader("sprite");
//    auto mesh = blackboard.mesh_manager.get_mesh("sprite");
//
//    float scaleY = 200.0f / texture.height();
//    float scaleX = 200.0f / texture.width();
//    registry_.assign<Transform>(jacko_entity, -300, -300, 0., scaleX, scaleY);
//    registry_.assign<Sprite>(jacko_entity, texture, shader, mesh);
//    registry_.assign<Jacko>(jacko_entity);
//    registry_.assign<Health>(jacko_entity, 10);
//    registry_.assign<Velocity>(jacko_entity, 0.f, 0.f);
//    registry_.assign<Layer>(jacko_entity, ENEMY_LAYER);
//}

void StoryIntroScene::create_background(Blackboard &blackboard) {
    auto texture = blackboard.texture_manager.get_texture("beach_background");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    background_entity = registry_.create();
    auto &background = registry_.assign<Sprite>(background_entity, texture, shader, mesh);
    registry_.assign<Layer>(background_entity, TERRAIN_LAYER);
    auto cam_size = blackboard.camera.size();
    background.set_size((int)cam_size.x, (int)cam_size.y);
    background.set_pos(0, 0);

}

//void StoryIntroScene::create_fade_overlay(Blackboard &blackboard) {
//    fade_overlay_entity = registry_.create();
//    auto shaderFade = blackboard.shader_manager.get_shader("fade");
//    auto meshFade = blackboard.mesh_manager.get_mesh("health");
//    float height = blackboard.camera.size().y;
//    float width = blackboard.camera.size().x;
//    vec2 size = {width, height};
//    auto &fade = registry_.assign<FadeOverlay>(fade_overlay_entity, meshFade, shaderFade, size);
//}

void StoryIntroScene::create_pause_menu(Blackboard &blackboard) {
    pause_menu_entity = registry_.create();

    auto texture = blackboard.texture_manager.get_texture("pause_menu");
    auto shader = blackboard.shader_manager.get_shader("sprite");
    auto mesh = blackboard.mesh_manager.get_mesh("sprite");

    registry_.assign<Sprite>(pause_menu_entity, texture, shader, mesh);
    registry_.assign<PauseMenu>(pause_menu_entity);
//    registry_.assign<Transform>(pause_menu_entity, 0., 0., 0.,
//            blackboard.camera.size().x / texture.width(), blackboard.camera.size().y / (2*texture.height()));
}






