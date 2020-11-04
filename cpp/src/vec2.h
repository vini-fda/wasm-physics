//
// Created by vinicius on 02/11/2020.
//

#ifndef CPP_WASM_PHYSICS_VEC2_H
#define CPP_WASM_PHYSICS_VEC2_H


class vec2 {
public:
    float x, y;
public:
    vec2() : x(0.0), y(0.0) {};
    vec2(const vec2& v) {
      x = v.x;
      y = v.y;
    };
    vec2(float x, float y) : x(x), y(y) {};
    //Assignment
    vec2& operator=(vec2 const& rv);
    //Arithmetic operators(compound assignment)
    vec2& operator+=(const vec2& rv);
    vec2& operator-=(const vec2& rv);
    vec2& operator*=(const float& alpha);
    vec2& operator/=(const float& alpha);

    //Arithmetic operators(binary)
    friend vec2 operator+(vec2 lv, const vec2& rv);
    friend vec2 operator-(vec2 lv, const vec2& rv);
    //Outer product ^
    friend float operator^(const vec2& lv, const vec2& rv);
    //Inner product %
    friend float operator*(const vec2& lv, const vec2& rv);
    //Comparison
    bool operator == (const vec2& rv) const;
    friend bool near(const vec2& lv, const vec2& rv);
    //Norm & distance
    friend float norm2(const vec2& v);
    friend float norm(const vec2& v);
    friend float dist2(const vec2& lv, const vec2& rv);
    friend float dist(const vec2& lv, const vec2& rv);

    //Mult by scalar(left and right)
    friend vec2 operator*(vec2 lv, float alpha);
    friend vec2 operator*(float alpha, vec2 rv);
    //Projection
    friend vec2 proj(const vec2& lv, const vec2& rv);
    //Normalize
    vec2& normalize();
};


#endif //CPP_WASM_PHYSICS_VEC2_H
