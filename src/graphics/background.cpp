#include "background.h"
#include "../util/gl_utils.h"

Background::Background(Texture texture, Shader shader) :
        shader_(shader),
        texture_(texture),
        sp1_(Sprite(texture, shader)),
        sp2_(Sprite(texture, shader)) {
}

Background::Background(const Background &other) :
        shader_(other.shader_),
        texture_(other.texture_),
        sp1_(other.sp1_),
        sp2_(other.sp2_) {}


void Background::draw(const mat3 &projection) {
    // draw background sprites
    sp1_.draw(projection);
    sp2_.draw(projection);
}

vec2 Background::pos1() {
    return sp1_.pos();
}

vec2 Background::pos2() {
    return sp2_.pos();
}

void Background::set_pos1(const vec2 &pos) {
    sp1_.set_pos(pos);
}

void Background::set_pos1(float x, float y) {
    set_pos1({x, y});
}

void Background::set_pos2(const vec2 &pos) {
    sp2_.set_pos(pos);
}

void Background::set_pos2(float x, float y) {
    set_pos2({x, y});
}

vec2 Background::scale() {
    return sp1_.scale();
}

void Background::set_scale(const vec2 &scale) {
    sp1_.set_scale(scale);
    sp2_.set_scale(scale);
}

void Background::set_scale(float x_scale, float y_scale) {
    set_scale({x_scale, y_scale});
}

float Background::rotation_rad() {
    return sp1_.rotation_rad();
}

void Background::set_rotation_rad(float theta) {
    sp1_.set_rotation_rad(theta);
    sp2_.set_rotation_rad(theta);
}