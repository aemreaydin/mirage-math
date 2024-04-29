#pragma once
#include "mirage_math/constants.hpp"
#include "mirage_math/mat.hpp"

template<typename T, size_t N>
static bool areMatricesEqual(
  const Mirage::Math::Mat<T, N, N>& mat1, const Mirage::Math::Mat<T, N, N>& mat2, float tol = Mirage::Math::EPSILON )
{
  for ( auto i = 0; i != N; ++i )
  {
    for ( auto j = 0; j != N; ++j )
    {
      if ( std::fabs( mat1[i][j] - mat2[i][j] ) > tol )
      {
        return false;
      }
    }
  }
  return true;
}

template<typename T, size_t N>
static bool areVectorsEqual(
  const Mirage::Math::Vec<T, N>& vec1, const Mirage::Math::Vec<T, N>& vec2, float tol = Mirage::Math::EPSILON )
{
  for ( auto i = 0; i != N; ++i )
  {
    if ( std::fabs( vec1[i] - vec2[i] ) > tol )
    {
      return false;
    }
  }
  return true;
}
