#include "background.h"
#include "../util/gl_utils.h"

Background::Background(Texture texture, Shader shader, Mesh mesh, int z, bool infinite = true) :
        shader_(shader),
        texture_(texture),
        sp1_(Sprite(texture, shader, mesh)),
        sp2_(Sprite(texture, shader, mesh)),
        z(z),
        infinite(infinite) {
}

Background::Background(Texture texture, Shader shader, Mesh mesh, int z) :
        shader_(shader),
        texture_(texture),
        sp1_(Sprite(texture, shader, mesh)),
        sp2_(Sprite(texture, shader, mesh)),
        z(z),
        infinite(true) {
}

Background::Background(const Background &other) :
        shader_(other.shader_),
        texture_(other.texture_),
        sp1_(other.sp1_),
        sp2_(other.sp2_),
        z(other.z),
        infinite(other.infinite) {}


void Background::draw(const mat3 &projection) {
    // draw background sprites
    sp1_.draw(projection);
    if (infinite) {
        sp2_.draw(projection);
    }
}

vec2 Background::pos1() {
    return sp1_.pos();
}

vec2 Background::pos2() {
    return sp2_.pos();
}

void Background::set_pos1(const vec2 &pos) {
    sp1_.set_pos((int)pos.x, (int)pos.y);
//    sp1_.set_pos(pos.x, pos.y);
}

void Background::set_pos1(float x, float y) {
    set_pos1({x, y});
}

void Background::set_pos2(const vec2 &pos) {
    sp2_.set_pos((int)pos.x, (int)pos.y);
//    sp2_.set_pos(pos.x, pos.y);
}

void Background::set_pos2(float x, float y) {
    set_pos2({x, y});
}


vec2 Background::scale() {
    return sp1_.scale();
}

void Background::set_scale(const vec2 &scale) {
    sp1_.set_scale_int(scale.x, scale.y);
    sp2_.set_scale_int(scale.x, scale.y);
}

void Background::set_scale(float x_scale, float y_scale) {
    set_scale({x_scale, y_scale});
}

void Background::set_size(int x_size, int y_size) {
    set_scale(
        (float)x_size / texture_.width(),
        (float)y_size / texture_.height()
    );
}


float Background::rotation_rad() {
    return sp1_.rotation_rad();
}

void Background::set_rotation_rad(float theta) {
    sp1_.set_rotation_rad(theta);
    sp2_.set_rotation_rad(theta);
}

int Background::z_pos() {
    return z;
}

void Background::set_z_pos(int z_pos) {
    z = z_pos;
}

vec2 Background::texture_size() {
    return {(float) texture_.width(), (float) texture_.height()};
}


