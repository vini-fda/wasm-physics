//
// Created by vinicius on 02/11/2020.
//

#ifndef CPP_WASM_PHYSICS_ATOM_H
#define CPP_WASM_PHYSICS_ATOM_H
#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
#include "vec2.h"
#include "Shader.h"
#include "vec2.h"
#include <memory>

class Atom {
public:
    Atom();
    Atom(const vec2& position, const vec2& velocity, float radius=1.0, float mass=1.0);

    //vec2 force{vec2(0,0)};
    vec2 vel{vec2(0, 0)};
    vec2 pos{vec2(0.0, 0.0)};
    double radius{1.0};
    double mass{1.0};

    void draw();
    //void processInput();
    //Updates physics of the Atom
    void update(float dt);
    /* TODO: integrate C++ and javascript */

private:
    std::unique_ptr<Shader> shader;
    static const int NUM_VERTICES = 32;
    float vertices[3*NUM_VERTICES];
    unsigned int VAO=0;
    unsigned int VBO=0;
};




#endif //CPP_WASM_PHYSICS_ATOM_H
