//
// Created by alex on 24/01/19.
//

#pragma once

#include "mesh.h"
#include "render.h"
#include "shader.h"
#include "shader_manager.h"
#include "texture.h"

class Sprite : public Renderable {
private:
    Mesh mesh_;
    Shader shader_;
    Texture texture_;

    vec2 position_, pixel_scale_, scale_, uv1_, uv2_;
    vec3 color_;
    float rotation_;

public:
    static TexturedVertex vertices[4];
    static uint16_t indices[6];

public:
    Sprite(Texture texture, Shader shader, Mesh mesh);
    Sprite(const Sprite& other);

    void draw(const mat3& projection);

    vec2 pos();
    void set_pos(const vec2& pos);
    void set_pos(float x, float y);

    vec2 scale();
    void set_scale(const vec2& scale);
    void set_scale(float x_scale, float y_scale);
    void set_scale_int(float x_scale, float y_scale);
    void set_size(uint32_t width, uint32_t height);

    void set_size(int x_size, int y_size);

    float rotation_rad();
    void set_rotation_rad(float theta);

    vec3 color();
    void set_color(const vec3& color);
    void set_color(float r, float g, float b);


    vec2 uv1();
    vec2 uv2();
    void set_uvs(float u1, float v1, float u2, float v2);
    void set_uvs(const vec2& uv1, const vec2& uv2);
    void set_texture_rect(uint32_t left, uint32_t top, uint32_t width, uint32_t height);

    void set_shader(Shader shader);

};