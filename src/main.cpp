//
// Created by alex on 20/01/19.
//

#include <entt/entity/registry.hpp>
#include <GL/glew.h>
#include <SDL.h>
#include <stdio.h>

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

    auto scene_manager = SceneManager();

    initialize_scenes(scene_manager, blackboard);

    bool quit = false;
    while (!quit) {
        blackboard.input_manager.update();
        scene_manager.update(window.delta_time(), blackboard);

        window.clear();
        scene_manager.render(blackboard);
        window.display();

        quit = blackboard.input_manager.should_exit();
    }

    window.destroy();
    return 0;
}
