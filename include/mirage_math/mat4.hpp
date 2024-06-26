#pragma once

#include "mat.hpp"

namespace Mirage::Math {

class Mat4 : public Mat<float, 4, 4>
{
public:
  Mat4() = default;

  template<typename T>
    requires( IsSame<T, float> )
  Mat4( T t00, T t01, T t02, T t03, T t10, T t11, T t12, T t13, T t20, T t21, T t22, T t23, T t30, T t31, T t32, T t33 )
  {
    ( *this )( 0, 0 ) = t00;
    ( *this )( 1, 0 ) = t10;
    ( *this )( 2, 0 ) = t20;
    ( *this )( 3, 0 ) = t30;
    ( *this )( 0, 1 ) = t01;
    ( *this )( 1, 1 ) = t11;
    ( *this )( 2, 1 ) = t21;
    ( *this )( 3, 1 ) = t31;
    ( *this )( 0, 2 ) = t02;
    ( *this )( 1, 2 ) = t12;
    ( *this )( 2, 2 ) = t22;
    ( *this )( 3, 2 ) = t32;
    ( *this )( 0, 3 ) = t03;
    ( *this )( 1, 3 ) = t13;
    ( *this )( 2, 3 ) = t23;
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
};

inline Mat4 inverse( const Mat4& mat )
{
  const auto& a = reinterpret_cast<const Vec3&>( mat[0] );
  const auto& b = reinterpret_cast<const Vec3&>( mat[1] );
  const auto& c = reinterpret_cast<const Vec3&>( mat[2] );
  const auto& d = reinterpret_cast<const Vec3&>( mat[3] );

  const auto& x = mat( 3, 0 );
  const auto& y = mat( 3, 1 );
  const auto& z = mat( 3, 2 );
  const auto& w = mat( 3, 3 );

  auto s = cross( a, b );
  auto t = cross( c, d );
  auto u = a * y - b * x;
  auto v = c * w - d * z;

  const auto inv_det = 1.0F / ( dot( s, v ) + dot( t, u ) );
  s *= inv_det;
  t *= inv_det;
  u *= inv_det;
  v *= inv_det;

  const auto r0 = cross( b, v ) + t * y;
  const auto r1 = cross( v, a ) - t * x;
  const auto r2 = cross( d, u ) + s * w;
  const auto r3 = cross( u, c ) - s * z;

  return Mat4{ r0.x(),
    r0.y(),
    r0.z(),
    -dot( b, t ),
    r1.x(),
    r1.y(),
    r1.z(),
    dot( a, t ),
    r2.x(),
    r2.y(),
    r2.z(),
    -dot( d, s ),
    r3.x(),
    r3.y(),
    r3.z(),
    dot( c, s ) };
}

} // namespace Mirage::Math
