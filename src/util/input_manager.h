//
// Created by alex on 20/01/19.
//

#pragma once

#include <SDL.h>
#include <unordered_map>


enum KeyStatus {
    JUST_PRESSED,
    JUST_RELEASED,
    PRESSED,
    RELEASED,
    UNTRACKED
};

class InputManager {
private:
    std::unordered_map<SDL_Keycode, KeyStatus> key_states_;
    bool should_exit_;

public:
    InputManager();

    // update
    void update();

    // returns true if an exit event has been polled
    bool should_exit();

    // returns true if key successfully added to track list, false otherwise
    bool track(SDL_Keycode key);

    // returns the status of the given key,
    // JUST_PRESSED/JUST_RELEASED if this is the first frame since press/release
    // PRESSED/RELEASED if this is not the first frame since press/release
    // UNTRACKED if the key hasn't been registered with track()
    KeyStatus get_status(SDL_Keycode key);

private:

    void set_key_status_from_event(SDL_Event& event);

};