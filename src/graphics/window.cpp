//
// Created by alex on 20/01/19.
//

#include <GL/glew.h>

#include "window.h"

bool Window::initialize(const char* title, uint32_t width, uint32_t height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Could not initialize video!
        printf("SDL could not initialize video subsystems! ERROR: %s\n", SDL_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    sdl_window_ = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );

    gl_context_ = SDL_GL_CreateContext(sdl_window_);

    glViewport(0, 0, width, height);
    width_ = width;
    height_ = height;

    SDL_GL_SetSwapInterval(-1); // -1 for Vsync

    last_time_ = SDL_GetPerformanceCounter();
    recent_time_ = SDL_GetPerformanceCounter();

    if (glewInit()) {
        printf("Failed to initialize OpenGL!\n");
        return false;
    }

    return true;
}

void Window::destroy() {
    SDL_DestroyWindow(sdl_window_);
}

void Window::clear() {
    glClearColor(1, 1, 1, 1); // same colour as the top of the background
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::display() {
    SDL_GL_SwapWindow(sdl_window_);

    last_time_ = recent_time_;
    recent_time_ = SDL_GetPerformanceCounter();
    delta_time_ = ((recent_time_ - last_time_) / (float)SDL_GetPerformanceFrequency());
}

float Window::delta_time() {
    return delta_time_;
}

void Window::draw(Renderable* renderable, const mat3& projection) {
    // no need to do any setup
    renderable->draw(projection);
}

vec2 Window::size() {
    return {(float) width_, (float) height_};
}
