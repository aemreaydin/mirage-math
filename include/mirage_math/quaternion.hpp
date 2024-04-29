#pragma once

#include "mat3.hpp"
#include "vec.hpp"

namespace Mirage::Math {

class Quaternion : public Vec4
{
public:
  using Vec4::Vec;

  [[nodiscard]] inline const Vec3& getVector() const { return toSubVec<3>(); }
  [[nodiscard]] inline Mat3        getRotationMatrix()
  {
    float x2 = x() * x();
    float y2 = y() * y();
    float z2 = z() * z();
    float xy = x() * y();
    float xz = x() * z();
    float yz = y() * z();
    float wx = w() * x();
    float wy = w() * y();
    float wz = w() * z();

    return Mat3{ 1.0F - 2.0F * y2 - 2.0F * z2,
      2.0F * ( xy - wz ),
      2.0F * ( xz + wy ),
      2.0F * ( xy + wz ),
      1.0F - 2.0F * x2 - 2.0F * z2,
      2.0F * ( yz - wx ),
      2.0F * ( xz - wy ),
      2.0F * ( yz + wx ),
      1.0F - 2.0F * x2 - 2.0F * y2 };
  }

  inline void setRotationMatrix( const Mat3& rotation_mat );
};

Quaternion operator*( const Quaternion& q00, const Quaternion& q01 )
{
  return Quaternion{
    q00.x() * q01.w() + q00.y() * q01.z() - q00.z() * q01.y() + q00.w() * q01.x(),
    q00.y() * q01.w() + q00.z() * q01.x() + q00.w() * q01.y() - q00.x() * q01.z(),
    q00.z() * q01.w() + q00.w() * q01.z() + q00.x() * q01.y() - q00.y() * q01.x(),
    q00.w() * q01.w() - q00.x() * q01.x() - q00.y() * q01.y() - q00.z() * q01.z(),
  };
}

inline Vec3 transform( const Vec3& vec, const Quaternion& quat )
{
  const Vec3& b         = quat.getVector();
  const float c         = quat.w();
  const float b_squared = magnitudeSquared( b );

  return ( c * c - b_squared ) * vec + 2.0F * dot( vec, b ) * b + 2.0F * c * cross( b, vec );
}

} // namespace Mirage::Math
