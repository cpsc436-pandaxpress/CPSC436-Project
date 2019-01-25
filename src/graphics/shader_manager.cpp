//
// Created by alex on 24/01/19.
//

#include "shader_manager.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "../util/gl_utils.h"

ShaderManager::ShaderManager() :
    shaders_()
{}

ShaderManager::~ShaderManager() {
    for (auto& entry : shaders_) {
        auto& shader = entry.second;
        release_shader(shader.vert_id_, shader.frag_id_, shader.program_id_);
    }
}

// adapted from salmon game code

bool ShaderManager::load_shader(const char *vert_path, const char *frag_path, const char *name) {
    auto key_str = std::string(name);
    if (shaders_.count(key_str) > 0) {
        return false; // shader with given name already exists
    }

    gl_flush_errors();

    GLuint vert, frag, program;

    // Opening files
    std::ifstream vs_is(vert_path);
    std::ifstream fs_is(frag_path);

    if (!vs_is.good() || !fs_is.good())
    {
        fprintf(stderr, "Failed to load shader files %s, %s", vert_path, frag_path);
        return false;
    }

    // Reading sources
    std::stringstream vs_ss, fs_ss;
    vs_ss << vs_is.rdbuf();
    fs_ss << fs_is.rdbuf();
    std::string vs_str = vs_ss.str();
    std::string fs_str = fs_ss.str();
    const char* vs_src = vs_str.c_str();
    const char* fs_src = fs_str.c_str();
    GLsizei vs_len = (GLsizei)vs_str.size();
    GLsizei fs_len = (GLsizei)fs_str.size();

    vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vs_src, &vs_len);
    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fs_src, &fs_len);

    // Compiling
    // Shaders already delete if compilation fails
    if (!gl_compile_shader(vert))
        return false;

    if (!gl_compile_shader(frag))
    {
        glDeleteShader(vert);
        return false;
    }

    // Linking
    program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);
    {
        GLint is_linked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &is_linked);
        if (is_linked == GL_FALSE)
        {
            GLint log_len;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
            std::vector<char> log(log_len);
            glGetProgramInfoLog(program, log_len, &log_len, log.data());

            release_shader(vert, frag, program);
            fprintf(stderr, "Link error: %s", log.data());
            return false;
        }
    }

    if (gl_has_errors())
    {
        release_shader(vert, frag, program);
        fprintf(stderr, "OpenGL errors occured while compiling Effect");
        return false;
    }

    auto shader = Shader(vert, frag, program);
    shaders_.insert(std::pair(key_str, shader));

    return true;
}

Shader ShaderManager::get_shader(const char* name) {
    auto key_str = std::string(name);
    return shaders_.at(key_str);
}

void ShaderManager::release_shader(GLuint vert_id, GLuint frag_id, GLuint program_id) {
    glDeleteProgram(program_id);
    glDeleteShader(vert_id);
    glDeleteShader(frag_id);
}