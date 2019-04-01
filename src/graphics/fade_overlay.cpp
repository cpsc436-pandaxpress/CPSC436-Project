//
// Created by Avery Brown on 2019-03-29.
//

#include "fade_overlay.h"
#include "util/constants.h"
#include "../util/blackboard.h"

FadeOverlay::FadeOverlay(Mesh mesh, Shader shader, vec2 size) :
        shader_(shader),
        mesh_(mesh),
        size_(size) {
        position_ = {0.f, 0.f};
        scale_ = {1.f, 1.f};
        alpha_ = 0.f;
}


FadeOverlay::FadeOverlay(const FadeOverlay &other) :
        shader_(other.shader_),
        mesh_(other.mesh_),
        position_(other.position_),
        scale_(other.scale_),
        alpha_(other.alpha_)
{}

void FadeOverlay::draw(const mat3 &projection) {

    // transform
    mat3 transform = {
            {1.f, 0.f, 0.f},
            {0.f, 1.f, 0.f},
            {0.f, 0.f, 1.f}
    };

    mul_in_place(transform, make_translate_mat3(position_.x, position_.y));
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
    shader_.set_uniform_vec2("scale", scale);
    shader_.set_uniform_float("alpha", alpha_);

    // draw!
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);

    // unbind buffer
    mesh_.unbind();

    // unbind shader
    shader_.unbind();
}

vec2 FadeOverlay::pos() {
    return {position_.x, position_.y};
}

void FadeOverlay::set_pos(const vec2 &pos) {
    position_ = {pos.x, pos.y};
}

void FadeOverlay::set_pos(float x, float y) {
    position_ = {x, y};
}

vec2 FadeOverlay::scale() {
    return {scale_.x, scale_.y};
}

void FadeOverlay::set_scale(const vec2 &scale) {
    scale_ = {scale.x, scale.y};
}

void FadeOverlay::set_scale(float x_scale, float y_scale) {
    scale_ = {x_scale, y_scale};
}

vec2 FadeOverlay::size() {
    return size_;
}

void FadeOverlay::set_size(int x_size, int y_size) {
    size_ = {(float) x_size, (float) y_size};
}

void FadeOverlay::set_alpha(float alpha) {
    alpha_ = alpha;
}

float FadeOverlay::alpha() {
    return alpha_;
}