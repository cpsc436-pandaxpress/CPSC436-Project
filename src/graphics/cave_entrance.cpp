//
// Created by Becca Roth on 2019-04-01.
//

#include "cave_entrance.h"
#include "util/constants.h"

Vertex CaveEntrance::vertices[] = {
        Vertex{
                {-3.0f,10.0f,0.0f},
                {0,0,0}
        },
        Vertex{
                {-3.0f,8.0f,0.0f},
                {0,0,0}
        },
        Vertex{
                {-5.0f,10.0f,0.0f},
                {0,0,0}
        },
        Vertex{
                {-5.0f,8.0f,0.0f},
                {0,0,0}
        }
};

uint16_t CaveEntrance::indices[] = {
        0,1,2,
        0,2,3,
        1,2,3
};

CaveEntrance::CaveEntrance(Mesh mesh, Shader shader, vec2 size, vec2 scale) :
        shader_(shader),
        mesh_(mesh),
        size_(size),
        scale_(scale) {
    position_ = {0.f, 0.f};
    rotation_ = 0.f;
    status_ = 0;
}

CaveEntrance::CaveEntrance(const CaveEntrance &other) :
        shader_(other.shader_),
        mesh_(other.mesh_),
        position_(other.position_),
        scale_(other.scale_),
        rotation_(other.rotation_),
        status_(other.status_)
{}

void CaveEntrance::draw(const mat3 &projection) {
    // transform
    mat3 transform = {
            {1.f, 0.f, 0.f},
            {0.f, 1.f, 0.f},
            {0.f, 0.f, 1.f}
    };

    mul_in_place(transform, make_translate_mat3(position_.x, position_.y));
    mul_in_place(transform, make_rotate_mat3(rotation_));
    mul_in_place(transform, make_scale_mat3(scale_.x, scale_.y));

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
            sizeof(Vertex), // No values between vertices
            0  // offset = 0
    );
    shader_.set_input_vec3(
            "in_color",
            sizeof(Vertex), // No values between vertices
            0  // offset = sizeOf(vec3)
    );

    shader_.set_uniform_mat3("transform", transform);
    shader_.set_uniform_mat3("projection", projection);


    // draw!
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_SHORT, nullptr);

    // unbind buffer
    mesh_.unbind();

    // unbind shader
    shader_.unbind();
}

vec2 CaveEntrance::pos() {
    return {position_.x, position_.y};
}

void CaveEntrance::set_pos(const vec2 &pos) {
    position_ = {pos.x, pos.y};
}

void CaveEntrance::set_pos(float x, float y) {
    position_ = {x, y};
}

vec2 CaveEntrance::scale() {
    return {scale_.x, scale_.y};
}

void CaveEntrance::set_scale(const vec2 &scale) {
    scale_ = {scale.x, scale.y};
}

void CaveEntrance::set_scale(float x_scale, float y_scale) {
    scale_ = {x_scale, y_scale};
}

vec2 CaveEntrance::size() {
    return size_;
}

void CaveEntrance::set_size(int x_size, int y_size) {
    size_ = {(float) x_size, (float) y_size};
}

float CaveEntrance::rotation_rad() {
    return rotation_;
}

void CaveEntrance::set_rotation_rad(float theta) {
    rotation_ = theta;
}

vec3 CaveEntrance::color_start() {
    return color_start_;
}

void CaveEntrance::set_color_start(const vec3 &color) {
    color_start_ = {color.x, color.y, color.z};
}

void CaveEntrance::set_color_start(float r, float g, float b) {
    color_start_ = {r, g, b};
}

vec3 CaveEntrance::color_end() {
    return color_end_;
}

void CaveEntrance::set_color_end(const vec3 &color) {
    color_end_ = {color.x, color.y, color.z};
}

void CaveEntrance::set_color_end(float r, float g, float b) {
    color_end_ = {r, g, b};
}

void CaveEntrance::set_status(int flag) {
    status_ = flag;
}

int CaveEntrance::status() {
    return status_;
}