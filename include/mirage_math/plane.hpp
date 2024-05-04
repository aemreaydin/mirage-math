#pragma once

#include "mirage_math/point.hpp"
#include "mirage_math/vec.hpp"

namespace Mirage::Math {

class Plane : public Vec4
{
  using Vec4::Vec4;

public:
  [[nodiscard]] inline const Vec3& getNormal() const { return toSubVec<3>(); }
};

float dot( const Plane& plane, const Point3& point )
{
  return plane.x() * point.x() + plane.y() * point.y() + plane.z() * point.z() + plane.w();
}

float dot( const Plane& plane, const Vec3& point )
{
  return plane.x() * point.x() + plane.y() * point.y() + plane.z() * point.z();
}

} // namespace Mirage::Math
