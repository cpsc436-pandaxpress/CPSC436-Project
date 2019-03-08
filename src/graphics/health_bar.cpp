//
// Created by Prayansh Srivastava on 2019-03-06.
//

#include "health_bar.h"

vec3 HealthBar::vertices[] = {
        vec3{-0.5f, 0.5f, 0.0f}, // Top-left
        vec3{0.5f, 0.5f, 0.0f}, // Top-right
        vec3{0.5f, -0.5f, 0.0f}, // Bottom-right
        vec3{-0.5f, -0.5f, 0.0f}, // Bottom-left
};

uint16_t HealthBar::indices[] = {
        0, 1, 2,
        2, 3, 0
};

HealthBar::HealthBar(Mesh mesh, Shader shader, vec2 size) :
        shader_(shader),
        mesh_(mesh),
        size_(size) {
    position_ = {0.f, 0.f};
    scale_ = {1.f, 1.f};
    color_start_ = {1.f, 1.f, 1.f};
    color_end_ = {1.f, 1.f, 1.f};
    rotation_ = 0.f;
    health_ = 1.0f;
}

HealthBar::HealthBar(const HealthBar &other) :
        shader_(other.shader_),
        mesh_(other.mesh_),
        position_(other.position_),
        scale_(other.scale_),
        color_start_(other.color_start_),
        color_end_(other.color_end_),
        rotation_(other.rotation_) {}

void HealthBar::draw(const mat3 &projection) {
    // transform
    mat3 transform = {
            {1.f, 0.f, 0.f},
            {0.f, 1.f, 0.f},
            {0.f, 0.f, 1.f}
    };

    mul_in_place(transform, make_translate_mat3(position_.x, position_.y));
    mul_in_place(transform, make_rotate_mat3(rotation_));
    mul_in_place(transform, make_scale_mat3(size_.x, size_.y));
    mul_in_place(transform, make_scale_mat3(scale_.x, scale_.y));
    vec2 scale = {scale_.x * size_.x, scale_.y * size_.y};

    // bind shader
    shader_.bind();

    // setup blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    // bind buffer
    mesh_.bind();

    // setup attributes
    shader_.set_input_vec3(
            "in_position",
            0, // No values between vertices
            0  // offset = 0
    );

    //setup uniforms
    shader_.set_uniform_mat3("transform", transform);
    shader_.set_uniform_mat3("projection", projection);
    shader_.set_uniform_vec3("start_color", color_start_);
    shader_.set_uniform_vec3("end_color", color_end_);
    shader_.set_uniform_vec2("scale", scale);
    shader_.set_uniform_float("health", health_);

    // draw! TODO
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);

    // unbind buffer
    mesh_.unbind();

    // unbind shader
    shader_.unbind();
}

vec2 HealthBar::pos() {
    return {position_.x, position_.y};
}

void HealthBar::set_pos(const vec2 &pos) {
    position_ = {pos.x, pos.y};
}

void HealthBar::set_pos(float x, float y) {
    position_ = {x, y};
}

vec2 HealthBar::scale() {
    return {scale_.x, scale_.y};
}

void HealthBar::set_scale(const vec2 &scale) {
    scale_ = {scale.x, scale.y};
}

void HealthBar::set_scale(float x_scale, float y_scale) {
    scale_ = {x_scale, y_scale};
}

vec2 HealthBar::size() {
    return size_;
}

void HealthBar::set_size(int x_size, int y_size) {
    size_ = {(float) x_size, (float) y_size};
}

float HealthBar::rotation_rad() {
    return rotation_;
}

void HealthBar::set_rotation_rad(float theta) {
    rotation_ = theta;
}

float HealthBar::health() {
    return health_;
}

void HealthBar::set_health(float health_percentage) {
    health_ = health_percentage;
}

vec3 HealthBar::color_start() {
    return color_start_;
}

void HealthBar::set_color_start(const vec3 &color) {
    color_start_ = {color.x, color.y, color.z};
}

void HealthBar::set_color_start(float r, float g, float b) {
    color_start_ = {r, g, b};
}

vec3 HealthBar::color_end() {
    return color_end_;
}

void HealthBar::set_color_end(const vec3 &color) {
    color_end_ = {color.x, color.y, color.z};
}

void HealthBar::set_color_end(float r, float g, float b) {
    color_end_ = {r, g, b};
}
