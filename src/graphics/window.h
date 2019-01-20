//
// Created by alex on 20/01/19.
//

#pragma once

#include "SDL.h"

// Wrap SDL calls with a window creation/management class
class Window {
private:
    SDL_Window* sdl_window_;
    SDL_GLContext gl_context_;

public:
    Window(): sdl_window_(NULL), gl_context_() {}

    bool initialize(char* title, uint32_t width, uint32_t height);

    void destroy();


};