//
// Created by alex on 24/01/19.
//

#include "sprite.h"
#include "../util/gl_utils.h"


TexturedVertex Sprite::vertices[4] = {
        TexturedVertex {
                { -0.5f, 0.5f, -0.01f },
                { 0.f, 1.f }
        },
        TexturedVertex {
                { 0.5f, 0.5f, -0.01f },
                { 1.f, 1.f }
        },
        TexturedVertex {
                { 0.5f, -0.5f, -0.01f },
                { 1.f, 0.f }
        },
        TexturedVertex {
                { -0.5f, -0.5f, -0.01f },
                { 0.f, 0.f }
        }
};

uint16_t Sprite::indices[6] = { 0, 3, 1, 1, 3, 2 };

Sprite::Sprite(Texture texture, Shader shader, Mesh mesh) :
        mesh_(mesh),
        shader_(shader),
        texture_(texture)
{
    position_ = { 0.f, 0.f};
    pixel_scale_ = {(float)texture.width(), (float)texture.height()};
    scale_ = {1.f, 1.f};
    uv1_ = {0, 0};
    uv2_ = {1, 1};
    color_ = {1.f, 1.f, 1.f};
    rotation_ = 0.f;
}

Sprite::Sprite(const Sprite& other) :
        mesh_(other.mesh_),
        shader_(other.shader_),
        texture_(other.texture_),
        position_(other.position_),
        pixel_scale_(other.pixel_scale_),
        scale_(other.scale_),
        color_(other.color_),
        uv1_(other.uv1_),
        uv2_(other.uv2_),
        rotation_(other.rotation_)
{}


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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

    shader_.set_uniform_vec2("uv1", uv1_);
    shader_.set_uniform_vec2("uv2", uv2_);

    // bind texture
    glActiveTexture(GL_TEXTURE0);
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

void Sprite::set_scale_int(float x_scale, float y_scale) {
    int pix_x = (int)pixel_scale_.x;
    int pix_y = (int)pixel_scale_.y;

    float true_x_scale = (pixel_scale_.x * x_scale) / pix_x;
    float true_y_scale = (pixel_scale_.x * y_scale) / pix_x;

    scale_ = { true_x_scale, true_y_scale };
}

void Sprite::set_scale(float x_scale, float y_scale) {
    scale_ = { x_scale, y_scale };
}

void Sprite::set_size(uint32_t width, uint32_t height) {
    set_scale(
        (float)width / pixel_scale_.x,
        (float)height / pixel_scale_.y
    );
}

void Sprite::set_size(int x_size, int y_size) {
    set_scale(
        (float)x_size / pixel_scale_.x,
        (float)y_size / pixel_scale_.y
    );
}

float Sprite::rotation_rad() {
    return rotation_;
}

void Sprite::set_rotation_rad(float theta) {
    rotation_ = theta;
}

vec3 Sprite::color() {
    return color_;
}

void Sprite::set_color(const vec3& color) {
    color_ = { color_.x, color_.y, color_.z };
}

void Sprite::set_color(float r, float g, float b) {
    color_ = { r, g, b };
}

vec2 Sprite::uv1() {
    return uv1_;
}

vec2 Sprite::uv2() {
    return uv2_;
}

void Sprite::set_uvs(float u1, float v1, float u2, float v2) {
    uv1_ = {u1, v1};
    uv2_ = {u2, v2};
}

void Sprite::set_uvs(const vec2& uv1, const vec2& uv2) {
    uv1_ = uv1;
    uv2_ = uv2;
}

void Sprite::set_texture_rect(uint32_t left, uint32_t top, uint32_t width, uint32_t height) {
    float u1 = (float)left / texture_.width();
    float v1 = (float)top / texture_.height();
    float u2 = (float)(left + width) / texture_.width();
    float v2 = (float)(top + height) / texture_.height();
    set_uvs(u1, v1, u2, v2);
}

void Sprite::set_shader(Shader shader) {
    shader_ = shader;
}
