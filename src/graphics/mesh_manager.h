//
// Created by alex on 21/01/19.
//

#pragma once

#include <GL/glew.h>
#include <string>
#include <unordered_map>

#include "../util/gl_utils.h"
#include "mesh.h"

// Manages loading/unloading of textures

class MeshManager {
private:
    std::unordered_map<std::string, Mesh> meshes_;

public:
    MeshManager();
    ~MeshManager();

    bool load_mesh(
        const char* name,
        size_t vertex_count,
        TexturedVertex* vertices,
        size_t index_count,
        uint16_t* indices
    );

    bool load_mesh(
            const char* name,
            size_t vertex_count,
            vec3* vertices,
            size_t index_count,
            uint16_t * indices
    );

    bool load_mesh(
            const char* name,
            size_t vertex_count,
            Vertex* vertices,
            size_t index_count,
            uint16_t * indices
    );

    Mesh get_mesh(const char* name);
};