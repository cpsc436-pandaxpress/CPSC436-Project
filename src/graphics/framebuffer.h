//
// Created by alex on 24/01/19.
//

#pragma once

// Owning wrapper of an OpenGL framebuffer
//TODO: define
//TODO: implement
class Framebuffer {
public:
    Framebuffer();
    ~Framebuffer();

    Texture get_texture();

    void resize();
};
