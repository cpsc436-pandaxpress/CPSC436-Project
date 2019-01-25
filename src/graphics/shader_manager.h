//
// Created by alex on 21/01/19.
//

#pragma once

#include "shader.h"


//TODO: define
//TODO: implement
class ShaderManager {

public:
    ShaderManager();
    ~ShaderManager();

    bool load_shader();

    Shader get_shader();
};