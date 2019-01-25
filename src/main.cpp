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
#include "util/blackboard.h"


void initialize_scenes(SceneManager& scene_manager, Blackboard& blackboard) {
    //TODO: initialize scenes here
}

int main(int argc, char** argv) {

    auto window = Window();

    window.initialize("Express Panda", 800, 600);

    Blackboard blackboard;
    blackboard.input_manager = InputManager();
    blackboard.shader_manager = ShaderManager();
    blackboard.textureManager = TextureManager();

    auto scene_manager = SceneManager();

    initialize_scenes(scene_manager, blackboard);


    //sprite test

    Camera camera(800.f, 600.f, 0.f, 0.f);

    blackboard.textureManager.load_texture("data/textures/panda.png", "panda");
    blackboard.shader_manager.load_shader("data/shaders/sprite.vs.glsl", "data/shaders/sprite.fs.glsl", "sprite");

    Texture texture = blackboard.textureManager.get_texture("panda");
    Shader shader = blackboard.shader_manager.get_shader("sprite");

    Sprite sprite(texture, shader);


    bool quit = false;
    while (!quit) {
        blackboard.input_manager.update();
        scene_manager.update(window.delta_time(), blackboard);

        window.clear();
        scene_manager.render(blackboard);
        window.draw((Renderable*)(&sprite), camera.get_projection());

        window.display();

        quit = blackboard.input_manager.should_exit();
    }

    window.destroy();
    return 0;
}
