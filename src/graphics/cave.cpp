//
// Created by Rebecca Roth on 2019-03-08.
//

#include "cave.h"
#include "util/constants.h"

Vertex Cave::vertices[] = {
        Vertex{
                {0.0f,10.0f,0.0f},
                {169,169,169}
            },
        Vertex{{0.0f,9.0f,0.0f},
             {169,169,169}},
        Vertex{{-1.0f,9.0f,0.0f},
               {128,128,128}},
        Vertex{{-2.0f,10.0f,0.0f},
               {169,169,169}},
        Vertex{
                {-3.0f,9.0f,0.0f},
                {169,169,169}
            },
        Vertex{
                {-3.0f,10.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-4.0f,10.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-5.0f,10.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-5.0f,9.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-3.0f,8.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-4.0f,8.0f,0.0f},
                {128,128,128}
        },
        Vertex{
                {-5.0f,8.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-4.0f,7.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-4.0f,9.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-1.0f,8.0f,0.0f},
                {105,105,105}
        },
        Vertex{
                {-2.0f,8.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-2.0f,6.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-3.0f,7.0f,0.0f},
                {108,108,108}
        },
        Vertex{
                {-3.0f,5.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-4.0f,6.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-4.0f,5.0f,0.0f},
                {128,128,128}
        },
        Vertex{
                {-4.0f,4.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-4.0f,3.0f,0.0f},
                {108,108,108}
        },
        Vertex{
                {-7.0f,2.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-10.0f,2.0f,0.0f},
                {50,50,50}
        },
        Vertex{
                {-10.0f,3.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-7.0f,4.0f,0.0f},
                {108,108,108}
        },
        Vertex{
                {-6.0f,4.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-6.0f,5.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-10.0f,5.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-7.0f,6.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-10.0f,7.0f,0.0f},
                {50,50,50}
        },
        Vertex{
                {-6.0f,7.0f,0.0f},
                {128,128,128}
        },
        Vertex{
                {-7.0f,8.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-10.0f,9.0f,0.0f},
                {105,105,105}
        },
        Vertex{
                {-7.0f,10.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-10.0f,10.0f,0.0f},
                {169,169,169}
        },
        Vertex{
                {-2.8,10.0f,0.0f},
                {0,0,0}
        },
        Vertex{
                {-2.8,8.0f,0.0f},
                {0,0,0}
        },
        Vertex{
                {-5.2,10.0f,0.0f},
                {0,0,0}
        },
        Vertex{
                {-5.2,8.0f,0.0f},
                {0,0,0}
        }
};

Vertex Cave::entrance_vertices[] = {
        Vertex{
                {-2.8,10.0f,0.0f},
                {0,0,0}
        },
        Vertex{
                {-2.8,8.0f,0.0f},
                {0,0,0}
        },
        Vertex{
                {-5.2,10.0f,0.0f},
                {0,0,0}
        },
        Vertex{
                {-5.2,8.0f,0.0f},
                {0,0,0}
        }
};

uint16_t Cave::entrance_indices[] = {
        0,1,2,
        0,2,3
};

uint16_t Cave::indices[] = {
        37,39,38,
        38,39,40,
        18,24,29,
        18,29,36,
        34,35,36,
        8,34,35,
        8,33,34,
        30,31,32,
        29,30,31,
        31,32,33,
        31,33,34,
        0,1,2,
        0,2,3,
        2,3,4,
        3,4,5,
        4,5,6,
        6,5,8,
        4,6,8,
        4,9,10,
        8,10,11,
        9,10,12,
        10,11,12,
        4,10,13,
        8,10,13,
        1,2,14,
        2,14,15,
        14,15,16,
        2,4,15,
        4,15,17,
        15,16,17,
        9,12,17,
        16,17,19,
        16,18,19,
        18,19,20,
        18,20,21,
        18,21,22,
        12,17,19,
        21,22,23,
        23,24,25,
        23,25,26,
        23,26,27,
        21,23,27,
        21,26,28,
        20,21,28,
        19,20,28,
        25,26,29,
        23,26,29,
        23,29,30,
        19,25,30,
        19,30,32,
        12,19,32,
        11,12,32,
        11,32,33,
        8,11,33,
        7,8,35,
};

Cave::Cave(Mesh mesh, Shader shader, vec2 size, vec2 scale, bool growing) :
        shader_(shader),
        mesh_(mesh),
        size_(size),
        scale_(scale) {
    position_ = {0.f, 0.f};
    rotation_ = 0.f;
    status_ = 0;
    growing = growing;
}

Cave::Cave(const Cave &other) :
        shader_(other.shader_),
        mesh_(other.mesh_),
        position_(other.position_),
        scale_(other.scale_),
        rotation_(other.rotation_),
        status_(other.status_)
{}

void Cave::draw(const mat3 &projection) {
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
            sizeof(vec3)  // offset = sizeOf(vec3)
    );

    shader_.set_uniform_mat3("transform", transform);
    shader_.set_uniform_mat3("projection", projection);

    // draw!
    glDrawElements(GL_TRIANGLES, 165, GL_UNSIGNED_SHORT, nullptr);

    // unbind buffer
    mesh_.unbind();

    // unbind shader
    shader_.unbind();
}

vec2 Cave::pos() {
    return {position_.x, position_.y};
}

void Cave::set_pos(const vec2 &pos) {
    position_ = {pos.x, pos.y};
}

void Cave::set_pos(float x, float y) {
    position_ = {x, y};
}

vec2 Cave::scale() {
    return {scale_.x, scale_.y};
}

void Cave::set_scale(const vec2 &scale) {
    scale_ = {scale.x, scale.y};
}

void Cave::set_scale(float x_scale, float y_scale) {
    scale_ = {x_scale, y_scale};
}

vec2 Cave::size() {
    return size_;
}

void Cave::set_size(int x_size, int y_size) {
    size_ = {(float) x_size, (float) y_size};
}

float Cave::rotation_rad() {
    return rotation_;
}

void Cave::set_rotation_rad(float theta) {
    rotation_ = theta;
}

vec3 Cave::color_start() {
    return color_start_;
}

void Cave::set_color_start(const vec3 &color) {
    color_start_ = {color.x, color.y, color.z};
}

void Cave::set_color_start(float r, float g, float b) {
    color_start_ = {r, g, b};
}

vec3 Cave::color_end() {
    return color_end_;
}

void Cave::set_color_end(const vec3 &color) {
    color_end_ = {color.x, color.y, color.z};
}

void Cave::set_color_end(float r, float g, float b) {
    color_end_ = {r, g, b};
}

void Cave::set_status(int flag) {
    status_ = flag;
}

int Cave::status() {
    return status_;
}