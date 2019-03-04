//
// Created by Prayansh Srivastava on 2019-03-03.
//

#include "text.h"

#include "../util/gl_utils.h"

Text::Text(Shader shader, Mesh mesh, FontType font,
        vec3 color, float width, float height) :
        shader_(shader),
        mesh_(mesh),
        font_(font),
        color_(color)
{
    position_ = {0.f, 0.f};
    pixel_scale_ = {(float) width, (float) height};
    scale_ = 1.f;
    rotation_ = 0.f;
}

Text::Text(const Text& other) :
        shader_(other.shader_),
        mesh_(other.mesh_),
        font_(other.font_),
        position_(other.position_),
        pixel_scale_(other.pixel_scale_),
        scale_(other.scale_),
        color_(other.color_),
        rotation_(other.rotation_)
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
    shader_.set_uniform_vec3("textColor", color_);
    shader_.set_uniform_mat3("projection", projection);

    // bind texture
    glActiveTexture(GL_TEXTURE0);

    // draw!
    // Iterate through all characters
    float x = position_.x;
    std::string::const_iterator c;
    for (c = text_.begin(); c != text_.end(); c++) {
        Character ch = font_.characters[*c];

        GLfloat xpos = position_.x + ch.Bearing.x * scale_;
        GLfloat ypos = position_.y + (font_.characters['H'].Bearing.y - ch.Bearing.y) * scale_;

        GLfloat w = ch.Size.x * scale_;
        GLfloat h = ch.Size.y * scale_;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
                {xpos,     ypos + h, 0.0, 1.0},
                {xpos + w, ypos,     1.0, 0.0},
                {xpos,     ypos,     0.0, 0.0},

                {xpos,     ypos + h, 0.0, 1.0},
                {xpos + w, ypos + h, 1.0, 1.0},
                {xpos + w, ypos,     1.0, 0.0}
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, mesh_.vbo());
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices),
                        vertices); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph
        x += (ch.Advance >> 6) *
             scale_; // Bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
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

float Text::rotation_rad() {
    return rotation_;
}

void Text::set_rotation_rad(float theta) {
    rotation_ = theta;
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