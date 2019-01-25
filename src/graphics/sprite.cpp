//
// Created by alex on 24/01/19.
//

#include "sprite.h"
#include "../util/gl_utils.h"


TexturedVertex Sprite::vertices[4] = {
    TexturedVertex {
        { -1, 1, -0.01f },
        { 0.f, 1.f }
    },
    TexturedVertex {
        { 1, 1, -0.01f },
        { 1.f, 1.f }
    },
    TexturedVertex {
        { 1, -1, -0.01f },
        { 1.f, 0.f }
    },
    TexturedVertex {
        { -1, -1, -0.01f },
        { 0.f, 0.f }
    }
};

uint16_t Sprite::indices[6] = { 0, 3, 1, 1, 3, 2 };

Sprite::Sprite(Texture texture, Shader shader) :
    mesh_(4, vertices, 6, indices),
    shader_(shader),
    texture_(texture)
{
    position_ = { 0, 9};

}

void Sprite::draw(const mat3& projection) {
    // transform
    mat3 transform = {
        { 1.f, 0.f, 0.f },
        { 0.f, 1.f, 0.f },
        { 0.f, 0.f, 1.f }
    };

    mul_in_place(transform, make_translate_mat3(position_.x, position_.y));
    mul_in_place(transform, make_rotate_mat3(rotation_));
    mul_in_place(transform, make_scale_mat3(scale_.x * pixel_scale_.x, scale_.y * pixel_scale_.y));

    // bind shader
    shader_.bind();

    // setup blending
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    // bind buffers
    mesh_.bind();

    // setup attributes
    shader_.set_input_vec3("in_position", sizeof(TexturedVertex), 0);
    shader_.set_input_vec3("in_texcoord", sizeof(TexturedVertex), sizeof(vec3));

    //setup uniforms
    shader_.set_uniform_mat3("transform", transform);
    shader_.set_uniform_vec3("fcolor", color_);
    shader_.set_uniform_mat3("projection", projection);

    // bind texture
    texture_.bind();

    // draw!
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);

    // unbind texture
    texture_.unbind();

    // unbind buffers
    mesh_.unbind();

    // unbind shader
    shader_.unbind();

}

vec2 Sprite::pos() {
    return { position_.x, position_.y };
}

void Sprite::set_pos(const vec2& pos) {
    position_ = { pos.x, pos.y };
}

void Sprite::set_pos(float x, float y) {
    position_ = { x, y };
}

vec2 Sprite::scale() {
    return { scale_.x, scale_.y };
}

void Sprite::set_scale(const vec2& scale) {
    scale_ = { scale.x, scale.y };
}

void Sprite::set_scale(float x_scale, float y_scale) {
    scale_ = { x_scale, y_scale };
}

float Sprite::rotation_rad() {
    return rotation_;
}

void Sprite::set_rotation_rad(float theta) {
    rotation_ = theta;
}

vec3 Sprite::color() {

}

void Sprite::set_color(const vec3& color) {
    color_ = { color_.x, color_.y, color_.z };
}

void Sprite::set_color(float r, float g, float b) {
    color_ = { r, g, b };
}