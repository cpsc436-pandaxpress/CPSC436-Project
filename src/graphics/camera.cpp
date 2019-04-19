//
// Created by alex on 25/01/19.
//

#include "camera.h"

Camera::Camera(float width, float height, float center_x, float center_y) {
    dimensions_ = {width, height};
    position_ = {center_x, center_y};
    in_transition = false;
    transition_ready = false;
    compose();
}

void Camera::set_size(float width, float height) {
    dimensions_ = {width, height};
}

vec2 Camera::size() const {
    return dimensions_;
}

void Camera::set_position(float x, float y) {
    position_ = {x, y};
}

vec2 Camera::position() const {
    return position_;
}

void Camera::compose() {
    float h_width = dimensions_.x * 0.5f;
    float h_height = dimensions_.y * 0.5f;

    float left = (int)(position_.x - h_width);
    float top = (int)(position_.y - h_height);
    float right = (int)(position_.x + h_width);
    float bottom = (int)(position_.y + h_height);

    float sx = 2.f / (right - left);
    float sy = 2.f / (top - bottom);
    float tx = -(right + left) / (right - left);
    float ty = -(top + bottom) / (top - bottom);
    projection_ = { { sx, 0.f, 0.f },{ 0.f, sy, 0.f },{ tx, ty, 1.f } };
}

const mat3& Camera::get_projection() {
    return projection_;
}

const vec2 Camera::get_relative_pos(vec2 pos) {
    return {position_.x - dimensions_.x / 2.f + pos.x, position_.y - dimensions_.y / 2.f + pos.y};
}