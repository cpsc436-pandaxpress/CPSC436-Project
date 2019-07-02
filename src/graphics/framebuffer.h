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
    uint32_t width_, height_;

public:
    Framebuffer(uint32_t width, uint32_t height);
    ~Framebuffer();

    void test();

    Texture get_texture();

    void bind();
    void unbind();

    uint32_t width() { return width_; }
    uint32_t height() { return height_; }

    void resize(uint32_t width, uint32_t height);
};
