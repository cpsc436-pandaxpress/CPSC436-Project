//
// Created by alex on 20/01/19.
//

#include <entt/entity/registry.hpp>
#include <GL/glew.h>
#include <SDL.h>
#include <stdio.h>

#include "graphics/window.h"
#include "scene/scene_manager.h"
#include "util/input_manager.h"

int main(int argc, char** argv) {

    auto window = Window();

    window.initialize("Express Panda", 800, 600);

    auto input_manager = InputManager();
    auto scene_manager = SceneManager();

    bool quit = false;
    while (!quit) {
        input_manager.update();

        quit = input_manager.should_exit();
    }

    window.destroy();
    return 0;
}