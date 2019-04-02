//
// Created by Prayansh Srivastava on 2019-03-28.
//

#include "font_manager.h"

FontManager::FontManager() : fonts_() {

}

FontManager::~FontManager() {
    for (auto &font: fonts_) {
        font.second.deleteTextures();
    }
}

bool FontManager::load_font(const char *path, const char *name, const unsigned int fontSize) {
    if (path == nullptr) {
        return false;
    }
    auto key_str = std::string(name);
    if (fonts_.count(key_str) > 0) {
        return false; // Texture with given name already loaded!
    }
    FontType font = FontType();
    bool loaded = font.load(path, fontSize);
    if (loaded) {
        fonts_.insert(std::pair<std::string, FontType>(key_str, font));
    }
    return loaded;
}

FontType FontManager::get_font(const char *name) {
    auto key_str = std::string(name);
    return fonts_.at(key_str);
}
