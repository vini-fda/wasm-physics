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
//    //The displacement vector between the two atoms
//    let r: vec2 = vec2.create();
//    vec2.sub(r, atom1.pos, atom2.pos);
//    //The relative velocity
//    let V_rel: vec2 = vec2.create();
//    vec2.sub(V_rel, atom1.velocity, atom2.velocity);
//    //let V_rel_dir: vec2 = vec2.create();
//    //vec2.normalize(V_rel_dir, V_rel);
//    let dotP = vec2.dot(V_rel, r);
//    let sqrLen_V_rel = vec2.sqrLen(V_rel);
//    //-p5.Vector.dot(V_rel, dpos) / V_rel.mag();
//    let deltaT = -dotP - Math.sqrt(dotP*dotP - sqrLen_V_rel*(vec2.sqrLen(r) - (atom1.radius + atom2.radius)**2));
//    deltaT /= sqrLen_V_rel;
//    //let deltaT = beta - sqrt(sq(atom1.radius + atom2.radius) - sq(dpos.mag()) + sq(beta));
//    console.log(deltaT);
//    return deltaT;
    //The displacement vector between the two atoms
    vec2 r = (a.pos - b.pos).normalize();
    return 0;
}
