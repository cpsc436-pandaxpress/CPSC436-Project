//
// Created by alex on 20/01/19.
//

#pragma once

#include "input_manager.h"

#include "../graphics/shader_manager.h"
#include "../graphics/texture_manager.h"


// Struct containing all our singletons
// All require individual initialization
struct Blackboard {
    InputManager input_manager;
    ShaderManager shader_manager;
    TextureManager textureManager;
};