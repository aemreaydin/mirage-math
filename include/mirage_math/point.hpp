#pragma once

#include "vec.hpp"

namespace Mirage::Math {

class Point3 : public Vec3
{
public:
  Point3() = default;
  Point3( float x, float y, float z ) : Vec3( x, y, z ) {}
  Point3( const Vec3& vec ) : Vec3( vec ) {};
};

inline Point3 operator+( const Point3& point, const Vec3& vec )
{
  return Point3{ point.x() + vec.x(), point.y() + vec.y(), point.z() + vec.z() };
}

inline Point3 operator-( const Point3& point, const Vec3& vec )
{
  return Point3{ point.x() - vec.x(), point.y() - vec.y(), point.z() - vec.z() };
}

inline Vec3 operator-( const Point3& a, const Point3& b )
{
  return Vec3{ a.x() - b.x(), a.y() - b.y(), a.z() - b.z() };
}

} // namespace Mirage::Math
