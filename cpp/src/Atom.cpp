//
// Created by vinicius on 02/11/2020.
//

#include "Atom.h"
#include <GL/glew.h>
#include <cmath>
#include <memory>


#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
//using namespace glm;
#include <string>

int Atom::count_instances = 0;
float Atom::vertices[] = {0.0};

Atom::Atom()
{
    if(count_instances == 0) {
        //Vertices set up
        for (size_t i = 0; i < NUM_VERTICES; i++) {
            float theta = 2.0*i*M_PI/NUM_VERTICES;
            vertices[3*i] = cosf(theta);
            vertices[3*i+1] = sinf(theta);
            vertices[3*i+2] = 0.0;
        }
    }
    count_instances++;


    //Vertex shader
    std::string vs = "#version 100\n"
                     "attribute vec4 vPos;\n"
                     "uniform mat4 model;\n"
                     "void main()\n"
                     "{\n"
                     "   gl_Position = model * vPos;\n"
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
    this->radius = radius;
    this->mass = mass;
}
void Atom::draw()
{
    shader->use();
    model = glm::mat4(1.0f);
    model = translate(model, glm::vec3(pos.x, pos.y, 0.0));
    model = scale(model, glm::vec3(radius, radius, 1.0));
    shader->setMat4("model", model);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_LOOP, 0, NUM_VERTICES);
}

void Atom::update(float dt) {
    this->pos += this->vel * dt;
}

float collision_time(const Atom &a, const Atom &b) {
    //The displacement vector between the two atoms
    vec2 r = a.pos - b.pos;
    //Relative velocity
    vec2 v_rel = a.vel - b.vel;
    //Dot product
    float P = v_rel * r;
    //Squared length/norm of relative velocity
    float sqV = norm2(v_rel);
    //The collision time
    float deltaT = -P - sqrtf(P*P - sqV*(norm2(r) - (a.radius + b.radius)*(a.radius + b.radius)));
    deltaT /= sqV;

    return deltaT;
}

/* Should be called when a and b collide */
void resolve_collision(Atom &a, Atom &b) {
    //r is the direction which connects the two atoms
    vec2 r = (a.pos - b.pos).normalize();
    //n is perpendicular to r
    vec2 n = perpTo(r);

    //n and r are orthonormal basis vectors
    /* Calculate each velocity component
    * we must calculate those parallel to r */

    //Velocity parallel to r
    float va_r = (a.mass - b.mass)*(r * a.vel) + 2*b.mass*(r * b.vel);
    va_r /= a.mass + b.mass;
    float vb_r = (b.mass - a.mass)*(r * b.vel) + 2*a.mass*(r * a.vel);
    vb_r /= a.mass + b.mass;

    //Velocities after collision
    a.vel = proj(a.vel, n) + va_r * r;
    b.vel = proj(b.vel, n) + vb_r * r;

}
