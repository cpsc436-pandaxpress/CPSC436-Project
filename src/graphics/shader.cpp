//
// Created by alex on 24/01/19.
//

#include "shader.h"


Shader::Shader(GLuint vert_id, GLuint frag_id, GLuint program_id) :
    vert_id_(vert_id),
    frag_id_(frag_id),
    program_id_(program_id)
{}

Shader::Shader(const Shader& other) :
    vert_id_(other.vert_id_),
    frag_id_(other.frag_id_),
    program_id_(other.program_id_)
{}

void Shader::bind() {
    glUseProgram(program_id_);
}

void Shader::unbind() {
    glUseProgram(0);
}

void Shader::set_uniform_vec2(const char* loc, const vec2& val) {
    GLint uniform_uloc = glGetUniformLocation(program_id_, loc);
    glUniform2fv(uniform_uloc, 1, (float*)&val);
}

void Shader::set_uniform_vec3(const char* loc, const vec3& val) {
    GLint uniform_uloc = glGetUniformLocation(program_id_, loc);
    glUniform3fv(uniform_uloc, 1, (float*)&val);

}

void Shader::set_uniform_mat3(const char* loc, const mat3& val) {
    GLint uniform_uloc = glGetUniformLocation(program_id_, loc);
    glUniformMatrix3fv(uniform_uloc, 1, GL_FALSE, (float*)&val);

}

void Shader::set_input_vec2(const char* loc, size_t vertex_size, size_t attrib_offset)  {
    GLint input_loc = glGetAttribLocation(program_id_, loc);
    glEnableVertexAttribArray(input_loc);
    glVertexAttribPointer(input_loc, 2, GL_FLOAT, GL_FALSE, vertex_size, (void*)attrib_offset);
}

void Shader::set_input_vec3(const char* loc, size_t vertex_size, size_t attrib_offset)  {
    GLint input_loc = glGetAttribLocation(program_id_, loc);
    glEnableVertexAttribArray(input_loc);
    glVertexAttribPointer(input_loc, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)attrib_offset);
}

void Shader::set_uniform_float(const char *loc, const float value) {
    glUniform1f(glGetUniformLocation(program_id_, loc), value);
}

void Shader::set_uniform_int(const char *loc, int value) {
    glUniform1i(glGetUniformLocation(program_id_, loc), value);
}
