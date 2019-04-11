//
// Created by alex on 24/01/19.
//

//
// Created by alex on 24/01/19.
//

#include "gl_utils.h"

#include <cmath>


// OpenGL error utility functions from salmon game code

void gl_flush_errors()
{
    while (glGetError() != GL_NO_ERROR);
}

bool gl_has_errors() {
    return gl_has_errors("untagged");
}

bool gl_has_errors(const char* tag)
{
    GLenum error = glGetError();

    if (error == GL_NO_ERROR) return false;

    while (error != GL_NO_ERROR)
    {
        const char* error_str = "";
        switch (error)
        {
            case GL_INVALID_OPERATION:
                error_str = "INVALID_OPERATION";
                break;
            case GL_INVALID_ENUM:
                error_str = "INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error_str = "INVALID_VALUE";
                break;
            case GL_OUT_OF_MEMORY:
                error_str = "OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error_str = "INVALID_FRAMEBUFFER_OPERATION";
                break;
        }

        fprintf(stderr, "[%s] OpenGL: %s\n", tag, error_str);
        error = glGetError();
    }

    return true;
}

bool gl_compile_shader(GLuint shader)
{
    glCompileShader(shader);
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint log_len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
        std::vector<char> log(log_len);
        glGetShaderInfoLog(shader, log_len, &log_len, log.data());
        glDeleteShader(shader);

        fprintf(stderr, "GLSL: %s", log.data());
        return false;
    }

    return true;
}

float dot(vec2 l, vec2 r)
{
    return l.x * r.x + l.y * r.y;
}

float dot(vec3 l, vec3 r)
{
    return l.x * r.x + l.y * r.y + l.z * r.z;
}

mat3 mul(const mat3 & l, const mat3 & r)
{
    mat3 l_t = { { l.c0.x, l.c1.x, l.c2.x},
                 { l.c0.y, l.c1.y, l.c2.y } ,
                 { l.c0.z, l.c1.z, l.c2.z } };

    mat3 ret;
    ret.c0.x = dot(l_t.c0, r.c0);
    ret.c0.y = dot(l_t.c1, r.c0);
    ret.c0.z = dot(l_t.c2, r.c0);

    ret.c1.x = dot(l_t.c0, r.c1);
    ret.c1.y = dot(l_t.c1, r.c1);
    ret.c1.z = dot(l_t.c2, r.c1);

    ret.c2.x = dot(l_t.c0, r.c2);
    ret.c2.y = dot(l_t.c1, r.c2);
    ret.c2.z = dot(l_t.c2, r.c2);
    return ret;
}


mat3& mul_in_place(mat3& l, const mat3& r) {
    mat3 l_t = { { l.c0.x, l.c1.x, l.c2.x},
                 { l.c0.y, l.c1.y, l.c2.y } ,
                 { l.c0.z, l.c1.z, l.c2.z } };

    l.c0.x = dot(l_t.c0, r.c0);
    l.c0.y = dot(l_t.c1, r.c0);
    l.c0.z = dot(l_t.c2, r.c0);

    l.c1.x = dot(l_t.c0, r.c1);
    l.c1.y = dot(l_t.c1, r.c1);
    l.c1.z = dot(l_t.c2, r.c1);

    l.c2.x = dot(l_t.c0, r.c2);
    l.c2.y = dot(l_t.c1, r.c2);
    l.c2.z = dot(l_t.c2, r.c2);

    return l;
}

vec2 normalize(vec2 v)
{
    float m = sqrtf(dot(v, v));
    return { v.x / m, v.y / m };
}

mat3 make_translate_mat3(float x, float y) {
    return{
        { 1.f, 0.f, 0.f },
        { 0.f, 1.f, 0.f },
        { x, y, 1.f }
    };
}

mat3 make_scale_mat3(float x_scale, float y_scale) {
    return {
        { x_scale, 0.f, 0.f },
        { 0.f, y_scale, 0.f },
        { 0.f, 0.f, 1.f }
    };
}

mat3 make_rotate_mat3(float theta) {
    float c = cosf(theta);
    float s = sinf(theta);
    return {
        { c, s, 0.f },
        { -s, c, 0.f },
        { 0.f, 0.f, 1.f }
    };
}
