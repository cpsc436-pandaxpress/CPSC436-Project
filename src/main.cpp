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
#include "scene/test_scene.h"
#include "util/blackboard.h"

#include <SDL_mixer.h>
#include <sstream>


static const SceneID TEST_SCENE_ID = 0;

int main(int argc, char** argv) {

    auto window = Window();

    window.initialize("Express Panda", 800, 600);

    Blackboard blackboard = {
        Camera(1600, 1200, 0, 0),
        0,
        InputManager(),
        ShaderManager(),
        TextureManager(),
        window
    };

    auto scene_manager = SceneManager();

    //load assets and configure

    blackboard.input_manager.track(SDL_SCANCODE_UP);
    blackboard.input_manager.track(SDL_SCANCODE_DOWN);
    blackboard.input_manager.track(SDL_SCANCODE_LEFT);
    blackboard.input_manager.track(SDL_SCANCODE_RIGHT);
    blackboard.input_manager.track(SDL_SCANCODE_SPACE);

    blackboard.shader_manager.load_shader(
            shaders_path("sprite.vs.glsl"),
            shaders_path("sprite.fs.glsl"),
            "sprite"
    );

    blackboard.textureManager.load_texture(textures_path("panda.png"), "panda");
    blackboard.textureManager.load_texture(textures_path("grass_block_1.png"), "platform1");
    blackboard.textureManager.load_texture(textures_path("grass_block_2.png"), "platform2");
    blackboard.textureManager.load_texture(textures_path("platform_center_grass.png"), "platform_center_grass");
    blackboard.textureManager.load_texture(textures_path("bread.png"), "bread");


    // initialize scenes here

    TestScene test_scene(blackboard, scene_manager);

    scene_manager.add_scene(TEST_SCENE_ID, (Scene*)(&test_scene));

    // set the first scene
    scene_manager.change_scene(TEST_SCENE_ID);

    //set background music
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "Failed to initialize SDL Audio");

    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        fprintf(stderr, "Failed to open audio device");

    }
    Mix_Music* m_background_music;
    m_background_music = Mix_LoadMUS(audio_path("PE2.ogg"));


    Mix_PlayMusic(m_background_music, -1);

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
