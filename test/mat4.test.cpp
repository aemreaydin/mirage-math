#include "mirage_math/mat4.hpp"
#include "test_utils.hpp"
#include "gtest/gtest.h"
#include <gtest/gtest-death-test.h>

using namespace Mirage::Math;

class Mat4Test : public ::testing::Test
{
protected:
  Mat4 identity{ 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F };
  Mat4 scaling{ 2.0F, 0.0F, 0.0F, 0.0F, 0.0F, 3.0F, 0.0F, 0.0F, 0.0F, 0.0F, 4.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F };
  Mat4 rotation;
  Mat4 translation{ 1.0F, 0.0F, 0.0F, 1.0F, 0.0F, 1.0F, 0.0F, 2.0F, 0.0F, 0.0F, 1.0F, 3.0F, 0.0F, 0.0F, 0.0F, 1.0F };
  Mat4 non_invertible{ 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F };
  void SetUp() override
  {

    const float pi    = 3.14159265F;
    float       angle = pi / 2;
    rotation          = Mat4{ cos( angle ),
      -sin( angle ),
      0.0F,
      0.0F,
      sin( angle ),
      cos( angle ),
      0.0F,
      0.0F,
      0.0F,
      0.0F,
      1.0F,
      0.0F,
      0.0F,
      0.0F,
      0.0F,
      1.0F };
  }
};

TEST_F( Mat4Test, IndexOperators )
{
  Mat4 mat_val = { 1.0F, 2.0F, 3.0F, 4.0F, 6.0F, 7.0F, 8.0F, 9.0F, 5.0F, 5.0F, 5.0F, 5.0F, 0.0F, 0.0F, 0.0F, 0.0F };
  EXPECT_FLOAT_EQ( mat_val( 0, 0 ), 1.0F );
  EXPECT_FLOAT_EQ( mat_val( 1, 0 ), 6.0F );
  EXPECT_FLOAT_EQ( mat_val( 2, 0 ), 5.0F );
  EXPECT_FLOAT_EQ( mat_val( 3, 0 ), 0.0F );
  EXPECT_FLOAT_EQ( mat_val( 0, 1 ), 2.0F );
  EXPECT_FLOAT_EQ( mat_val( 1, 1 ), 7.0F );
  EXPECT_FLOAT_EQ( mat_val( 2, 1 ), 5.0F );
  EXPECT_FLOAT_EQ( mat_val( 3, 1 ), 0.0F );
  EXPECT_FLOAT_EQ( mat_val( 0, 2 ), 3.0F );
  EXPECT_FLOAT_EQ( mat_val( 1, 2 ), 8.0F );
  EXPECT_FLOAT_EQ( mat_val( 2, 2 ), 5.0F );
  EXPECT_FLOAT_EQ( mat_val( 3, 2 ), 0.0F );
  EXPECT_FLOAT_EQ( mat_val( 0, 3 ), 4.0F );
  EXPECT_FLOAT_EQ( mat_val( 1, 3 ), 9.0F );
  EXPECT_FLOAT_EQ( mat_val( 2, 3 ), 5.0F );
  EXPECT_FLOAT_EQ( mat_val( 3, 3 ), 0.0F );

  Mat4 index_mat = {
    Vec4{1.0F, 2.0F, 3.0F, 4.0F},
    Vec4{6.0F, 7.0F, 8.0F, 9.0F},
    Vec4{5.0F, 5.0F, 5.0F, 5.0F},
    Vec4{0.0F, 0.0F, 0.0F, 0.0F}
  };
  EXPECT_FLOAT_EQ( index_mat( 0, 0 ), 1.0F );
  EXPECT_FLOAT_EQ( index_mat( 1, 0 ), 2.0F );
  EXPECT_FLOAT_EQ( index_mat( 2, 0 ), 3.0F );
  EXPECT_FLOAT_EQ( index_mat( 3, 0 ), 4.0F );
  EXPECT_FLOAT_EQ( index_mat( 0, 1 ), 6.0F );
  EXPECT_FLOAT_EQ( index_mat( 1, 1 ), 7.0F );
  EXPECT_FLOAT_EQ( index_mat( 2, 1 ), 8.0F );
  EXPECT_FLOAT_EQ( index_mat( 3, 1 ), 9.0F );
  EXPECT_FLOAT_EQ( index_mat( 0, 2 ), 5.0F );
  EXPECT_FLOAT_EQ( index_mat( 1, 2 ), 5.0F );
  EXPECT_FLOAT_EQ( index_mat( 2, 2 ), 5.0F );
  EXPECT_FLOAT_EQ( index_mat( 3, 2 ), 5.0F );
  EXPECT_FLOAT_EQ( index_mat( 0, 3 ), 0.0F );
  EXPECT_FLOAT_EQ( index_mat( 1, 3 ), 0.0F );
  EXPECT_FLOAT_EQ( index_mat( 2, 3 ), 0.0F );
  EXPECT_FLOAT_EQ( index_mat( 3, 3 ), 0.0F );

  Vec4 index_vec4 = index_mat[1];
  EXPECT_FLOAT_EQ( index_vec4[0], 6.0F );
  EXPECT_FLOAT_EQ( index_vec4[1], 7.0F );
  EXPECT_FLOAT_EQ( index_vec4[2], 8.0F );
  EXPECT_FLOAT_EQ( index_vec4[3], 9.0F );
}

