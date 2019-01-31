//
// Created by alex on 27/01/19.
//

#pragma once

#include <cmath>

struct Transform {
    float x, y;
    float theta;
    float x_scale, y_scale;

    Transform(float x, float y, float theta, float x_scale, float y_scale) :
        x(x), y(y), theta(theta), x_scale(x_scale), y_scale(y_scale) {};
    Transform(float x, float y, float theta) : x(x), y(y), theta(theta), x_scale(1), y_scale(1) {}
    Transform() : Transform(0, 0, 0) {}
    Transform(const Transform& other) : Transform(other.x, other.y, other.theta, other.x_scale, other.y_scale) {}

    void set_angle_degrees(float degrees) {
        theta = degrees / 180 * M_PI;
    }
};