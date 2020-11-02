//
// Created by vinicius on 02/11/2020.
//

#ifndef CPP_WASM_PHYSICS_VEC2_H
#define CPP_WASM_PHYSICS_VEC2_H


class Vec2 {
private:
    float x, y;
public:
    Vec2(float x, float y);
    //Assignment
    Vec2& operator=(const Vec2& rv);
    //Arithmetic operators(compound assignment)
    Vec2& operator+=(const Vec2& rv);
    Vec2& operator-=(const Vec2& rv);
    Vec2& operator*=(const float& alpha);
    Vec2& operator/=(const float& alpha);

    //Arithmetic operators(binary)
    friend Vec2 operator+(Vec2 lv, const Vec2& rv);
    friend Vec2 operator-(Vec2 lv, const Vec2& rv);
    //Outer product ^
    friend float operator^(const Vec2& lv, const Vec2& rv);
    //Inner product %
    friend float operator*(const Vec2& lv, const Vec2& rv);
    //Comparison
    bool operator == (const Vec2& rv) const;
    friend bool near(const Vec2& lv, const Vec2& rv);
    //Norm & distance
    friend float norm2(const Vec2& v);
    friend float norm(const Vec2& v);
    friend float dist2(const Vec2& lv, const Vec2& rv);
    friend float dist(const Vec2& lv, const Vec2& rv);

    //Mult by scalar(left and right)
    friend Vec2 operator*(Vec2 lv, float alpha);
    friend Vec2 operator*(float alpha, Vec2 rv);
    //Projection
    friend Vec2 proj(const Vec2& lv, const Vec2& rv);
};


#endif //CPP_WASM_PHYSICS_VEC2_H
