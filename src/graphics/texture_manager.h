//
// Created by alex on 21/01/19.
//

#pragma once

#include <GL/glew.h>

#include "texture.h"

// Manages loading/unloading of textures
//TODO: define
//TODO: implement
class TextureManager {

public:
    TextureManager();
    ~TextureManager();

    bool load_texture();

    Texture get_texture();
};