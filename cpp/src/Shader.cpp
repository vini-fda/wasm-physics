//
// Created by vinicius on 02/11/2020.
//

#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

void Shader::setMat4(const std::string &name, glm::mat4 mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(shader_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}