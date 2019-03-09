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
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
}

void Mesh::unbind() {
    glBindVertexArray(0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // apparently redundant https://stackoverflow.com/a/25415474
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}