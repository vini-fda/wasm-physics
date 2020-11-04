//
// Created by vinicius on 02/11/2020.
//

#include "Atom.h"
#include <GL/glew.h>
#include <cmath>
#include <memory>

//#include <glm/gtc/matrix_transform.hpp>
//using namespace glm;
#include <string>

Atom::Atom()
{
    //Vertices set up
    for (size_t i = 0; i < NUM_VERTICES; i++) {
        float theta = 2.0*i*M_PI/NUM_VERTICES;
        vertices[3*i] = cosf(theta);
        vertices[3*i+1] = sinf(theta);
        vertices[3*i+2] = 0.0;
    }
    //Vertex shader
    std::string vs = "#version 100\n"
                     "attribute vec4 vPos;\n"
                     "void main()\n"
                     "{\n"
                     "   gl_Position = vPos;\n"
                     "}";
    //Fragment shader
    std::string fs = "#version 100\n"
                     "precision mediump float;\n"
                     "void main()\n"
                     "{\n"
                     "   gl_FragColor = vec4(1.0, 0.0, 0.2, 1.0);\n"
                     "}";

    //Shader set up
    shader = std::make_unique<Shader>(vs.c_str(), fs.c_str());
    //VBO & VAO
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    //Initialization
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
}
Atom::Atom(const vec2& position, const vec2& velocity, float radius, float mass) : Atom()
{
    this->pos = position;
    this->vel = velocity;
    this->radius = radius / 20.0; //TODO:ADD A PROJECTION MATRIX SO I DON'T HAVE TO USE THIS HACK
    this->mass = mass;
}
void Atom::draw()
{
    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_LOOP, 0, NUM_VERTICES);
}

void Atom::update(float dt) {
    this->pos += this->vel * dt;
}
