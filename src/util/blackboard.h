//
// Created by alex on 20/01/19.
//

#pragma once

#include "input_manager.h"

#include "../graphics/camera.h"
#include "../graphics/shader_manager.h"
#include "../graphics/texture_manager.h"
#include "../graphics/window.h"


// Struct containing all our singletons
// All require individual initialization
struct Blackboard {
    Camera camera;
    float delta_time;
    InputManager input_manager;
    ShaderManager shader_manager;
    TextureManager textureManager;
    Window& window;
};