//
// Created by alex on 24/01/19.
//

#pragma once

#include <GL/gl.h>
// Non-owning wrapper of an OpenGL texture
//TODO: define
//TODO: implement
class Texture {
    friend class TextureManager;

public:
    const uint32_t width, height;
private:
    const GLuint id_;

public:
    Texture(int width, int height, GLuint id);
    Texture(const Texture& other);

    // bind the texture for rendering
    void bind();

    // unbind the currently bound texture
    static void unbind();
};
