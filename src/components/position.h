//
// Created by alex on 27/01/19.
//

#pragma once

#include <cmath>

struct Position {
    float x, y;
    float theta;

    Position(float x, float y, float theta) : x(x), y(y), theta(theta) {}
    Position() : Position(0, 0, 0) {}
    Position(const Position& other) : Position(other.x, other.y, other.theta) {}

    void set_angle_degrees(float degrees) {
        theta = degrees / 180 * M_PI;
    }
};