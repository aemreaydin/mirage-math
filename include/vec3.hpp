#pragma once

#include <cassert>
#include <cmath>

struct Vec3 {
  float x{};
  float y{};
  float z{};

  Vec3() = default;
  Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

  float &operator[](int ind) {
    assert(ind <= 2 && "Index > 2");
    return (&x)[ind];
  }

  const float &operator[](int ind) const {
    assert(ind <= 2 && "Index > 2");
    return (&x)[ind];
  }

  Vec3 &operator+=(float add) {
    x += add;
    y += add;
    z += add;
    return *this;
  }

  Vec3 &operator-=(float sub) {
    x -= sub;
    y -= sub;
    z -= sub;
    return *this;
  }

  Vec3 &operator*=(float mul) {
    x *= mul;
    y *= mul;
    z *= mul;
    return *this;
  }

  Vec3 &operator/=(float div) {
    assert(div != 0.0F && "Can't divide by 0");
    div = 1.0f / div;
    x *= div;
    y *= div;
    z *= div;
    return *this;
  }
};

inline Vec3 operator+(const Vec3 &left, const Vec3 &right) {
  return {left.x + right.x, left.y + right.y, left.z + right.z};
}

inline Vec3 operator-(const Vec3 &left, const Vec3 &right) {
  return {left.x - right.x, left.y - right.y, left.z - right.z};
}

inline Vec3 operator*(const Vec3 &vec, float mul) {
  return {vec.x * mul, vec.y * mul, vec.z * mul};
}

inline Vec3 operator/(const Vec3 &vec, float div) {
  assert(div != 0.0F && "Can't divide by 0");
  div = 1.0F / div;
  return {vec.x * div, vec.y * div, vec.z * div};
}

inline Vec3 operator-(const Vec3 &vec) { return {-vec.x, -vec.y, -vec.z}; }

inline float Magnitude(const Vec3 &vec) {
  return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

inline Vec3 Normalize(const Vec3 &vec) { return vec / Magnitude(vec); }
