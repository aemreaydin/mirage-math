#pragma once

#include "vec.hpp"

namespace Mirage::Math {

class Point3 : public Vec3
{
public:
  Point3() = default;
  Point3( float x, float y, float z ) : Vec3( x, y, z ) {}
};

} // namespace Mirage::Math
