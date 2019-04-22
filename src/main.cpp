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
#include <scene/dracula_boss_scene.h>
#include <SDL_mixer.h>
#include <sstream>
#include <scene/vertical_scene.h>
#include <util/csv_reader.h>
#include <iostream>
#include <scene/boss_scene.h>
#include <graphics/health_bar.h>
#include <graphics/cave.h>
#include <graphics/font_manager.h>
#include <util/property_reader.h>
#include <scene/story_intro_beach.h>
#include <scene/story_intro_jungle.h>
#include <scene/story_end_scene.h>



int start() {
    Window window("Express Panda");

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
        FontManager(),
        std::unique_ptr<Shader>(),
        0,
        MAX_HEALTH,
        MAX_LIVES,
        DEFAULT_SPEED_MULTIPLIER
    };



    //load assets and configure
    PropertyReader scores(data_path "/score.ini");
    if (!scores.load()) {
        scores.put("jungle", "0");
        scores.put("sky", "0");
    }


    blackboard.input_manager.track(SDL_SCANCODE_UP);
    blackboard.input_manager.track(SDL_SCANCODE_DOWN);
    blackboard.input_manager.track(SDL_SCANCODE_LEFT);
    blackboard.input_manager.track(SDL_SCANCODE_RIGHT);
    blackboard.input_manager.track(SDL_SCANCODE_SPACE);
    blackboard.input_manager.track(SDL_SCANCODE_RETURN);
    blackboard.input_manager.track(SDL_SCANCODE_ESCAPE);
    blackboard.input_manager.track(SDL_SCANCODE_A);
    blackboard.input_manager.track(SDL_SCANCODE_D);
    blackboard.input_manager.track(SDL_SCANCODE_W);
    blackboard.input_manager.track(SDL_SCANCODE_W);
    blackboard.input_manager.track(SDL_SCANCODE_5);
    blackboard.input_manager.track(SDL_SCANCODE_6);
    blackboard.input_manager.track(SDL_SCANCODE_7);
    blackboard.input_manager.track(SDL_SCANCODE_8);
    blackboard.input_manager.track(SDL_SCANCODE_9);
    blackboard.input_manager.track(SDL_SCANCODE_0);


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
            shaders_path("caveEntrance.vs.glsl"),
            shaders_path("caveEntrance.fs.glsl"),"caveEntrance");

     blackboard.shader_manager.load_shader(
            shaders_path("text.vs.glsl"),
            shaders_path("text.fs.glsl"), "text");

    blackboard.shader_manager.load_shader(
            shaders_path("fade.vs.glsl"),
            shaders_path("fade.fs.glsl"),"fade");

    // example post-process shader
    blackboard.shader_manager.load_shader(
            shaders_path("sprite.vs.glsl"),
            shaders_path("recolor.fs.glsl"),
            "recolor");

    blackboard.shader_manager.load_shader(
            shaders_path("sprite.vs.glsl"),
            shaders_path("wave.fs.glsl"),
            "wave");

    blackboard.shader_manager.load_shader(
            shaders_path("sprite.vs.glsl"),
            shaders_path("split.fs.glsl"),
            "shift");

    blackboard.shader_manager.load_shader(
            shaders_path("sprite.vs.glsl"),
            shaders_path("strobe.fs.glsl"),
            "strobe");

    blackboard.shader_manager.load_shader(
            shaders_path("shake.vs.glsl"),
            shaders_path("sprite.fs.glsl"),
            "shake");

    blackboard.texture_manager.load_texture(textures_path("panda.png"), "panda");
    blackboard.texture_manager.load_texture(textures_path("panda_sprite_sheet.png"), "panda_sprites");
    blackboard.texture_manager.load_texture(textures_path("grass_block_1.png"), "platform1");
    blackboard.texture_manager.load_texture(textures_path("platform_center_grass.png"), "platform_center_grass");
    blackboard.texture_manager.load_texture(textures_path("grass_block_2.png"), "platform2");
    blackboard.texture_manager.load_texture(textures_path("bread_sprite_sheet.png"), "bread");

    blackboard.texture_manager.load_texture(textures_path("story_text.png"), "story_text");
    blackboard.texture_manager.load_texture(textures_path("endless_jungle_text.png"), "endless_jungle_text");
    blackboard.texture_manager.load_texture(textures_path("endless_sky_text.png"), "endless_sky_text");
    blackboard.texture_manager.load_texture(textures_path("jacko_text.png"), "jacko_text");
    blackboard.texture_manager.load_texture(textures_path("pixel.png"), "pixel");
    blackboard.texture_manager.load_texture(textures_path("menu_full.png"), "splash");
    blackboard.texture_manager.load_texture(textures_path("ghost_sprite_sheet.png"), "ghost");
    blackboard.texture_manager.load_texture(textures_path("llama_sprite_sheet.png"), "llama");
    blackboard.texture_manager.load_texture(textures_path("spit_sprite_sheet.png"), "spit");
    blackboard.texture_manager.load_texture(textures_path("bg_back.png"), "bg_back");
    blackboard.texture_manager.load_texture(textures_path("bg_front.png"), "bg_front");
    blackboard.texture_manager.load_texture(textures_path("bg_middle.png"), "bg_middle");
    blackboard.texture_manager.load_texture(textures_path("bg_top.png"), "bg_top");
    blackboard.texture_manager.load_texture(textures_path("pause_menu.png"), "pause_menu");
    blackboard.texture_manager.load_texture(textures_path("dracula_sprite_sheet.png"), "dracula");
    blackboard.texture_manager.load_texture(textures_path("boss_bats.png"), "bat");
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

    blackboard.texture_manager.load_texture(textures_path("vial.png"), "vial");
    blackboard.texture_manager.load_texture(textures_path("shield.png"), "shield");
  
    blackboard.texture_manager.load_texture(textures_path("story_beach_back.png"), "beach_back");
    blackboard.texture_manager.load_texture(textures_path("story_beach_front.png"), "beach_front");
    blackboard.texture_manager.load_texture(textures_path("story_beach_water_1.png"), "beach_water_1");
    blackboard.texture_manager.load_texture(textures_path("story_beach_water_2.png"), "beach_water_2");
    blackboard.texture_manager.load_texture(textures_path("story_beach_water_3.png"), "beach_water_3");
    blackboard.texture_manager.load_texture(textures_path("story_beach_water_4.png"), "beach_water_4");
    blackboard.texture_manager.load_texture(textures_path("story_beach_kelly.png"), "beach_kelly");
    blackboard.texture_manager.load_texture(textures_path("story_beach_panda.png"), "beach_panda");
    blackboard.texture_manager.load_texture(textures_path("story_beach_hearts.png"), "beach_hearts");
    blackboard.texture_manager.load_texture(textures_path("story_beach_jacko.png"), "beach_jacko");
    blackboard.texture_manager.load_texture(textures_path("skip_scene.png"), "skip_scene");


    blackboard.texture_manager.load_texture(textures_path("castle_back.png"), "castle_back");
    blackboard.texture_manager.load_texture(textures_path("castle_front.png"), "castle_front");


    blackboard.texture_manager.load_texture(textures_path("story_jungle_background.png"), "story_jungle_background");
    blackboard.texture_manager.load_texture(textures_path("story_jungle_panda.png"), "story_jungle_panda");
    blackboard.texture_manager.load_texture(textures_path("story_jungle_kelly.png"), "story_jungle_kelly");
    blackboard.texture_manager.load_texture(textures_path("story_jungle_grass.png"), "story_jungle_grass");
    blackboard.texture_manager.load_texture(textures_path("story_jungle_vape.png"), "story_jungle_vape");

    blackboard.texture_manager.load_texture(textures_path("story_end_background.png"), "story_end_background");
    blackboard.texture_manager.load_texture(textures_path("story_end_kelly.png"), "story_end_kelly");
    blackboard.texture_manager.load_texture(textures_path("story_ending_panda_sprite_sheet.png"), "story_ending_panda");

    blackboard.texture_manager.load_texture(textures_path("solid_block_1.png"), "solid_block_1");
    blackboard.texture_manager.load_texture(textures_path("solid_block_2.png"), "solid_block_2");
    blackboard.texture_manager.load_texture(textures_path("falling_blocks_1.png"), "falling_blocks_1");
    blackboard.texture_manager.load_texture(textures_path("falling_blocks_2.png"), "falling_blocks_2");
    blackboard.texture_manager.load_texture(textures_path("dirt_1.png"), "dirt_1");
    blackboard.texture_manager.load_texture(textures_path("dirt_2.png"), "dirt_2");
    blackboard.texture_manager.load_texture(textures_path("grass_1.png"), "grass_1");
    blackboard.texture_manager.load_texture(textures_path("grass_2.png"), "grass_2");

    blackboard.mesh_manager.load_mesh("health", 4, HealthBar::vertices, 6, HealthBar::indices);
    blackboard.mesh_manager.load_mesh("cave", 41, Cave::vertices, 168, Cave::indices);
    blackboard.mesh_manager.load_mesh("caveEntrance", 4, CaveEntrance::vertices, 9, CaveEntrance::indices);
    blackboard.mesh_manager.load_mesh("sprite", 4, Sprite::vertices, 6, Sprite::indices);
    blackboard.soundManager.init();

    blackboard.fontManager.load_font(fonts_path("TitilliumWeb.ttf"), "titillium_72", 72);

    auto scene_manager = SceneManager(blackboard);

    // initialize scenes here
    MainMenuScene main_menu(blackboard, scene_manager);
    main_menu.add_item(blackboard, "story_text", STORY_BEACH_INTRO_SCENE_ID);
    main_menu.add_item(blackboard, "endless_jungle_text", ENDLESS_JUNGLE_SCENE_ID);
    main_menu.add_item(blackboard, "endless_sky_text", ENDLESS_SKY_SCENE_ID);
