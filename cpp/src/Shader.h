#ifndef EMSCRIPTEN_SDL_TEST_SHADER_H
#define EMSCRIPTEN_SDL_TEST_SHADER_H

#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>

#include <glm/mat4x4.hpp>


class Shader {
private:
    GLuint shader_program;
public:
    Shader(const char* vertexSource, const char* fragmentSource) {
        //Vertex shader
        GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertexSource, NULL);
        glCompileShader(vertex_shader);
        GLint vertex_shader_status;
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_shader_status);

        char vertexLogBuffer[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, vertexLogBuffer);
        std::cout << "vertex_shader_status: " << vertex_shader_status << " " << vertexLogBuffer << std::endl;

        //Fragment shader
        GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragmentSource, NULL);
        glCompileShader(fragment_shader);
        GLint fragment_shader_status;
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_shader_status);

        char fragmentLogBuffer[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, fragmentLogBuffer);
        std::cout << "fragment_shader_status: " << fragment_shader_status << " " << fragmentLogBuffer << std::endl;

        //Shader program
        shader_program = glCreateProgram();
        glAttachShader(shader_program, vertex_shader);
        glAttachShader(shader_program, fragment_shader);
        glLinkProgram(shader_program);
    }
    void use() const {
        glUseProgram(shader_program);
    }
    GLuint getID() const {
        return shader_program;
    }
    void setMat4(const std::string &name, glm::mat4 mat) const;

};


#endif //EMSCRIPTEN_SDL_TEST_SHADER_H
