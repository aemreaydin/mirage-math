#pragma once

#include "point.hpp"
#include "vec.hpp"

namespace Mirage::Math {

class Line
{
  Point3 m_point;
  Vec3   m_line;

public:
  Line() = default;
  Line( const Point3& point, const Vec3& line ) : m_point( point ), m_line( line ) {}

  [[nodiscard]] inline const Vec3&   line() const { return m_line; }
  [[nodiscard]] inline const Point3& point() const { return m_point; }
};

inline float distance( const Vec3& point, const Line& line )
{
  Vec3 cross_vec = cross( point - line.point(), line.line() );
  return std::sqrt( dot( cross_vec, cross_vec ) / dot( line.line(), line.line() ) );
}

inline float distance( const Line& line_a, const Line& line_b )
{
  Vec3 ab = line_b.point() - line_a.point();

  float v11 = dot( line_a.line(), line_a.line() );
  float v22 = dot( line_b.line(), line_b.line() );
  float v12 = dot( line_a.line(), line_b.line() );

  float det = ( v12 * v12 - v11 * v22 );
  if ( std::fabs( det ) > std::numeric_limits<float>::min() )
  {
    det = 1.0F / det;

    float dot_v1ab = dot( line_a.line(), ab );
    float dot_v2ab = dot( line_b.line(), ab );

    float t1 = ( v12 * dot_v2ab - v22 * dot_v1ab ) * det;
    float t2 = ( v11 * dot_v2ab - v12 * dot_v1ab ) * det;

    return magnitude( ( line_b.point() + t2 * line_b.line() ) - ( line_a.point() + t1 * line_a.line() ) );
  }

  // Lines are parallel, so just calculate the distance between line_a and point_b
  return distance( line_b.point(), line_a );
}

} // namespace Mirage::Math
