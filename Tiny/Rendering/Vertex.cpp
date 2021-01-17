//
//  Vertex.cpp
//  Shaders
//
//  Created by Jeppe Nielsen on 03/07/15.
//  Copyright (c) 2015 Jeppe Nielsen. All rights reserved.
//

#include "Vertex.hpp"

using namespace Tiny;

template<> const VertexAttribute VertexAttributeType<glm::vec3>::attribute() {
    return VertexAttribute(  3, GL_FLOAT, GL_FALSE );
}

template<> const VertexAttribute VertexAttributeType<glm::vec2>::attribute() {
    return VertexAttribute(2, GL_FLOAT, GL_FALSE);
}

template<> const VertexAttribute VertexAttributeType<Color>::attribute() {
    return VertexAttribute(4, GL_UNSIGNED_BYTE, GL_TRUE);
}

template<> void ShaderVariableType<float>::SetValue(GLint location, const float &value) {
    glUniform1f(location, value);
}
template<> GLenum ShaderVariableType<float>::GetType() { return GL_FLOAT; }

template<> void ShaderVariableType<glm::vec2>::SetValue(GLint location, const glm::vec2 &value) {
    glUniform2f(location, value.x, value.y);
}
template<> GLenum ShaderVariableType<glm::vec2>::GetType() { return GL_FLOAT_VEC2; }

template<> void ShaderVariableType<glm::vec3>::SetValue(GLint location, const glm::vec3 &value) {
    glUniform3f(location, value.x, value.y, value.z);
}
template<> GLenum ShaderVariableType<glm::vec3>::GetType() { return GL_FLOAT_VEC3; }

template<> void ShaderVariableType<glm::mat4x4>::SetValue(GLint location, const glm::mat4x4 &value) {
    //glUniformMatrix4fv(location, 1, GL_FALSE, value.GetGlMatrix());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
template<> GLenum ShaderVariableType<glm::mat4x4>::GetType() { return GL_FLOAT_MAT4; }

template<> void ShaderVariableType<Color>::SetValue(GLint location, const Color &value) {
    glUniform4f(location, value.R(), value.G(), value.B(), value.A());
}
template<> GLenum ShaderVariableType<Color>::GetType() { return GL_FLOAT_VEC4; }

