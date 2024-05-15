#pragma once

#include "mirage_math/line.hpp"
#include "point.hpp"
#include "transform.hpp"
#include "vec.hpp"

namespace Mirage::Math {

class Plane : public Vec4
{
public:
  using Vec4::Vec4;

  [[nodiscard]] inline const Vec3& getNormal() const { return toSubVec<3>(); }

  inline void normalizeInPlace()
  {
    float mag = magnitude( getNormal() );
    *this /= mag;
  }
};

inline float dot( const Plane& plane, const Point3& point )
{
  return plane.x() * point.x() + plane.y() * point.y() + plane.z() * point.z() + plane.w();
}

inline float dot( const Plane& plane, const Vec3& point )
{
  return plane.x() * point.x() + plane.y() * point.y() + plane.z() * point.z();
}

Plane operator*( const Plane& plane, const Transform4& transform )
{
  return Plane{
    plane.x() * transform( 0, 0 ) + plane.y() * transform( 1, 0 ) + plane.z() * transform( 2, 0 ),
    plane.x() * transform( 0, 1 ) + plane.y() * transform( 1, 1 ) + plane.z() * transform( 2, 1 ),
    plane.x() * transform( 0, 2 ) + plane.y() * transform( 1, 2 ) + plane.z() * transform( 2, 2 ),
    plane.x() * transform( 0, 3 ) + plane.y() * transform( 1, 3 ) + plane.z() * transform( 2, 3 ) + plane.w(),
  };
}

inline Transform4 makeReflection( const Plane& plane )
{
  float nx_sq = -2.0F * plane.x() * plane.x();
  float ny_sq = -2.0F * plane.y() * plane.y();
  float nz_sq = -2.0F * plane.z() * plane.z();
  float nx_ny = -2.0F * plane.x() * plane.y();
  float nx_nz = -2.0F * plane.x() * plane.z();
  float ny_nz = -2.0F * plane.y() * plane.z();
  float nx_d  = -2.0F * plane.x() * plane.w();
  float ny_d  = -2.0F * plane.y() * plane.w();
  float nz_d  = -2.0F * plane.z() * plane.w();

  return Transform4{
    1.0F + nx_sq,
    nx_ny,
    nx_nz,
    nx_d,
    nx_ny,
    1.0F + ny_sq,
    ny_nz,
    ny_d,
    nx_nz,
    ny_nz,
    1.0F + nz_sq,
    nz_d,
  };
}

inline std::optional<Point3> getIntersection( const Plane& plane, const Line& line )
{
  float fp = dot( plane, line.point() );
  float fv = dot( plane, line.line() );
  return std::fabs( fv ) > FLOAT_MIN ? std::optional{ line.point() - ( fp / fv ) * line.line() } : std::nullopt;
}

} // namespace Mirage::Math
