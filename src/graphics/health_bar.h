//
// Created by Prayansh Srivastava on 2019-03-06.
//

#ifndef PANDAEXPRESS_HEALTH_BAR_H
#define PANDAEXPRESS_HEALTH_BAR_H


#include "render.h"
#include "shader.h"
#include "mesh.h"

class HealthBar : public Renderable {
private:
    Shader shader_;
    Mesh mesh_;
    vec2 position_, size_, scale_;
    vec3 color_start_, color_end_;
    float rotation_;
public:
    static vec3 vertices[4];
    static uint16_t indices[6];

    HealthBar(Mesh mesh, Shader shader, vec2 size);
    HealthBar(const HealthBar& other);

    void draw(const mat3& projection);

    vec2 pos();
    void set_pos(const vec2& pos);
    void set_pos(float x, float y);

    vec2 scale();
    void set_scale(const vec2& scale);
    void set_scale(float x_scale, float y_scale);

    vec2 size();
    void set_size(int x_size, int y_size);

    float rotation_rad();
    void set_rotation_rad(float theta);

    vec3 color_start();
    void set_color_start(const vec3& color);
    void set_color_start(float r, float g, float b);

    vec3 color_end();
    void set_color_end(const vec3& color);
    void set_color_end(float r, float g, float b);
};


#endif //PANDAEXPRESS_HEALTH_BAR_H
