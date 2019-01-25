//
// Created by alex on 24/01/19.
//

#include "texture.h"


Texture::Texture(int width, int height, GLuint id) :
    width(width),
    height(height),
    id_(id)
{}

Texture::Texture(const Texture& other) :
    width(other.width),
    height(other.height),
    id_(other.id_)
{}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}