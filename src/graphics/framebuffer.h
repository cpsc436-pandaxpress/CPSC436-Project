//
// Created by alex on 24/01/19.
//

#pragma once

#include <cstdint>
#include "texture.h"


// Owning wrapper of an OpenGL framebuffer
class Framebuffer {
private:
    GLuint buffer_, texture_;
    uint32_t _width, _height;

public:
    Framebuffer(uint32_t width, uint32_t height);
    ~Framebuffer();

    Texture get_texture();

    void bind();
    void unbind();

    uint32_t width() { return _width; }
    uint32_t height() { return _height; }

    void resize(uint32_t width, uint32_t height);
};
