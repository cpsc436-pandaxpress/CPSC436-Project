//
// Created by Prayansh Srivastava on 2019-03-03.
//

#ifndef PANDAEXPRESS_FONT_H
#define PANDAEXPRESS_FONT_H

#include <unordered_map>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "texture.h"
#include <util/gl_utils.h>

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    GLuint tex_id;   // ID handle of the glyph texture
    vec2 size;    // Size of glyph
    vec2 bearing; // Offset from baseline to left/top of glyph
    GLuint advance;     // Horizontal offset to advance to next glyph
};

class FontType {
public:
    FontType();
    FontType(const FontType &other);
    // Holds a list of pre-compiled Characters
    std::unordered_map<GLchar, Character> characters;
    bool load(std::string font, GLuint fontSize);
};


#endif //PANDAEXPRESS_FONT_H
