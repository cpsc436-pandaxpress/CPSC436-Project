//
// Created by alex on 24/01/19.
//
#include "mesh.h"

Mesh::Mesh(GLuint vao, GLuint vbo, GLuint ibo) :
    vao_(vao),
    vbo_(vbo),
    ibo_(ibo)
{}

Mesh::Mesh(const Mesh &other) :
    vao_(other.vao_),
    vbo_(other.vbo_),
    ibo_(other.ibo_)
{}

void Mesh::bind() {
    glBindVertexArray(vao_);
}

void Mesh::unbind() {
    glBindVertexArray(0);
}