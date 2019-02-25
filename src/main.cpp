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
#include "util/blackboard.h"
#include "util/random.h"

#include <SDL_mixer.h>
#include <sstream>
#include <scene/vertical_scene.h>
#include <util/csv_reader.h>
#include <iostream>
#include <scene/horizontal_scene.h>


static const SceneID HORIZONTAL_SCENE_ID = 0;
static const SceneID VERTICAL_SCENE_ID = 1;

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
        Random(0)
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

    blackboard.texture_manager.load_texture(textures_path("panda.png"), "panda");
    blackboard.texture_manager.load_texture(textures_path("grass_block_1.png"), "platform1");
    blackboard.texture_manager.load_texture(textures_path("platform_center_grass.png"), "platform_center_grass");
    blackboard.texture_manager.load_texture(textures_path("grass_block_2.png"), "platform2");
    blackboard.texture_manager.load_texture(textures_path("bread.png"), "bread");
    blackboard.texture_manager.load_texture(textures_path("ghost.png"), "ghost");
    blackboard.texture_manager.load_texture(textures_path("llama.png"), "llama");
    blackboard.texture_manager.load_texture(textures_path("spit.png"), "spit");
    blackboard.texture_manager.load_texture(textures_path("branchspiky.png"), "branch1");
    blackboard.texture_manager.load_texture(textures_path("branchspiky2.png"), "branch2");
    blackboard.texture_manager.load_texture(textures_path("bg_back.png"), "bg_back");
    blackboard.texture_manager.load_texture(textures_path("bg_front.png"), "bg_front");
    blackboard.texture_manager.load_texture(textures_path("bg_middle.png"), "bg_middle");
    blackboard.texture_manager.load_texture(textures_path("bg_top.png"), "bg_top");
    blackboard.texture_manager.load_texture(textures_path("tutorial.png"), "tutorial");
    blackboard.texture_manager.load_texture(textures_path("tutorial2.png"), "tutorial_bread");
    blackboard.texture_manager.load_texture(textures_path("stalagmite.png"), "stalagmite");
    blackboard.texture_manager.load_texture(textures_path("stalagmite2.png"), "stalagmite2");

    blackboard.mesh_manager.load_mesh("sprite", 4, Sprite::vertices, 6, Sprite::indices);




    // initialize scenes here
    HorizontalScene horizontal_scene(blackboard, scene_manager);
    VerticalScene vertical_scene(blackboard, scene_manager);

    scene_manager.add_scene(HORIZONTAL_SCENE_ID, (Scene*)(&horizontal_scene));
    scene_manager.add_scene(VERTICAL_SCENE_ID, (Scene*)(&vertical_scene));

    // set the first scene
    scene_manager.change_scene(HORIZONTAL_SCENE_ID);

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
