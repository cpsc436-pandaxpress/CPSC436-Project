//
// Created by alex on 25/02/19.
//

#include "mesh_manager.h"

MeshManager::MeshManager() : meshes_() {}

MeshManager::~MeshManager() {
    for (auto &entry: meshes_) {
        GLuint vbo, ibo, vao;
        vbo = entry.second.vbo();
        ibo = entry.second.ibo();
        vao = entry.second.vao();
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ibo);
        glDeleteVertexArrays(1, &vao);
    }
}

bool MeshManager::load_mesh(
        const char *name,
        size_t vertex_count,
        TexturedVertex *vertices,
        size_t index_count,
        uint16_t *indices
) {

    auto key_str = std::string(name);
    if (meshes_.count(key_str) > 0) {
        return false; // Mesh with given name already loaded!
    }

    GLuint vao, vbo, ibo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexturedVertex) * vertex_count, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * index_count, indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    bool result = !gl_has_errors();

    auto mesh = Mesh(vao, vbo, ibo);
    meshes_.insert(std::pair<std::string, Mesh>(key_str, mesh));

    return result;
}

bool MeshManager::load_mesh(
        const char *name,
        size_t vertex_count,
        vec3 *vertices,
        size_t index_count,
        uint16_t *indices
) {

    auto key_str = std::string(name);
    if (meshes_.count(key_str) > 0) {
        return false; // Mesh with given name already loaded!
    }

    GLuint vao, vbo, ibo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * vertex_count, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * index_count, indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    bool result = !gl_has_errors();

    auto mesh = Mesh(vao, vbo, ibo);
    meshes_.insert(std::pair<std::string, Mesh>(key_str, mesh));

    return result;
}

bool MeshManager::load_mesh(
        const char *name,
        size_t vertex_count,
        Vertex *vertices,
        size_t index_count,
        uint16_t *indices
) {

    auto key_str = std::string(name);
    if (meshes_.count(key_str) > 0) {
        return false; // Mesh with given name already loaded!
    }

    GLuint vao, vbo, ibo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex_count, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * index_count, indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    bool result = !gl_has_errors();

    auto mesh = Mesh(vao, vbo, ibo);
    meshes_.insert(std::pair<std::string, Mesh>(key_str, mesh));

    return result;
}

Mesh MeshManager::get_mesh(const char *name) {
    auto key_str = std::string(name);
    return meshes_.at(key_str);
}