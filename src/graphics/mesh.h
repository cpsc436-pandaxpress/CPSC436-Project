//
// Created by alex on 24/01/19.
//

#pragma once

#include "../util/gl_utils.h"

// an struct that owns the referenced OpenGL buffers
class Mesh
{
private:
    GLuint vao_;
    GLuint vbo_;
    GLuint ibo_;

public:
    Mesh(size_t vertex_count, TexturedVertex* vertices, size_t index_count, uint16_t* indices);
    ~Mesh();

    GLuint vao() { return vao_; }

    GLuint vbo() { return vbo_; }

    GLuint ibo() { return ibo_; }

    void bind();

    static void unbind();
};