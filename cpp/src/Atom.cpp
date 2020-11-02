//
// Created by vinicius on 02/11/2020.
//

#include "Atom.h"

void Atom::update(float dt) {
    this->pos += this->vel * dt;
}
