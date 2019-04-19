//
// Created by alex on 20/01/19.
//

#pragma once

#include "SDL.h"

#include "render.h"
#include "sprite.h"
#include "framebuffer.h"
#include <memory>

// Wrap SDL calls with a window creation/management class
class Window : public RenderTarget {
private:
    SDL_Window* sdl_window_;
    SDL_GLContext gl_context_;
    uint64_t last_time_, recent_time_;
    int width_, height_;
    float delta_time_ = 0;
    int WINDOWED_WIDTH = 800;
    int WINDOWED_HEIGHT = 450;
    std::unique_ptr<Framebuffer> framebuffer_;

public:
    Window(const char* title);

    ~Window();

    bool initialize(const char* title);

    // destroy the window when finished
    void destroy();

    // clears the window
    void clear();

    // renders the internal buffer to the back buffer using the given shader
    // then swaps the back buffers and displays what's been drawn
    void display(Shader shader, Mesh mesh);

    // returns the time elapsed between the last 2 display() calls, in seconds
    float delta_time();

    // returns the size of the window
    vec2 size();

    void draw(Renderable* renderable, const mat3& projection) override;

    void colorScreen(vec3 color);

};