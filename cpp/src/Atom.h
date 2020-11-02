//
// Created by vinicius on 02/11/2020.
//

#ifndef CPP_WASM_PHYSICS_ATOM_H
#define CPP_WASM_PHYSICS_ATOM_H
#include "Vec2.h"

class Atom {
private:
    Vec2 pos, vel;
    float mass, radius;
    Atom(Vec2 pos, Vec2 vel, float radius=1.0, float mass=1.0) :
    pos(pos), vel(vel), radius(radius), mass(mass)
    {
    }
    void update(float dt);
    /* TODO: integrate C++ and javascript */
};




#endif //CPP_WASM_PHYSICS_ATOM_H
