#pragma once

#include "mesh.h"
#include "render.h"
#include "shader.h"
#include "shader_manager.h"
#include "texture.h"
#include "sprite.h"

class Background : public Renderable {
private:
    Shader shader_;
    Texture texture_;
    Sprite sp1_, sp2_;

public:
    Background(Texture texture, Shader shader);

    Background(const Background &other);

    void draw(const mat3 &projection);

    vec2 pos1();

    vec2 pos2();

    void set_pos1(const vec2 &pos);

    void set_pos1(float x, float y);

    void set_pos2(const vec2 &pos);

    void set_pos2(float x, float y);

    vec2 scale();

    void set_scale(const vec2 &scale);

    void set_scale(float x_scale, float y_scale);

    float rotation_rad();

    void set_rotation_rad(float theta);
};