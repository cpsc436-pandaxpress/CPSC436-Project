//
// Created by alex on 21/01/19.
//

#pragma once

#include <optional>
#include <string>
#include <unordered_map>

#include "shader.h"


class ShaderManager {
private:
    std::unordered_map<std::string, Shader> shaders_;

public:
    ShaderManager();
    ~ShaderManager();

    bool load_shader(const char* vert_path, const char* frag_path, const char* name);

    Shader get_shader(const char* name);

private:

    void release_shader(GLuint vert_id, GLuint frag_id, GLuint program_id);
};