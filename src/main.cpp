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


static const SceneID TEST_SCENE_ID = 0;

int main(int argc, char** argv) {

    auto window = Window();

    window.initialize("Express Panda", 800, 600);

    Blackboard blackboard = {
        Camera(1600.f, 1200.f, 0.f, 0.f),
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

    blackboard.textureManager.load_texture(textures_path("panda.png"), "panda");
    blackboard.shader_manager.load_shader(
        shaders_path("sprite.vs.glsl"),
        shaders_path("sprite.fs.glsl"),
        "sprite"
    );

    blackboard.textureManager.load_texture(textures_path("platform center grass.png"), "platform");

    // initialize scenes here

    TestScene test_scene(blackboard, scene_manager);

    scene_manager.add_scene(TEST_SCENE_ID, (Scene*)(&test_scene));

    // set the first scene
    scene_manager.change_scene(TEST_SCENE_ID);

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
