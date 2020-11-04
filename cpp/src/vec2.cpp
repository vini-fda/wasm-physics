//
// Created by vinicius on 02/11/2020.
//

#include "vec2.h"
#include <limits>
#include <cmath>
#include <cstring>
#include <cstdint>

int32_t ulpsDistance(float a, float b);
bool nearlyEqual(float a, float b,
                 float fixedEpsilon, int ulpsEpsilon);

vec2& vec2::operator=(const vec2 &rv) {
    if(this != &rv) {
        this->x = rv.x;
        this->y = rv.y;
    }
    return *this;
}

vec2 &vec2::operator+=(const vec2 &rv) {
    this->x += rv.x;
    this->y += rv.y;
    return *this;
}

vec2 &vec2::operator-=(const vec2 &rv) {
    this->x -= rv.x;
    this->y -= rv.y;
    return *this;
}

vec2 &vec2::operator*=(const float &alpha) {
    this->x *= alpha;
    this->y *= alpha;
    return *this;
}

vec2 &vec2::operator/=(const float &alpha) {
    this->x /= alpha;
    this->y /= alpha;
    return *this;
}

vec2 operator+(vec2 lv, const vec2 &rv) {
    return (lv += rv);
}

vec2 operator-(vec2 lv, const vec2 &rv) {
    return (lv -= rv);
}

//Performs outer product in canonical basis
float operator^(const vec2& lv, const vec2 &rv) {
    return (lv.x * rv.y - lv.y * rv.x);
}

float operator*(const vec2 &lv, const vec2 &rv) {
    return lv.x*rv.x + lv.y*rv.y;
}

bool vec2::operator==(const vec2 &rv) const {
    return (x == rv.x) && (y == rv.y);
}

bool near(const vec2 &lv, const vec2 &rv) {
    /* Tests if two vectors are close to one another */
    /* TODO: EXPLAIN THEORY */
    /* TODO: IMPROVE THIS */
    //https://floating-point-gui.de/errors/comparison/
    //https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html
    if(lv == rv)
        return true; //shortcut
    else {
        constexpr float e = std::numeric_limits<float>::epsilon();
        //ULP: units of least precision
        constexpr int ulp_threshold = 10;
        return nearlyEqual(norm2(lv), norm2(rv), e, ulp_threshold);
    }
}

float norm2(const vec2 &v) {
    /* Square of the norm of v */
    return v*v;
}

vec2 operator*(vec2 lv, float alpha) {
    return (lv *= alpha);
}

vec2 operator*(float alpha, vec2 rv) {
    return (rv *= alpha);
}

/* Projects vector lv into vector rv's span */
vec2 proj(const vec2& lv, const vec2 &rv) {
    return (lv*rv)/(rv*rv) * rv;
}

float norm(const vec2 &v) {
    return sqrtf(norm2(v));
}

float dist2(const vec2 &lv, const vec2 &rv) {
    return norm2(lv - rv);
}

float dist(const vec2 &lv, const vec2 &rv) {
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









