//
// Created by Prayansh Srivastava on 2019-03-03.
//

#include "text.h"
#include "../util/gl_utils.h"

Text::Text(Shader shader, Mesh mesh, FontType font, std::string text) :
        shader_(shader),
        mesh_(mesh),
        font_(font),
        text_(text)
{
    position_ = {0.f, 0.f};
    color_ = {1.0f, 1.0f, 1.0f};
    scale_ = 1.f;
}

Text::Text(const Text& other) :
        shader_(other.shader_),
        mesh_(other.mesh_),
        font_(other.font_),
        position_(other.position_),
        scale_(other.scale_),
        color_(other.color_)
{}

void Text::draw(const mat3& projection) {
    // bind shader
    shader_.bind();

    // setup blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    // bind buffers
    mesh_.bind();

    // setup attributes
    shader_.set_input_vec3("in_position", sizeof(TexturedVertex), 0);
    shader_.set_input_vec3("in_texcoord", sizeof(TexturedVertex), sizeof(vec3));

    //setup uniforms
    shader_.set_uniform_vec3("fcolor", color_);
    shader_.set_uniform_mat3("projection", projection);

    float x = position_.x;
    std::string::const_iterator i;
    for (i = text_.begin(); i != text_.end(); i++) {
        auto chTex = font_.characters[*i];
        auto texture = Texture(static_cast<int>(chTex.size.x), static_cast<int>(chTex.size.y), chTex.tex_id);

        mat3 transform = {
                { 1.f, 0.f, 0.f },
                { 0.f, 1.f, 0.f },
                { 0.f, 0.f, 1.f }
        };

        GLfloat xpos = x + chTex.bearing.x * scale_;
        GLfloat ypos = position_.y + (chTex.size.y - chTex.bearing.y) * scale_;
        mul_in_place(transform, make_translate_mat3(xpos, ypos));
        mul_in_place(transform,
                     make_scale_mat3(scale_ * texture.width(), scale_ * texture.height()));
        shader_.set_uniform_mat3("transform", transform);
        glActiveTexture(GL_TEXTURE0);
        texture.bind();

        // draw!
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);

        // unbind texture
        texture.unbind();
        x += (chTex.advance >> 6) * scale_;
    }

    // unbind buffers
    mesh_.unbind();

    // unbind shader
    shader_.unbind();
}

vec2 Text::pos() {
    return { position_.x, position_.y };
}

void Text::set_pos(const vec2& pos) {
    position_ = { pos.x, pos.y };
}

void Text::set_pos(float x, float y) {
    position_ = { x, y };
}

float Text::scale() {
    return scale_;
}

void Text::set_scale(float scale) {
    scale_ = scale;
}

void Text::set_size(int x_size, int y_size) {
}

vec3 Text::color() {
    return color_;
}

void Text::set_color(const vec3& color) {
    color_ = { color_.x, color_.y, color_.z };
}

void Text::set_color(float r, float g, float b) {
    color_ = { r, g, b };
}

std::string Text::text() {
    return text_;
}

void Text::set_text(std::string text) {
    text_ = text;
}