//
// Created by alex on 20/01/19.
//

#pragma once

#include "SDL.h"

#include "render.h"
#include "sprite.h"

// Wrap SDL calls with a window creation/management class
class Window : public RenderTarget {
private:
    SDL_Window* sdl_window_;
    SDL_GLContext gl_context_;
    uint64_t last_time_, recent_time_;
    float delta_time_ = 0;

public:
    Window(): sdl_window_(nullptr), gl_context_() {}

    // Initialize the window
    // returns false if some part of initialization fails
    // otherwise returns true
    bool initialize(char* title, uint32_t width, uint32_t height);

    // destroy the window when finished
    void destroy();

    // clears the window
    void clear();

    // swaps the buffers and displays what's been drawn
    void display();

    // returns the time elapsed between the last 2 display() calls, in seconds
    float delta_time();


    void draw(Renderable* renderable, const mat3& projection) override;

};