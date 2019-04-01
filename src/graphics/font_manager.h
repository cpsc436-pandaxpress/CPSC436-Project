//
// Created by Prayansh Srivastava on 2019-03-28.
//

#ifndef PANDAEXPRESS_FONT_MANAGER_H
#define PANDAEXPRESS_FONT_MANAGER_H

#include <GL/glew.h>
#include <string>
#include <unordered_map>

#include "font.h"

class FontManager {
private:
    std::unordered_map<std::string, FontType> fonts_;

public:
    FontManager();
    ~FontManager();

    bool load_font(const char* path, const char* name, const unsigned int fontSize);

    FontType get_font(const char* name);
};


#endif //PANDAEXPRESS_FONT_MANAGER_H