//    main_menu.add_item(blackboard, "jacko_text",  BOSS_SCENE_ID);
    scene_manager.add_scene(MAIN_MENU_SCENE_ID, (Scene*)(&main_menu));


    // initialize scenes here


    HorizontalScene horizontal_scene(blackboard, scene_manager);
    horizontal_scene.set_high_score(std::stoi(scores.get("jungle")));

    BossScene boss_scene(blackboard, scene_manager);
    DraculaBossScene dracula_boss_scene(blackboard, scene_manager);

    VerticalScene vertical_scene(blackboard, scene_manager);
    vertical_scene.set_high_score(std::stoi(scores.get("sky")));

    StoryIntroBeachScene story_beach_intro_scene(blackboard, scene_manager);

    StoryIntroJungleScene story_jungle_intro_scene(blackboard, scene_manager);

    StoryEndScene story_end_scene(blackboard, scene_manager);

    scene_manager.add_scene(STORY_EASY_JUNGLE_SCENE_ID, (Scene*)(&horizontal_scene), STORY_EASY);
    scene_manager.add_scene(ENDLESS_JUNGLE_SCENE_ID, (Scene*)(&horizontal_scene), ENDLESS);
    scene_manager.add_scene(ENDLESS_SKY_SCENE_ID, (Scene*)(&vertical_scene), ENDLESS);
    scene_manager.add_scene(BOSS_SCENE_ID, (Scene*)(&boss_scene), JACKO);
    scene_manager.add_scene(DRACULA_BOSS_SCENE_ID, (Scene*)(&dracula_boss_scene), DRACULA);
    scene_manager.add_scene(STORY_BEACH_INTRO_SCENE_ID, (Scene*)(&story_beach_intro_scene), STORY_EASY);
    scene_manager.add_scene(STORY_JUNGLE_INTRO_SCENE_ID, (Scene*)(&story_jungle_intro_scene), STORY_EASY);
    scene_manager.add_scene(STORY_EASY_SKY_SCENE_ID, (Scene*)(&vertical_scene), STORY_EASY);
    scene_manager.add_scene(STORY_HARD_JUNGLE_SCENE_ID, (Scene*)(&horizontal_scene), STORY_HARD);
    scene_manager.add_scene(STORY_HARD_SKY_SCENE_ID, (Scene*)(&vertical_scene), STORY_HARD);
    scene_manager.add_scene(STORY_END_SCENE_ID, (Scene*)(&story_end_scene), STORY_EASY);

    // set the first scene

    scene_manager.change_scene(MAIN_MENU_SCENE_ID);

    blackboard.post_process_shader = std::make_unique<Shader>(blackboard.shader_manager.get_shader("sprite"));

    bool quit = false;
    while (!quit) {
        //update blackboard
        blackboard.delta_time = std::min<float>(window.delta_time(), 0.25f) * blackboard.time_multiplier;
        blackboard.input_manager.update();

        scene_manager.update(blackboard);

        window.clear();
        scene_manager.render(blackboard);

        window.display(
            *blackboard.post_process_shader,
            blackboard.mesh_manager.get_mesh("sprite")
        );

        quit = blackboard.input_manager.should_exit();
    }
    scores.put("jungle", std::to_string(horizontal_scene.get_high_score()));
    scores.put("sky", std::to_string(vertical_scene.get_high_score()));
    scores.save();
    window.destroy();
    return 0;
}

int main(int argc, char** argv) {
    int init = !SDL_Init(0);

    if (init) {
        int result = start();
        SDL_Quit();

        return result;
    } else {
        return EXIT_FAILURE;
    }
}
