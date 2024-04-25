#pragma once

#include "mat.hpp"

namespace Mirage::Math {

struct Mat4 : public Mat<float, 4, 4>
{
  Mat4() = default;

  Mat4( float t00,
    float     t01,
    float     t02,
    float     t03,
    float     t10,
    float     t11,
    float     t12,
    float     t13,
    float     t20,
    float     t21,
    float     t22,
    float     t23,
    float     t30,
    float     t31,
    float     t32,
    float     t33 )
  {
    ( *this )( 0, 0 ) = t00;
    ( *this )( 0, 1 ) = t10;
    ( *this )( 0, 2 ) = t20;
    ( *this )( 0, 3 ) = t30;
    ( *this )( 1, 0 ) = t01;
    ( *this )( 1, 1 ) = t11;
    ( *this )( 1, 2 ) = t21;
    ( *this )( 1, 3 ) = t31;
    ( *this )( 2, 0 ) = t02;
    ( *this )( 2, 1 ) = t12;
    ( *this )( 2, 2 ) = t22;
    ( *this )( 2, 3 ) = t32;
    ( *this )( 3, 0 ) = t03;
    ( *this )( 3, 1 ) = t13;
    ( *this )( 3, 2 ) = t23;
    ( *this )( 3, 3 ) = t33;
  }

  Mat4( const Vec4& v00, const Vec4& v01, const Vec4& v02, const Vec4& v03 )
  {
    ( *this )[0] = v00;
    ( *this )[1] = v01;
    ( *this )[2] = v02;
    ( *this )[3] = v03;
  }

  Mat4( const Mat& other ) : Mat( other ) {}

  // TODO
  // template<typename... Args>
  //   requires MatConstructorT<float, 4, 4, Args...>
  // explicit Mat4( Args... args ) : Mat{ args... }
  // {}

  // TODO
  // template<typename... Args>
  //   requires MatConstructorVec<float, 4, Args...>
  // explicit Mat4( Args... args ) : Mat{ args... }
  // {}
};

} // namespace Mirage::Math
