//
// Created by Prayansh Srivastava on 2019-03-03.
//

#ifndef PANDAEXPRESS_FONT_H
#define PANDAEXPRESS_FONT_H

#include <map>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
    GLuint Advance;     // Horizontal offset to advance to next glyph
};

class FontType {
public:
    FontType();
    FontType(const FontType &other);
    // Holds a list of pre-compiled Characters
    std::map<GLchar, Character> characters;
    void load(std::string font, GLuint fontSize);
};


#endif //PANDAEXPRESS_FONT_H
