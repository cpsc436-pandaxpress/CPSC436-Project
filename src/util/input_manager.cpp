//
// Created by alex on 20/01/19.
//

#include <SDL.h>

#include "input_manager.h"


InputManager::InputManager() :
    key_states_(),
    should_exit_(false)
{}

void InputManager::update() {
    SDL_Event event;

    auto* keystate = SDL_GetKeyboardState(NULL);

    // update tracked states
    for (auto& entry : key_states_) {

        if (keystate[entry.first]) {
            if (entry.second == JUST_PRESSED || entry.second == PRESSED) {
                entry.second = PRESSED;
            }
            else {
                entry.second = JUST_PRESSED;
            }
        }
        else {
            if (entry.second == JUST_RELEASED || entry.second == RELEASED) {
                entry.second = RELEASED;
            }
            else {
                entry.second = JUST_RELEASED;
            }
        }
    }

    while (SDL_PollEvent(&event) != 0) {
        switch(event.type) {
            case SDL_QUIT:
                should_exit_ = true;
                break;
        }
    }
}

bool InputManager::should_exit() {
    return should_exit_;
}

bool InputManager::track(SDL_Scancode key) {
    if (key_states_.count(key) > 0) {
        return false;
    }
    else {
        key_states_.insert(std::pair<SDL_Scancode, KeyStatus>(key, RELEASED));
        return true;
    }
}

KeyStatus InputManager::get_status(SDL_Scancode key) {
    if (key_states_.count(key) > 0) {
        return key_states_.at(key);
    }
    else {
        return UNTRACKED;
    }
}

bool InputManager::key_just_pressed(SDL_Scancode key) {
    if (key_states_.count(key) > 0) {
        auto status = key_states_[key];
        return status == JUST_PRESSED;
    }
    else {
        return false;
    }
}

bool InputManager::key_just_released(SDL_Scancode key) {
    auto x = key_states_.count(key);
    if (key_states_.count(key) > 0) {
        auto status = key_states_[key];
        return status == JUST_RELEASED;
    }
    else {
        return false;
    }
}

bool InputManager::key_pressed(SDL_Scancode key) {
    if (key_states_.count(key) > 0) {
        auto status = key_states_[key];
        return status == PRESSED || status == JUST_PRESSED;
    }
    else {
        return false;
    }
}

bool InputManager::key_released(SDL_Scancode key) {
    if (key_states_.count(key) > 0) {
        auto status = key_states_[key];
        return status == RELEASED || status == JUST_RELEASED;
    }
    else {
        return false;
    }
}


void InputManager::set_key_status_from_event(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        auto key = event.key.keysym.scancode;
        if (key_states_.count(key) > 0) {
            key_states_[key] = JUST_PRESSED;
        }
    }
    if (event.type == SDL_KEYUP) {
        auto key = event.key.keysym.scancode;
        if (key_states_.count(key) > 0) {
            key_states_[key] = JUST_RELEASED;
        }
    }
}

