#pragma once

#include "constants.hpp"
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <format>
#include <string>
#include <type_traits>

namespace Mirage::Math {

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<typename T, typename U>
concept IsSame = std::is_same_v<T, U>;

template<typename T, size_t N, typename... Ts>
concept VecParams = (... && IsSame<T, Ts>)&&( ( sizeof...( Ts ) == N ) );

template<typename T, size_t N>
  requires Arithmetic<T>
class Vec
{
  std::array<T, N> m_data{};

public:
  Vec() = default;

  template<typename... Args>
    requires VecParams<T, N, Args...>
  inline constexpr explicit Vec( Args... args ) : m_data{ args... }
  {}

  template<size_t SubN = 3, typename U>
    requires( IsSame<T, U> )
  inline constexpr Vec( const Vec<T, SubN>& vec, U value ) : m_data{ vec.x(), vec.y(), vec.z(), value }
  {}

  inline T& operator[]( size_t i )
  {
    assert( i < N );
    return m_data[i];
  }
  inline const T& operator[]( size_t i ) const
  {
    assert( i < N );
    return m_data[i];
  }

  inline T& x() { return m_data[0]; }
  inline T& y() { return m_data[1]; }
  inline T& z()
    requires( N >= 3 )
  {
    return m_data[2];
  }
  inline T& w()
    requires( N >= 4 )
  {
    return m_data[3];
  }

  [[nodiscard]] inline const T& x() const { return m_data[0]; }
  [[nodiscard]] inline const T& y() const { return m_data[1]; }
  [[nodiscard]] inline const T& z() const
    requires( N >= 3 )
  {
    return m_data[2];
  }
  [[nodiscard]] inline const T& w() const
    requires( N >= 4 )
  {
    return m_data[3];
  }

  template<typename U>
  inline Vec& operator+=( U val )
    requires IsSame<T, U>
  {
    for ( auto& data : m_data )
    {
      data += val;
    }
    return *this;
  }

  template<typename U>
  inline Vec& operator-=( U val )
    requires IsSame<T, U>
  {
    for ( auto& data : m_data )
    {
      data -= val;
    }
    return *this;
  }

  template<typename U>
  inline Vec& operator*=( U val )
    requires IsSame<T, U>
  {
    for ( auto& data : m_data )
    {
      data *= val;
    }
    return *this;
  }

  template<typename U>
  inline Vec& operator/=( U val )
    requires IsSame<T, U>
  {
    assert( val != 0.0F );
    for ( auto& data : m_data )
    {
      data /= val;
    }
    return *this;
  }

  template<size_t U>
  inline Vec<T, U>& toSubVec()
    requires( U < N )
  {
    return *reinterpret_cast<Vec<T, U>*>( m_data.data() );
  }

  template<size_t U>
  const inline Vec<T, U>& toSubVec() const
    requires( U < N )
  {
    return *reinterpret_cast<const Vec<T, U>*>( m_data.data() );
  }

  inline void normalizeInPlace() { *this / magnitude( *this ); }

  explicit inline operator std::string() const
  {
    std::string result = "Vec" + std::to_string( N ) + "(";
    for ( size_t i = 0; i < N; i++ )
    {
      result += std::format( "{:.1f}", m_data[i] );
      if ( i < N - 1 )
      {
        result += ", ";
      }
    }
    result += ")";
    return result;
  }
};

template<typename T, size_t N>
inline Vec<T, N> operator+( const Vec<T, N>& left, const Vec<T, N>& right )
{
  Vec<T, N> vec{};
  for ( auto i = 0; i != N; ++i )
  {
    vec[i] = left[i] + right[i];
  }
  return vec;
}

template<typename T, size_t N>
inline Vec<T, N> operator-( const Vec<T, N>& left, const Vec<T, N>& right )
{
  Vec<T, N> vec{};
  for ( auto i = 0; i != N; ++i )
  {
    vec[i] = left[i] - right[i];
  }
  return vec;
}

template<typename T, size_t N>
inline Vec<T, N> operator-( const Vec<T, N>& left )
{
  Vec<T, N> vec{};
  for ( auto i = 0; i != N; ++i )
  {
    vec[i] = -left[i];
  }
  return vec;
}

template<typename T, size_t N>
inline Vec<T, N> operator*( const Vec<T, N>& left, T mul )
{
  Vec<T, N> vec{};
  for ( auto i = 0; i != N; ++i )
  {
    vec[i] = left[i] * mul;
  }
  return vec;
}

template<typename T, size_t N>
inline Vec<T, N> operator/( const Vec<T, N>& left, T div )
{
  assert( div != 0.0F );
  Vec<T, N> vec{};
  for ( auto i = 0; i != N; ++i )
  {
    vec[i] = left[i] / div;
  }
  return vec;
}

template<typename T, size_t N>
inline T magnitudeSquared( const Vec<T, N>& vec )
{
  T result{};
  for ( auto i = 0; i != N; ++i )
  {
    result += vec[i] * vec[i];
  }
  return result;
}

template<typename T, size_t N>
inline T magnitude( const Vec<T, N>& vec )
{
  return std::sqrt( magnitudeSquared( vec ) );
}

template<typename T, size_t N>
inline Vec<T, N> normalized( const Vec<T, N>& vec )
{
  return vec / magnitude( vec );
}

template<typename T, size_t N>
inline T dot( const Vec<T, N>& left, const Vec<T, N>& right )
{
  T result{};
  for ( auto i = 0; i != N; ++i )
  {
    result += left[i] * right[i];
  }
  return result;
}

template<typename T, size_t N>
inline Vec<T, N> cross( const Vec<T, N>& left, const Vec<T, N>& right )
  requires( N == 3 )
{
  return Vec<T, N>{ left[1] * right[2] - left[2] * right[1],
    left[2] * right[0] - left[0] * right[2],
    left[0] * right[1] - left[1] * right[0] };
}

template<typename T, size_t N>
inline Vec<T, N> project( const Vec<T, N>& source, const Vec<T, N>& target )
{
  return target * ( dot( source, target ) ) / dot( target, target );
}

template<typename T, size_t N>
inline Vec<T, N> reject( const Vec<T, N>& source, const Vec<T, N>& target )
{
  return source - project( source, target );
}

template<typename T, size_t N>
inline bool isUnitVector( const Vec<T, N>& vec, const T epsilon = EPSILON )
{
  return std::abs( dot( vec, vec ) - UNIT ) < epsilon;
}

using Vec2  = Vec<float, 2>;
using Vec3  = Vec<float, 3>;
using Vec4  = Vec<float, 4>;
using IVec3 = Vec<int, 3>;
using IVec4 = Vec<int, 4>;

} // namespace Mirage::Math
