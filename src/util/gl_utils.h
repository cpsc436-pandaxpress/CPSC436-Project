//
// Created by alex on 24/01/19.
//

#pragma once

#include <GL/glew.h>

#include "../graphics/gl_include.h"

#include <stdio.h>
#include <vector>

// OpenGL error utility classes/functions from salmon game code

struct vec2 { float x, y; };
struct vec3 { float x, y, z; };
struct mat3 { vec3 c0, c1, c2; };

struct TexturedVertex
{
    vec3 position;
    vec2 texcoord;
};

struct Vertex
{
    vec3 position;
    vec3 color;
};


void gl_flush_errors();

bool gl_has_errors();
bool gl_has_errors(char* tag);

bool gl_compile_shader(GLuint shader);

float dot(vec2 l, vec2 r);

float dot(vec3 l, vec3 r);

mat3 mul(const mat3& l, const mat3& r);

mat3& mul_in_place(mat3& l, const mat3& r);

vec2 normalize(vec2 v);

mat3 make_translate_mat3(float x, float y);
mat3 make_scale_mat3(float x_scale, float y_scale);
mat3 make_rotate_mat3(float theta);