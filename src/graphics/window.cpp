//
// Created by alex on 20/01/19.
//

#include <GL/glew.h>

#include "window.h"

bool Window::initialize(char* title, uint32_t width, uint32_t height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Could not initialize video!
        printf("SDL could not initialize video subsystems! ERROR: %s\n", SDL_GetError());
        return false;
    }

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

    if (glewInit()) {
        printf("Failed to initialize OpenGL!\n");
        return false;
    }

    return true;
}

void Window::destroy() {
    SDL_DestroyWindow(sdl_window_);
}