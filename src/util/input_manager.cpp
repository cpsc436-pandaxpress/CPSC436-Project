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

    // update states that were "JUST_XYZ" last frame
    for (auto& entry : key_states_) {
        switch (entry.second) {
            case JUST_PRESSED:
                entry.second = PRESSED;
            case JUST_RELEASED:
                entry.second = RELEASED;
        }
    }

    while (SDL_PollEvent(&event) != 0) {
        switch(event.type) {
            case SDL_QUIT:
                should_exit_ = true;
                break;
            case SDL_KEYDOWN: // back-to-back cases like this
            case SDL_KEYUP:   // give both cases the same behavior
                set_key_status_from_event(event);
                break;
        }
    }
}

bool InputManager::should_exit() {
    return should_exit_;
}

bool InputManager::track(SDL_Keycode key) {
    if (key_states_.count(key) > 0) {
        return false;
    }
    else {
        key_states_.insert(std::pair<SDL_Keycode, KeyStatus>(key, RELEASED));
        return true;
    }
}

KeyStatus InputManager::get_status(SDL_Keycode key) {
    if (key_states_.count(key) > 0) {
        return key_states_.at(key);
    }
    else {
        return UNTRACKED;
    }
}

void InputManager::set_key_status_from_event(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        auto key = event.key.keysym.sym;
        if (key_states_.count(key) > 0) {
            key_states_[key] = JUST_PRESSED;
        }
    }
    if (event.type == SDL_KEYUP) {
        auto key = event.key.keysym.sym;
        if (key_states_.count(key) > 0) {
            key_states_[key] = JUST_RELEASED;
        }
    }
}