TEST_F( Mat4Test, HandlesMatrixMultiplicationByMatrix )
{
  Mat4 test_mat1 = {
    Vec4{1.0F, 2.0F, 3.0F, 4.0F},
    Vec4{6.0F, 7.0F, 8.0F, 9.0F},
    Vec4{5.0F, 5.0F, 5.0F, 5.0F},
    Vec4{0.0F, 0.0F, 0.0F, 0.0F}
  };

  Mat4 test_mat2 = {
    Vec4{0.0F, 0.0F, 0.0F, 0.0F},
    Vec4{6.0F, 7.0F, 8.0F, 9.0F},
    Vec4{5.0F, 5.0F, 5.0F, 5.0F},
    Vec4{1.0F, 2.0F, 3.0F, 4.0F},
  };

  auto result = test_mat1 * test_mat2;
  EXPECT_FLOAT_EQ( result( 0, 0 ), 31 );
  EXPECT_FLOAT_EQ( result( 1, 0 ), 37 );
  EXPECT_FLOAT_EQ( result( 2, 0 ), 43 );
  EXPECT_FLOAT_EQ( result( 3, 0 ), 49 );
  EXPECT_FLOAT_EQ( result( 0, 1 ), 91 );
  EXPECT_FLOAT_EQ( result( 1, 1 ), 107 );
  EXPECT_FLOAT_EQ( result( 2, 1 ), 123 );
  EXPECT_FLOAT_EQ( result( 3, 1 ), 139 );
  EXPECT_FLOAT_EQ( result( 0, 2 ), 60 );
  EXPECT_FLOAT_EQ( result( 1, 2 ), 70 );
  EXPECT_FLOAT_EQ( result( 2, 2 ), 80 );
  EXPECT_FLOAT_EQ( result( 3, 2 ), 90 );
  EXPECT_FLOAT_EQ( result( 0, 3 ), 0 );
  EXPECT_FLOAT_EQ( result( 1, 3 ), 0 );
  EXPECT_FLOAT_EQ( result( 2, 3 ), 0 );
  EXPECT_FLOAT_EQ( result( 3, 3 ), 0 );
}

TEST_F( Mat4Test, HandlesMatrixMultiplicationByVector )
{
  Mat4 test_mat1 = {
    Vec4{1.0F, 2.0F, 3.0F, 4.0F},
    Vec4{6.0F, 7.0F, 8.0F, 9.0F},
    Vec4{5.0F, 5.0F, 5.0F, 5.0F},
    Vec4{0.0F, 0.0F, 0.0F, 0.0F}
  };
  Vec4 test_vec{ 1.0F, 2.0F, 3.0F, 4.0F };
  auto result = test_mat1 * test_vec;
  EXPECT_FLOAT_EQ( result[0], 30 );
  EXPECT_FLOAT_EQ( result[1], 80 );
  EXPECT_FLOAT_EQ( result[2], 50 );
  EXPECT_FLOAT_EQ( result[3], 0 );
}

TEST_F( Mat4Test, InverseOfIdentity )
{
  auto inv = inverse( identity );
  areMatricesEqual( inv, identity );
}

TEST_F( Mat4Test, InverseOfScaling )
{
  auto inv = inverse( scaling );
  Mat4 expected_inverse{ 0.5F, 0.F, 0.F, 0.F, 0.F, 0.333333F, 0.F, 0.F, 0.F, 0.F, 0.25F, 0.F, 0.F, 0.F, 0.F, 1.F };
  areMatricesEqual( inv, expected_inverse );
}

TEST_F( Mat4Test, InverseOfRotation )
{
  auto inv              = inverse( rotation );
  Mat4 expected_inverse = transpose( rotation );
  areMatricesEqual( inv, expected_inverse );
}

TEST_F( Mat4Test, InverseOfTranslation )
{
  auto inv = inverse( translation );
  Mat4 expected_inverse{ 1.F, 0.F, 0.F, -1.F, 0.F, 1.F, 0.F, -2.F, 0.F, 0.F, 1.F, -3.F, 0.F, 0.F, 0.F, 1.F };
  areMatricesEqual( inv, expected_inverse );
}
