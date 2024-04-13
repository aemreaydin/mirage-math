#pragma once

#include "vec3.hpp"
#include <array>

namespace MirageMath {

struct Mat3
{
  std::array<std::array<float, 3>, 3> mat{};

  Mat3(float n00, float n01, float n02, float n10, float n11, float n12, float n20, float n21, float n22)
  {
    mat[0][0] = n00;
    mat[0][1] = n10;
    mat[0][2] = n20;
    mat[1][0] = n01;
    mat[1][1] = n11;
    mat[1][2] = n21;
    mat[2][0] = n02;
    mat[2][1] = n12;
    mat[2][2] = n22;
  }

  Mat3(const Vec3& a, const Vec3& b, const Vec3& c)
  {
    mat[0][0] = a.x;
    mat[0][1] = a.y;
    mat[0][2] = a.z;
    mat[1][0] = b.x;
    mat[1][1] = b.y;
    mat[1][2] = b.z;
    mat[2][0] = c.x;
    mat[2][1] = c.y;
    mat[2][2] = c.z;
  }

  float& operator()(size_t i, size_t j)
  {
    assert(i <= 2 && j <= 2 && "At least one index > 2");
    return mat[i][j];
  }

  const float& operator()(size_t i, size_t j) const
  {
    assert(i <= 2 && j <= 2 && "At least one index > 2");
    return mat[i][j];
  }

  Vec3& operator[](size_t i)
  {
    assert(i <= 2 && "Index > 2");
    return *reinterpret_cast<Vec3*>(mat[i].data());
  }

  const Vec3& operator[](size_t i) const
  {
    assert(i <= 2 && "Index > 2");
    return *reinterpret_cast<const Vec3*>(mat[i].data());
  }
};

inline Mat3 operator*(const Mat3& a, const Mat3& b)
{
  return Mat3{ a.mat[0][0] * b.mat[0][0] + a.mat[0][1] * b.mat[1][0] + a.mat[0][2] * b.mat[2][0],
    a.mat[0][0] * b.mat[0][1] + a.mat[0][1] * b.mat[1][1] + a.mat[0][2] * b.mat[2][1],
    a.mat[0][0] * b.mat[0][2] + a.mat[0][1] * b.mat[1][2] + a.mat[0][2] * b.mat[2][2],
    a.mat[1][0] * b.mat[0][0] + a.mat[1][1] * b.mat[1][0] + a.mat[1][2] * b.mat[2][0],
    a.mat[1][0] * b.mat[0][1] + a.mat[1][1] * b.mat[1][1] + a.mat[1][2] * b.mat[2][1],
    a.mat[1][0] * b.mat[0][2] + a.mat[1][1] * b.mat[1][2] + a.mat[1][2] * b.mat[2][2],
    a.mat[2][0] * b.mat[0][0] + a.mat[2][1] * b.mat[1][0] + a.mat[2][2] * b.mat[2][0],
    a.mat[2][0] * b.mat[0][1] + a.mat[2][1] * b.mat[1][1] + a.mat[2][2] * b.mat[2][1],
    a.mat[2][0] * b.mat[0][2] + a.mat[2][1] * b.mat[1][2] + a.mat[2][2] * b.mat[2][2] };
};

inline Vec3 operator*(const Mat3& a, const Vec3& vec)
{
  return Vec3{ a.mat[0][0] * vec.x + a.mat[0][1] * vec.y + a.mat[0][2] * vec.z,
    a.mat[1][0] * vec.x + a.mat[1][1] * vec.y + a.mat[1][2] * vec.z,
    a.mat[2][0] * vec.x + a.mat[2][1] * vec.y + a.mat[2][2] * vec.z };
}

}// namespace MirageMath
