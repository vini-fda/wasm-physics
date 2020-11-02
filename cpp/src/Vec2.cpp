//
// Created by vinicius on 02/11/2020.
//

#include "Vec2.h"
#include <limits>
#include <cmath>

Vec2::Vec2(float x, float y) {
    this->x = x; this->y = y;
}

Vec2& Vec2::operator=(const Vec2 &rv) {
    if(this != &rv) {
        this->x = rv.x;
        this->y = rv.y;
    }
}

Vec2 &Vec2::operator+=(const Vec2 &rv) {
    this->x += rv.x;
    this->y += rv.y;
    return *this;
}

Vec2 &Vec2::operator-=(const Vec2 &rv) {
    this->x -= rv.x;
    this->y -= rv.y;
    return *this;
}

Vec2 &Vec2::operator*=(const float &alpha) {
    this->x *= alpha;
    this->y *= alpha;
    return *this;
}

Vec2 &Vec2::operator/=(const float &alpha) {
    this->x /= alpha;
    this->y /= alpha;
    return *this;
}

Vec2 operator+(Vec2 lv, const Vec2 &rv) {
    return (lv += rv);
}

Vec2 operator-(Vec2 lv, const Vec2 &rv) {
    return (lv -= rv);
}

//Performs outer product in canonical basis
float operator^(const Vec2& lv, const Vec2 &rv) {
    return (lv.x * rv.y - lv.y * rv.x);
}

float operator*(const Vec2 &lv, const Vec2 &rv) {
    return lv.x*rv.x + lv.y*rv.y;
}

bool Vec2::operator==(const Vec2 &rv) const {
    return (x == rv.x) && (y == rv.y);
}

bool near(const Vec2 &lv, const Vec2 &rv) {
    /* Tests if two vectors are close to one another */
    /* TODO: EXPLAIN THEORY */
    /* TODO: IMPROVE THIS */
    //https://floating-point-gui.de/errors/comparison/
    //sigma_x ~= epsilon * max(lv.x, rv.x)
    //sigma_y ~= epsilon * max(lv.y, rv.y)
    if(lv == rv)
        return true; //shortcut
    else {
        constexpr float e = std::numeric_limits<float>::epsilon();
        return norm2(lv - rv) <= 2.0*e*e;
    }
}

float norm2(const Vec2 &v) {
    /* Square of the norm of v */
    return v*v;
}

Vec2 operator*(Vec2 lv, float alpha) {
    return (lv *= alpha);
}

Vec2 operator*(float alpha, Vec2 rv) {
    return (rv *= alpha);
}

/* Projects vector lv into vector rv's span */
Vec2 proj(const Vec2& lv, const Vec2 &rv) {
    return (lv*rv)/(rv*rv) * rv;
}

float norm(const Vec2 &v) {
    return sqrtf(norm2(v));
}

float dist2(const Vec2 &lv, const Vec2 &rv) {
    return norm2(lv - rv);
}

float dist(const Vec2 &lv, const Vec2 &rv) {
    return norm(lv - rv);
}







