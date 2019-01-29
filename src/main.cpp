//
// Created by alex on 20/01/19.
//

#include <entt/entity/registry.hpp>
#include <GL/glew.h>
#include <SDL.h>
#include <stdio.h>

#include "graphics/camera.h"
#include "graphics/sprite.h"
#include "graphics/window.h"
#include "scene/scene_manager.h"
#include "scene/test_scene.h"
#include "util/blackboard.h"


static const SceneID TEST_SCENE_ID = 0;

void initialize_scenes(SceneManager& scene_manager, Blackboard& blackboard) {
    //TODO: initialize scenes here
    scene_manager.add_scene(TEST_SCENE_ID, new TestScene(blackboard, scene_manager));
    scene_manager.change_scene(TEST_SCENE_ID);
}

int main(int argc, char** argv) {

    auto window = Window();

    window.initialize("Express Panda", 800, 600);

    Blackboard blackboard {
        camera: Camera (800.f, 600.f, 0.f, 0.f),
        window: window
    };
    blackboard.delta_time = 0;
    blackboard.input_manager = InputManager();
    blackboard.shader_manager = ShaderManager();
    blackboard.textureManager = TextureManager();

    auto scene_manager = SceneManager();

    //load assets

    blackboard.textureManager.load_texture("data/textures/panda.png", "panda");
    blackboard.shader_manager.load_shader(
        "data/shaders/sprite.vs.glsl",
        "data/shaders/sprite.fs.glsl",
        "sprite"
    );

    initialize_scenes(scene_manager, blackboard);

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
