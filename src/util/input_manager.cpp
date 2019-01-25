//
// Created by alex on 20/01/19.
//

#include <SDL.h>

#include "input_manager.h"


InputManager::InputManager() :
    should_exit_(false)
{}

void InputManager::update() {
    //TODO: implement more
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            should_exit_ = true;
        }
    }
}

bool InputManager::should_exit() {
    return should_exit_;
}
