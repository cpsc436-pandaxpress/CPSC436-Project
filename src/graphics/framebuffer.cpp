//
// Created by alex on 14/04/19.
//

#include <GL/glew.h>
#include "framebuffer.h"
#include "texture.h"
#include "gl_include.h"


Framebuffer::Framebuffer(uint32_t width, uint32_t height) {
    // generate the Framebuffer
    glGenFramebuffers(1, &buffer_);

    // generate the texture
    glGenTextures(1, &texture_);

    resize(width, height);
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &buffer_);
    glDeleteTextures(1, &texture_);
}

Texture Framebuffer::get_texture() {
    return Texture(_width, _height, texture_);
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, buffer_);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::resize(uint32_t width, uint32_t height) {
    _width = width;
    _height = height;

    // generate the texture
    glBindTexture(GL_TEXTURE_2D, texture_);

    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_FLOAT, NULL
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    // bind the texture to the Framebuffer
    glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_, 0
    );

    glBindTexture(GL_TEXTURE_2D, 0);
}

