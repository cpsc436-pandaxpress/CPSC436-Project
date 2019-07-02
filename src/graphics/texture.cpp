//
// Created by alex on 24/01/19.
//

#include "texture.h"


Texture::Texture(int width, int height, GLuint id) :
    width_(width),
    height_(height),
    id_(id)
{}

Texture::Texture(const Texture& other) : Texture(other.width_, other.height_, other.id_) {}


uint32_t Texture::width() {
    return width_;
}

uint32_t Texture::height() {
    return height_;
}


void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}