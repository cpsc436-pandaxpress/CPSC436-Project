//
// Created by Avery Brown on 2019-03-29.
//

#ifndef PANDAEXPRESS_FADE_H
#define PANDAEXPRESS_FADE_H


#include "render.h"
#include "shader.h"
#include "../util/blackboard.h"

//
class FadeOverlay : public Renderable {
private:
    Shader shader_;
    Mesh mesh_;
    vec2 position_, size_, scale_;
    float alpha_;
    bool fadeIn_;

public:

    FadeOverlay(Mesh mesh, Shader shader, vec2 size);
    FadeOverlay(const FadeOverlay& other);

    void draw(const mat3& projection);

    vec2 pos();
    void set_pos(const vec2& pos);
    void set_pos(float x, float y);

    vec2 scale();
    void set_scale(const vec2& scale);
    void set_scale(float x_scale, float y_scale);

    vec2 size();
    void set_size(int x_size, int y_size);

    void set_alpha(float alpha);
    float alpha();

    void set_fadeIn(bool fade_in);
    bool fadeIn();
};

#endif //PANDAEXPRESS_FADE_H
