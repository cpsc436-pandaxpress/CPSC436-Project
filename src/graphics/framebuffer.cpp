//
// Created by alex on 14/04/19.
//

#include <GL/glew.h>
#include <cstdio>
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

void Framebuffer::test() {
    float pixel_data[4];
    bind();
    glReadPixels(0, 0, 1, 1, GL_RGBA, GL_FLOAT, pixel_data);
    unbind();
}

Texture Framebuffer::get_texture() {
    return Texture(width_, height_, texture_);
}


void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, buffer_);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::resize(uint32_t width, uint32_t height) {
    width_ = width;
    height_ = height;

    // generate the texture
    glBindTexture(GL_TEXTURE_2D, texture_);

    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    // bind the texture to the Framebuffer
    bind();
    glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_, 0
    );
    unbind();

}

