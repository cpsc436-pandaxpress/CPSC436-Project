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
#include "scene/test_scene.h"
#include "util/blackboard.h"
#include "util/random.h"


static const SceneID MAIN_MENU_SCENE_ID   = 0;
static const SceneID PLAY_SCENE_ID        = 1;
static const SceneID CONFIG_SCENE_ID      = 2;

int main(int argc, char** argv) {

    auto window = Window();

    window.initialize("Express Panda", 800, 600);

    Blackboard blackboard = {
        Camera(1600, 1200, 0, 0),
        0,
        InputManager(),
        ShaderManager(),
        TextureManager(),
        window,
        Random(0)
    };

    auto scene_manager = SceneManager();

    //load assets and configure

    blackboard.input_manager.track(SDL_SCANCODE_UP);
    blackboard.input_manager.track(SDL_SCANCODE_DOWN);
    blackboard.input_manager.track(SDL_SCANCODE_LEFT);
    blackboard.input_manager.track(SDL_SCANCODE_RIGHT);
    blackboard.input_manager.track(SDL_SCANCODE_SPACE);
    blackboard.input_manager.track(SDL_SCANCODE_RETURN);

    blackboard.shader_manager.load_shader(
            shaders_path("sprite.vs.glsl"),
            shaders_path("sprite.fs.glsl"),
            "sprite"
    );

    blackboard.textureManager.load_texture(textures_path("panda.png"), "panda");
    blackboard.textureManager.load_texture(textures_path("grass_block_1.png"), "platform1");
    blackboard.textureManager.load_texture(textures_path("grass_block_2.png"), "platform2");
    blackboard.textureManager.load_texture(textures_path("bread.png"), "bread");
    blackboard.textureManager.load_texture(textures_path("play_text.png"), "play_text");
    blackboard.textureManager.load_texture(textures_path("levels_text.png"), "levels_text");
    blackboard.textureManager.load_texture(textures_path("config_text.png"), "config_text");
    blackboard.textureManager.load_texture(textures_path("pixel.png"), "pixel");
    blackboard.textureManager.load_texture(textures_path("gross_splash.png"), "splash");


    // initialize scenes here
    //TODO: implement the following:

    MainMenuScene main_menu(blackboard, scene_manager);
    main_menu.add_item(blackboard, "play_text", PLAY_SCENE_ID);

    //TODO: implement level select and config scenes
    main_menu.add_item(blackboard, "levels_text", MAIN_MENU_SCENE_ID);
    main_menu.add_item(blackboard, "config_text",  MAIN_MENU_SCENE_ID);
    scene_manager.add_scene(MAIN_MENU_SCENE_ID, (Scene*)(&main_menu));

    TestScene test_scene(blackboard, scene_manager);
    scene_manager.add_scene(PLAY_SCENE_ID, (Scene*)(&test_scene));

    // set the first scene
    scene_manager.change_scene(MAIN_MENU_SCENE_ID);

    bool quit = false;
    while (!quit) {
        //update blackboard
        blackboard.delta_time = window.delta_time();
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
