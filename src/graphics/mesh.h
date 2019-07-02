//
// Created by alex on 24/01/19.
//

#pragma once

#include "../util/gl_utils.h"

// a struct with non-owning references to the relevant buffers/array
class Mesh {
private:
    GLuint vao_;
    GLuint vbo_;
    GLuint ibo_;

public:
    Mesh(GLuint vao, GLuint vbo, GLuint ibo);

    Mesh(const Mesh &other);

    GLuint vao() { return vao_; }

    GLuint vbo() { return vbo_; }

    GLuint ibo() { return ibo_; }

    void bind();

    void unbind();
};