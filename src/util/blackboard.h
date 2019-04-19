//
// Created by alex on 20/01/19.
//

#pragma once

#include <graphics/font_manager.h>
#include "input_manager.h"

#include "../graphics/camera.h"
#include "../graphics/mesh_manager.h"
#include "../graphics/shader_manager.h"
#include "../graphics/texture_manager.h"
#include "../graphics/window.h"
#include "../util/random.h"
#include "../util/constants.h"
#include "../util/sound_manager.h"


// Struct containing all our singletons
// All require individual initialization
struct Blackboard {
    Camera camera;
    float delta_time;
    InputManager input_manager;
    MeshManager mesh_manager;
    ShaderManager shader_manager;
    TextureManager texture_manager;
    Window& window;
    Random randNumGenerator;
    SoundManager soundManager;
    FontManager fontManager;
    std::unique_ptr<Shader> post_process_shader;
    float score;
};