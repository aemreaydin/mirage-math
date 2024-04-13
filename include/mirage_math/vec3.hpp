#pragma once

#include <cassert>
#include <cmath>
#include <ostream>

namespace MirageMath {

struct Vec3
{
  float x{};
  float y{};
  float z{};

  Vec3() = default;
  Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

  float& operator[](int ind)
  {
    assert(ind <= 2 && "Index > 2");
    return (&x)[ind];
  }

  const float& operator[](int ind) const
  {
    assert(ind <= 2 && "Index > 2");
    return (&x)[ind];
  }

  Vec3& operator+=(float add)
  {
    x += add;
    y += add;
    z += add;
    return *this;
  }

  Vec3& operator-=(float sub)
  {
    x -= sub;
    y -= sub;
    z -= sub;
    return *this;
  }

  Vec3& operator*=(float mul)
  {
    x *= mul;
    y *= mul;
    z *= mul;
    return *this;
  }

  Vec3& operator/=(float div)
  {
    assert(div != 0.0F && "Can't divide by 0");
    div = 1.0F / div;
    x *= div;
    y *= div;
    z *= div;
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const Vec3& v)
  {
    return os << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ')';
  }
};

inline Vec3 operator+(const Vec3& left, const Vec3& right)
{
  return { left.x + right.x, left.y + right.y, left.z + right.z };
}

inline Vec3 operator-(const Vec3& left, const Vec3& right)
{
  return { left.x - right.x, left.y - right.y, left.z - right.z };
}

inline Vec3 operator*(const Vec3& vec, float mul) { return { vec.x * mul, vec.y * mul, vec.z * mul }; }

inline Vec3 operator/(const Vec3& vec, float div)
{
  assert(div != 0.0F && "Can't divide by 0");
  div = 1.0F / div;
  return { vec.x * div, vec.y * div, vec.z * div };
}

inline Vec3 operator-(const Vec3& vec) { return { -vec.x, -vec.y, -vec.z }; }

inline float magnitude(const Vec3& vec) { return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z); }

inline Vec3 normalize(const Vec3& vec) { return vec / magnitude(vec); }

inline float dot(const Vec3& a, const Vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

inline Vec3 cross { return Vec3{ a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }

}// namespace MirageMath
