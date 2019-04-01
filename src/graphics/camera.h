//
// Created by alex on 24/01/19.
//

#pragma once

#include "../util/gl_utils.h"

// Defines an orthographic camera for use with OpenGL
class Camera {
private:
    mat3 projection_;
    vec2 dimensions_, position_;

public:
    Camera(float width, float height, float center_x, float center_y);

    void set_size(float width, float height);

    vec2 size() const;

    void set_position(float x, float y);

    vec2 position() const;

    void compose();

    const mat3& get_projection();

    bool in_transition;
    bool pre_transition;
};