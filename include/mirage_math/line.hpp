#pragma once

#include "vec.hpp"

namespace Mirage::Math {

class Line
{
  Vec3 m_point{};
  Vec3 m_line{};

public:
  Line() = default;
  Line( const Vec3& point, const Vec3& line ) : m_point( point ), m_line( line ) {}

  [[nodiscard]] inline const Vec3& line() const { return m_line; }
  [[nodiscard]] inline const Vec3& point() const { return m_point; }
};

float distance( const Vec3& point, const Line& line )
{
  Vec3 cross_vec = cross( point - line.point(), line.line() );
  return std::sqrt( dot( cross_vec, cross_vec ) / dot( line.line(), line.line() ) );
}

} // namespace Mirage::Math
