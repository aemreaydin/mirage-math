#pragma once
#include "mat.hpp"

namespace Mirage::Math {

struct Mat3 : public Mat<float, 3, 3>
{
  Mat3() = default;

  Mat3( float n00, float n01, float n02, float n10, float n11, float n12, float n20, float n21, float n22 )
  {
    ( *this )( 0, 0 ) = n00;
    ( *this )( 0, 1 ) = n10;
    ( *this )( 0, 2 ) = n20;
    ( *this )( 1, 0 ) = n01;
    ( *this )( 1, 1 ) = n11;
    ( *this )( 1, 2 ) = n21;
    ( *this )( 2, 0 ) = n02;
    ( *this )( 2, 1 ) = n12;
    ( *this )( 2, 2 ) = n22;
  }

  Mat3( const Vec3& v00, const Vec3& v01, const Vec3& v02 )
  {
    ( *this )[0] = v00;
    ( *this )[1] = v01;
    ( *this )[2] = v02;
  }

  Mat3( const Mat& other ) : Mat( other ) {}
};

inline float determinant( const Mat3& mat )
{
  return mat( 0, 0 ) * ( mat( 1, 1 ) * mat( 2, 2 ) - mat( 2, 1 ) * mat( 1, 2 ) )
         - mat( 0, 1 ) * ( mat( 1, 0 ) * mat( 2, 2 ) - mat( 1, 2 ) * mat( 2, 0 ) )
         + mat( 0, 2 ) * ( mat( 1, 0 ) * mat( 2, 1 ) - mat( 1, 1 ) * mat( 2, 0 ) );
}

inline Mat3 inverse( const Mat3& mat )
{
  const auto& a = mat[0];
  const auto& b = mat[1];
  const auto& c = mat[2];

  const auto b_cross_c = cross( b, c );
  const auto c_cross_a = cross( c, a );
  const auto a_cross_b = cross( a, b );

  const auto scalar_cross = dot( a_cross_b, c );

  return Mat3{ b_cross_c, c_cross_a, a_cross_b } / scalar_cross;
}

inline Mat3 makeRotationX( float t )
{
  auto c = std::cos( t );
  auto s = std::sin( t );

  return Mat3{ 1.0F, 0.0F, 0.0F, 0.0F, c, -s, 0.0F, s, c };
}

inline Mat3 makeRotationY( float t )
{
  auto c = std::cos( t );
  auto s = std::sin( t );

  return Mat3{ c, 0.0F, s, 0.0F, 1.0F, 0.0F, -s, 0.0F, c };
}

inline Mat3 makeRotationZ( float t )
{
  auto c = std::cos( t );
  auto s = std::sin( t );

  return Mat3{ c, -s, 0.0F, s, c, 0.0F, 0.0F, 0.0F, 1.0F };
}

inline Mat3 makeRotation( float t, const Vec3& a )
{
  auto c           = std::cos( t );
  auto s           = std::sin( t );
  auto one_minus_c = 1.0F - c;

  auto x = a.x() * one_minus_c;
  auto y = a.y() * one_minus_c;
  auto z = a.z() * one_minus_c;

  auto axay = x * a.y();
  auto axaz = x * a.z();
  auto ayaz = y * a.z();

  return Mat3{ c + x * a.x(),
    axay - s * a.z(),
    axaz + s * a.y(),
    axay + s * a.z(),
    c + y * a.y(),
    ayaz - s * a.x(),
    axaz - s * a.y(),
    ayaz + s * a.x(),
    c + z * a.z() };
}

inline Mat3 makeReflection( const Vec3& a )
{
  auto x = -2.0F * a.x();
  auto y = -2.0F * a.y();
  auto z = -2.0F * a.z();

  auto axay = x * a.y();
  auto axaz = x * a.z();
  auto ayaz = y * a.z();

  return Mat3{ 1.0F + x * a.x(), axay, axaz, axay, 1.0F + y * a.y(), ayaz, axaz, ayaz, 1.0F + z * a.z() };
}

inline Mat3 makeInvolution( const Vec3& a ) { return -makeReflection( a ); }

inline Mat3 makeScale( float sx, float sy, float sz ) { return Mat3{ sx, 0.0F, 0.0F, 0.0F, sy, 0.0F, 0.0F, 0.0F, sz }; }

inline Mat3 makeScale( float s, const Vec3& a )
{
  s -= 1.0F;
  auto x = s * a.x();
  auto y = s * a.y();
  auto z = s * a.z();

  auto axay = x * a.y();
  auto axaz = x * a.z();
  auto ayaz = y * a.z();

  return Mat3{ x * a.x() + 1.0F, axay, axaz, axay, y * a.y() + 1.0F, ayaz, axaz, ayaz, z * a.z() + 1.0F };
}

inline Mat3 makeSkew( float t, const Vec3& skew_direction, const Vec3& projected )
{
  t      = std::tan( t );
  auto x = skew_direction.x() * t;
  auto y = skew_direction.y() * t;
  auto z = skew_direction.z() * t;

  return Mat3{ x * projected.x() + 1.0F,
    x * projected.y(),
    x * projected.z(),
    y * projected.x(),
    y * projected.y() + 1.0F,
    y * projected.z(),
    z * projected.x(),
    z * projected.y(),
    z * projected.z() + 1.0F };
}

} // namespace Mirage::Math
