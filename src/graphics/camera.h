//
// Created by alex on 24/01/19.
//

#pragma once

#include "../util/gl_utils.h"

// Defines an orthographic camera for use with OpenGL
//TODO: define
//TODO: implement
class Camera {
private:
    mat3 projection_;
    vec2 dimensions_, position_;

public:
    Camera(float width, float height, float center_x, float center_y);

    void set_size(float width, float height);

    void set_position(float x, float y);

    void compose();

    const mat3& get_projection();


};