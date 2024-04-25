#pragma once

#include "vec.hpp"
#include <array>
#include <cassert>
#include <cstddef>

namespace Mirage::Math {

template<typename T, size_t Row, size_t Col, typename... Ts>
concept MatConstructorT = (... && IsSame<T, Ts>)&&( ( sizeof...( Ts ) == Row * Col ) );

template<typename T, size_t Row, size_t Col, typename... Ts>
concept MatConstructorVec = (... && IsSame<Vec<T, Row>, Ts>)&&( ( sizeof...( Ts ) == Row ) );

template<typename T, size_t Row, size_t Col>
  requires Arithmetic<T>
class Mat
{
  std::array<std::array<T, Col>, Row> m_data{};

public:
  Mat() = default;

  inline T& operator()( size_t i, size_t j )
  {
    assert( i < Row && j < Col );
    return m_data[i][j];
  }

  const T& operator()( size_t i, size_t j ) const
  {
    assert( i < Row && j < Col );
    return m_data[i][j];
  }

  inline Vec<T, Col>& operator[]( const size_t i )
  {
    assert( i < Col );
    return *reinterpret_cast<Vec<T, Col>*>( m_data[i].data() );
  }

  inline const Vec<T, Col>& operator[]( size_t i ) const
  {
    assert( i < Col );
    return *reinterpret_cast<const Vec<T, Col>*>( m_data[i].data() );
  }

  inline Mat& operator+=( const Mat& other )
  {
    for ( auto i = 0; i != Row; ++i )
    {
      for ( auto j = 0; j != Col; ++j )
      {
        m_data[i][j] += other.m_data[i][j];
      }
    }
    return *this;
  }

  inline Mat& operator-=( const Mat& other )
  {
    for ( auto i = 0; i != Row; ++i )
    {
      for ( auto j = 0; j != Col; ++j )
      {
        m_data[i][j] -= other.m_data[i][j];
      }
    }
    return *this;
  }

  inline Mat operator-() const
  {
    Mat result;
    for ( auto i = 0; i != Row; ++i )
    {
      for ( auto j = 0; j != Col; ++j )
      {
        result[i][j] = -m_data[i][j];
      }
    }
    return result;
  }

  template<typename U>
    requires IsSame<T, U>
  inline Mat& operator*=( U mul )
  {
    for ( auto& row : m_data )
    {
      for ( auto& col : row )
      {
        col *= mul;
      }
    }
    return *this;
  }

  template<typename U>
    requires IsSame<T, U>
  inline Mat& operator/=( U div )
  {
    assert( div != 0.0F );
    for ( auto& row : m_data )
    {
      for ( auto& col : row )
      {
        col /= div;
      }
    }
    return *this;
  }
};

template<typename T, size_t N>
inline Mat<T, N, N> operator+( const Mat<T, N, N>& left, const Mat<T, N, N>& right )
{
  auto mat = left;
  mat += right;
  return mat;
}

template<typename T, size_t N>
inline Mat<T, N, N> operator-( const Mat<T, N, N>& left, const Mat<T, N, N>& right )
{
  auto mat = left;
  mat -= right;
  return mat;
}

template<typename T, size_t N>
inline Mat<T, N, N> operator*( const Mat<T, N, N>& left, const Mat<T, N, N>& right )
{
  Mat<T, N, N> mat{};
  for ( auto i = 0; i != N; ++i )
  {
    for ( auto j = 0; j != N; ++j )
    {
      for ( auto k = 0; k != N; ++k )
      {
        mat( i, j ) += left( i, k ) * right( k, j );
      }
    }
  }
  return mat;
}

template<typename T, size_t N>
inline Vec<T, N> operator*( const Mat<T, N, N>& mat, const Vec<T, N>& vec )
{
  Vec<T, N> result{};
  for ( auto i = 0; i != N; ++i )
  {
    for ( auto j = 0; j != N; ++j )
    {
      result[i] += mat( i, j ) * vec[j];
    }
  }
  return result;
}

template<typename T, size_t N>
inline Mat<T, N, N> operator*( const Mat<T, N, N>& a, float mul )
{
  auto mat = a;
  mat *= mul;
  return mat;
}

template<typename T, size_t N>
inline Mat<T, N, N> operator/( const Mat<T, N, N>& a, float div )
{
  auto mat = a;
  mat /= div;
  return mat;
}

template<typename T, size_t N>
inline Mat<T, N, N> transpose( const Mat<T, N, N>& mat )
{
  Mat<T, N, N> result{};
  for ( size_t i = 0; i < N; ++i )
  {
    for ( size_t j = 0; j < N; ++j )
    {
      result( j, i ) = mat( i, j );
    }
  }
  return result;
}

} // namespace Mirage::Math
