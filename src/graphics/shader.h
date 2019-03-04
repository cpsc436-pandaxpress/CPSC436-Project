//
// Created by alex on 24/01/19.
//

#pragma once

#include <GL/glew.h>

#include "gl_include.h"

#include "../util/gl_utils.h"

// Non-owning wrapper of an OpenGL shader program
class Shader {
    friend class ShaderManager;
private:
    GLuint vert_id_, frag_id_, program_id_;

public:
    Shader(GLuint vert_id, GLuint frag_id, GLuint program_id);
    Shader(const Shader& other);

    void bind();

    void unbind();

    void set_uniform_vec2(const char* loc, const vec2& val);
    void set_uniform_vec3(const char* loc, const vec3& val);
    void set_uniform_mat3(const char* loc, const mat3& val);

    void set_input_vec2(const char* loc, size_t size, size_t position);
    void set_input_vec3(const char* loc, size_t size, size_t position);

    void set_uniform_float(const char *loc, const float val);
    void set_uniform_int(const char *loc, int val);

};