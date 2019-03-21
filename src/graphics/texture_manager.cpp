//
// Created by alex on 24/01/19.
//

#include "texture_manager.h"

#include "gl_include.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "../util/gl_utils.h"

TextureManager::TextureManager() :
    textures_()
{}

TextureManager::~TextureManager() {
    for (auto& texture: textures_) {
        glDeleteTextures(1, &texture.second.id_);
    }
}

bool TextureManager::load_texture(const char *path, const char *name) {
    if (path == nullptr) {
        return false;
    }
    auto key_str = std::string(name);
    if (textures_.count(key_str) > 0) {
        return false; // Texture with given name already loaded!
    }

    int width, height;
    GLuint id;

    stbi_uc* data = stbi_load(path, &width, &height, nullptr, 4);
    if (data == nullptr) {
        return false;
    }
    gl_flush_errors();
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    stbi_image_free(data);

    bool result = !gl_has_errors();

    auto texture = Texture(width, height, id);
    textures_.insert(std::pair<std::string, Texture>(key_str, texture));

    return result;
}

Texture TextureManager::get_texture(const char *name) {
    auto key_str = std::string(name);
    return textures_.at(key_str);
}