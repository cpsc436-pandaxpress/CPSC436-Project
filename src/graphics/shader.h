//
// Created by alex on 24/01/19.
//

#pragma once

#include <GL/glew.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "../util/gl_utils.h"

// Non-owning wrapper of an OpenGL shader program
//TODO: define
//TODO: implement
class Shader {
    friend class ShaderManager;
private:
    GLuint vert_id_, frag_id_, program_id_;

public:
    Shader(GLuint vert_id, GLuint frag_id, GLuint program_id);
    Shader(const Shader& other);

    void bind();

    static void unbind();

    void set_uniform_vec2(const char* loc, const vec2& val);
    void set_uniform_vec3(const char* loc, const vec3& val);
    void set_uniform_mat3(const char* loc, const mat3& val);

    void set_input_vec2(const char* loc, size_t size, size_t position);
    void set_input_vec3(const char* loc, size_t size, size_t position);

};