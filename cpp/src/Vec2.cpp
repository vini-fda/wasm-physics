//
// Created by vinicius on 02/11/2020.
//

#include "Vec2.h"
#include <limits>
#include <cmath>
#include <cstring>

int32_t ulpsDistance(float a, float b);
bool nearlyEqual(float a, float b,
                 float fixedEpsilon, int ulpsEpsilon);

Vec2::Vec2(float x, float y) {
    this->x = x; this->y = y;
}

Vec2& Vec2::operator=(const Vec2 &rv) {
    if(this != &rv) {
        this->x = rv.x;
        this->y = rv.y;
    }
    return *this;
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
    //https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html
    if(lv == rv)
        return true; //shortcut
    else {
        constexpr float e = std::numeric_limits<float>::epsilon();
        return nearlyEqual(norm2(lv), norm2(rv), e, 10);
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

int32_t ulpsDistance(const float a, const float b)
{
    /* source-code from https://bitbashing.io/comparing-floats.html */
    // Save work if the floats are equal.
    // Also handles +0 == -0
    if (a == b) return 0;

    const auto max =
            std::numeric_limits<int32_t>::max();

    // Max distance for NaN
    if (std::isnan(a) || std::isnan(b)) return max;

    // If one's infinite and they're not equal, max distance.
    if (std::isinf(a) || std::isinf(b)) return max;

    int32_t ia, ib;
    memcpy(&ia, &a, sizeof(float));
    memcpy(&ib, &b, sizeof(float));

    // Don't compare differently-signed floats.
    if ((ia < 0) != (ib < 0)) return max;

    // Return the absolute value of the distance in ULPs.
    int32_t distance = ia - ib;
    if (distance < 0) distance = -distance;
    return distance;
}

bool nearlyEqual(float a, float b,
                 float fixedEpsilon, int ulpsEpsilon)
{
    // Handle the near-zero case.
    const float difference = fabsf(a - b);
    if (difference <= fixedEpsilon) return true;

    return ulpsDistance(a, b) <= ulpsEpsilon;
}









