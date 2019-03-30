//
// Created by alex on 20/01/19.
//

#include <entt/entity/registry.hpp>
#include <GL/glew.h>
#include <SDL.h>
#include <stdio.h>
#include <util/constants.h>

#include "graphics/camera.h"
#include "graphics/sprite.h"
#include "graphics/window.h"
#include "scene/scene_manager.h"
#include "scene/main_menu_scene.h"
#include "util/blackboard.h"
#include "util/random.h"
#include <scene/horizontal_scene.h>
#include <SDL_mixer.h>
#include <sstream>
#include <scene/vertical_scene.h>
#include <util/csv_reader.h>
#include <iostream>
#include <scene/boss_scene.h>
#include <graphics/health_bar.h>
#include <graphics/cave.h>
#include <graphics/font_manager.h>

int main(int argc, char** argv) {

    auto window = Window();

    window.initialize("Express Panda", 800, 450);

    Blackboard blackboard = {
        Camera(1600, 900, 0, 0),
        0,
        InputManager(),
        MeshManager(),
        ShaderManager(),
        TextureManager(),
        window,
        Random(0),
        SoundManager(),
        FontManager()
    };



    //load assets and configure

    blackboard.input_manager.track(SDL_SCANCODE_UP);
    blackboard.input_manager.track(SDL_SCANCODE_DOWN);
    blackboard.input_manager.track(SDL_SCANCODE_LEFT);
    blackboard.input_manager.track(SDL_SCANCODE_RIGHT);
    blackboard.input_manager.track(SDL_SCANCODE_SPACE);
    blackboard.input_manager.track(SDL_SCANCODE_RETURN);
    blackboard.input_manager.track(SDL_SCANCODE_ESCAPE);

    blackboard.shader_manager.load_shader(
            shaders_path("sprite.vs.glsl"),
            shaders_path("sprite.fs.glsl"),"sprite");

    blackboard.shader_manager.load_shader(
            shaders_path("sample.vs.glsl"),
            shaders_path("sample.fs.glsl"),"sample");

    blackboard.shader_manager.load_shader(
            shaders_path("health.vs.glsl"),
            shaders_path("health.fs.glsl"),"health");

    blackboard.shader_manager.load_shader(
            shaders_path("cave.vs.glsl"),
            shaders_path("cave.fs.glsl"),"cave");
  
     blackboard.shader_manager.load_shader(
            shaders_path("text.vs.glsl"),
            shaders_path("text.fs.glsl"), "text");

    blackboard.texture_manager.load_texture(textures_path("panda.png"), "panda");
    blackboard.texture_manager.load_texture(textures_path("panda_sprite_sheet.png"), "panda_sprites");
    blackboard.texture_manager.load_texture(textures_path("grass_block_1.png"), "platform1");
    blackboard.texture_manager.load_texture(textures_path("platform_center_grass.png"), "platform_center_grass");
    blackboard.texture_manager.load_texture(textures_path("grass_block_2.png"), "platform2");
    blackboard.texture_manager.load_texture(textures_path("bread_sprite_sheet.png"), "bread");
    blackboard.texture_manager.load_texture(textures_path("play_text.png"), "play_text");
    blackboard.texture_manager.load_texture(textures_path("levels_text.png"), "levels_text");
    blackboard.texture_manager.load_texture(textures_path("config_text.png"), "config_text");
    blackboard.texture_manager.load_texture(textures_path("pixel.png"), "pixel");
    blackboard.texture_manager.load_texture(textures_path("menu_full.png"), "splash");
    blackboard.texture_manager.load_texture(textures_path("ghost_sprite_sheet.png"), "ghost");
    blackboard.texture_manager.load_texture(textures_path("llama_sprite_sheet.png"), "llama");
    blackboard.texture_manager.load_texture(textures_path("spit_sprite_sheet.png"), "spit");
    blackboard.texture_manager.load_texture(textures_path("bg_back.png"), "bg_back");
    blackboard.texture_manager.load_texture(textures_path("bg_front.png"), "bg_front");
    blackboard.texture_manager.load_texture(textures_path("bg_middle.png"), "bg_middle");
    blackboard.texture_manager.load_texture(textures_path("bg_top.png"), "bg_top");
    blackboard.texture_manager.load_texture(textures_path("tutorial.png"), "tutorial");
    blackboard.texture_manager.load_texture(textures_path("tutorial2.png"), "tutorial_bread");

    blackboard.texture_manager.load_texture(textures_path("jacko_sprite_sheet.png"), "jacko");
    blackboard.texture_manager.load_texture(textures_path("burger.png"), "burger");

    blackboard.texture_manager.load_texture(textures_path("stalagmite.png"), "stalagmite");

    blackboard.texture_manager.load_texture(textures_path("clouds_1.png"), "clouds1");
    blackboard.texture_manager.load_texture(textures_path("clouds_2.png"), "clouds2");
    blackboard.texture_manager.load_texture(textures_path("sky_bg.png"), "horizon");

    blackboard.texture_manager.load_texture(textures_path("bg_grave_back.png"), "grave_back");
    blackboard.texture_manager.load_texture(textures_path("bg_grave_front.png"), "grave_front");
    blackboard.texture_manager.load_texture(textures_path("bg_grave_top.png"), "grave_top");
    blackboard.texture_manager.load_texture(textures_path("bg_grave_mid.png"), "grave_middle");

    blackboard.mesh_manager.load_mesh("health", 4, HealthBar::vertices, 6, HealthBar::indices);
    blackboard.mesh_manager.load_mesh("cave", 41, Cave::vertices, 168, Cave::indices);
    blackboard.mesh_manager.load_mesh("sprite", 4, Sprite::vertices, 6, Sprite::indices);
    blackboard.soundManager.init();

    blackboard.fontManager.load_font(fonts_path("TitilliumWeb.ttf"), "titillium_72", 72);

    auto scene_manager = SceneManager(blackboard);

    // initialize scenes here
    MainMenuScene main_menu(blackboard, scene_manager);
    main_menu.add_item(blackboard, "play_text", HORIZONTAL_SCENE_ID);

    //TODO: implement level select and config scenes
    main_menu.add_item(blackboard, "levels_text", VERTICAL_SCENE_ID);
    main_menu.add_item(blackboard, "config_text",  BOSS_SCENE_ID);
    scene_manager.add_scene(MAIN_MENU_SCENE_ID, (Scene*)(&main_menu));


    // initialize scenes here


    HorizontalScene horizontal_scene(blackboard, scene_manager);

    BossScene boss_scene(blackboard, scene_manager);

    VerticalScene vertical_scene(blackboard, scene_manager);

    scene_manager.add_scene(BOSS_SCENE_ID, (Scene*)(&boss_scene));
    scene_manager.add_scene(VERTICAL_SCENE_ID, (Scene*)(&vertical_scene));
    scene_manager.add_scene(HORIZONTAL_SCENE_ID, (Scene*)(&horizontal_scene));

    // set the first scene

    scene_manager.change_scene(MAIN_MENU_SCENE_ID);



    bool quit = false;
    while (!quit) {
        //update blackboard
        blackboard.delta_time = std::min<float>(window.delta_time(), 0.25f);
        blackboard.input_manager.update();

        scene_manager.update(blackboard);

        window.clear();
        scene_manager.render(blackboard);

        window.display();

        quit = blackboard.input_manager.should_exit();
    }

    window.destroy();
    return 0;
}
