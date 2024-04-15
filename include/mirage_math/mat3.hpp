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

  Mat3& operator*=(float mul)
  {
    (*this)[0] * mul;
    (*this)[1] * mul;
    (*this)[2] * mul;
    return *this;
  }

  Mat3& operator/=(float div)
  {
    assert(div != 0.0F && "Can't divide by 0");
    div = 1.0F / div;
    (*this)[0] * div;
    (*this)[1] * div;
    (*this)[2] * div;
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const Mat3& m)
  {
    os << std::fixed;
    os.precision(2);
    for (int i = 0; i < 3; ++i) {
      os << "| ";
      for (int j = 0; j < 3; ++j) {
        os << m.mat[i][j];
        if (j != 2) {
          os << ", ";
        }
      }
      os << " |\n";
    }
    return os;
  }
};

inline Mat3 operator+(const Mat3& a, const Mat3& b) { return Mat3{ a[0] + b[0], a[1] + b[1], a[2] + b[2] }; }

inline Mat3 operator-(const Mat3& a, const Mat3& b) { return Mat3{ a[0] - b[0], a[1] - b[1], a[2] - b[2] }; }

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

inline Mat3 operator*(const Mat3& a, float mul) { return Mat3{ a[0] * mul, a[1] * mul, a[2] * mul }; }

inline Mat3 operator/(const Mat3& a, float div)
{
  assert(div != 0.0F && "Can't divide by 0");
  div = 1 / div;
  return a * div;
}

inline float determinant(const Mat3& mat)
{
  return mat(0, 0) * (mat(1, 1) * mat(2, 2) - mat(2, 1) * mat(1, 2))
         - mat(0, 1) * (mat(1, 0) * mat(2, 2) - mat(1, 2) * mat(2, 0))
         + mat(0, 2) * (mat(1, 0) * mat(2, 1) - mat(1, 1) * mat(2, 0));
}

inline Mat3 inverse(const Mat3& mat)
{
  const auto& a = mat[0];
  const auto& b = mat[1];
  const auto& c = mat[2];

  const auto b_cross_c = cross(b, c);
  const auto c_cross_a = cross(c, a);
  const auto a_cross_b = cross(a, b);

  const auto scalar_cross = dot(a_cross_b, c);

  return Mat3{ b_cross_c, c_cross_a, a_cross_b } / scalar_cross;
}

}// namespace MirageMath
