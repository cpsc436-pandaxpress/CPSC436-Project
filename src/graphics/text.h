//
// Created by Prayansh Srivastava on 2019-03-03.
//

#ifndef PANDAEXPRESS_TEXT_H
#define PANDAEXPRESS_TEXT_H

#include <map>
#include <string>
#include "render.h"
#include "shader.h"
#include "mesh.h"
#include "font.h"

class Text : public Renderable {
private:
    Mesh mesh_;
    Shader shader_;
    FontType font_;
    vec2 position_, pixel_scale_;
    vec3 color_;
    float rotation_, scale_;
    std::string text_;

public:
    Text(Shader shader, Mesh mesh, FontType font, vec3 color, const char* text, float width, float height);
    Text(const Text& other);

    void draw(const mat3& projection);

    vec2 pos();
    void set_pos(const vec2& pos);
    void set_pos(float x, float y);

    float scale();
    void set_scale(float scale);

    void set_size(int x_size, int y_size);

    float rotation_rad();
    void set_rotation_rad(float theta);

    vec3 color();
    void set_color(const vec3& color);
    void set_color(float r, float g, float b);
};


#endif //PANDAEXPRESS_TEXT_H
