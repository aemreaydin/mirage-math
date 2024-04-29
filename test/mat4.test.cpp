#include "mirage_math/mat4.hpp"
#include "test_utils.hpp"
#include "gtest/gtest.h"
#include <gtest/gtest-death-test.h>

using namespace Mirage::Math;

class Mat4Test : public ::testing::Test
{
protected:
  Mat4 identity{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
  Mat4 scaling{ 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1 };
  Mat4 rotation;
  Mat4 translation{ 1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 3, 0, 0, 0, 1 };
  Mat4 non_invertible{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 };
  void SetUp() override
  {

    const float pi    = 3.14159265F;
    float       angle = pi / 2;
    rotation = Mat4{ cos( angle ), -sin( angle ), 0, 0, sin( angle ), cos( angle ), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
  }
};

TEST_F( Mat4Test, IndexOperators )
{
  Mat4 index_mat = {
    Vec4{1.0F, 2.0F, 3.0F, 4.0F},
    Vec4{6.0F, 7.0F, 8.0F, 9.0F},
    Vec4{5.0F, 5.0F, 5.0F, 5.0F},
    Vec4{0.0F, 0.0F, 0.0F, 0.0F}
  };
  ASSERT_FLOAT_EQ( index_mat( 1, 1 ), 7.0F );
  ASSERT_FLOAT_EQ( index_mat( 3, 3 ), 0.0F );
  ASSERT_FLOAT_EQ( index_mat( 2, 1 ), 8.0F );

  Vec4 index_vec4 = index_mat[1];
  ASSERT_FLOAT_EQ( index_vec4[0], 6.0F );
  ASSERT_FLOAT_EQ( index_vec4[1], 7.0F );
  ASSERT_FLOAT_EQ( index_vec4[2], 8.0F );
  ASSERT_FLOAT_EQ( index_vec4[3], 9.0F );
}

TEST_F( Mat4Test, InverseOfIdentity )
{
  auto inv = inverse( identity );
  areMatricesEqual( inv, identity );
}

TEST_F( Mat4Test, InverseOfScaling )
{
  auto inv = inverse( scaling );
  Mat4 expected_inverse{ 0.5, 0, 0, 0, 0, 0.333333F, 0, 0, 0, 0, 0.25, 0, 0, 0, 0, 1 };
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
  Mat4 expected_inverse{ 1, 0, 0, -1, 0, 1, 0, -2, 0, 0, 1, -3, 0, 0, 0, 1 };
  areMatricesEqual( inv, expected_inverse );
}
