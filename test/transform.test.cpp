#include "mirage_math/transform.hpp"
#include "test_utils.hpp"
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

using namespace Mirage::Math;

class Transform4Test : public ::testing::Test
{
protected:
  Transform4 translation{
    Vec3{},
    Vec3{},
    Vec3{},
    Point3{ 1.0F, 2.0F, 3.0F }
  };
};

TEST_F( Transform4Test, IndexOperators )
{
  Transform4 index_mat = {
    Vec3{7.0F, 3.0F, 1.0F},
    Vec3{9.0F, 4.0F, 2.0F},
    Vec3{8.0F, 1.0F, 7.0F},
    Point3{2.0F, 7.0F, 5.0F}
  };

  EXPECT_FLOAT_EQ( index_mat( 1, 3 ), 7.0F );
  EXPECT_FLOAT_EQ( index_mat( 2, 3 ), 5.0F );
  EXPECT_FLOAT_EQ( index_mat( 3, 3 ), 1.0F );
  EXPECT_FLOAT_EQ( index_mat( 0, 2 ), 8.0F );
  EXPECT_FLOAT_EQ( index_mat( 3, 1 ), 0.0F );
  EXPECT_FLOAT_EQ( index_mat( 1, 1 ), 4.0F );
  EXPECT_FLOAT_EQ( index_mat( 0, 1 ), 9.0F );
  EXPECT_FLOAT_EQ( index_mat( 2, 1 ), 2.0F );

  Vec3 index_vec3 = index_mat[1];
  EXPECT_FLOAT_EQ( index_vec3[0], 9.0F );
  EXPECT_FLOAT_EQ( index_vec3[1], 4.0F );
  EXPECT_FLOAT_EQ( index_vec3[2], 2.0F );
}

TEST_F( Transform4Test, Translation )
{
  Point3 point = translation.getTranslation();
  EXPECT_FLOAT_EQ( point.x(), 1.0F );
  EXPECT_FLOAT_EQ( point.y(), 2.0F );
  EXPECT_FLOAT_EQ( point.z(), 3.0F );

  translation.setTranslation( Point3{ 4.0F, 5.0F, 6.0F } );
  point = translation.getTranslation();
  EXPECT_FLOAT_EQ( point.x(), 4.0F );
  EXPECT_FLOAT_EQ( point.y(), 5.0F );
  EXPECT_FLOAT_EQ( point.z(), 6.0F );
}

TEST_F( Transform4Test, Inverse )
{
  Transform4 mat{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F, 11.0F, 12.0F };
  Transform4 inv = inverse( mat );

  areMatricesEqual( inv, Transform4::identity() );
}

TEST_F( Transform4Test, PointVsVector )
{
  Vec3   vec{ 1.0F, 2.0F, 3.0F };
  Point3 point{ 1.0F, 1.0F, 1.0F };

  Point3     translate{ 1.0F, 2.0F, 3.0F };
  Transform4 translation_mat{ Transform4::identity() };
  translation_mat.setTranslation( translate );

  Vec3   vec_translated   = translation_mat * vec;
  Point3 point_translated = translation_mat * point;

  EXPECT_FLOAT_EQ( vec.x(), vec_translated.x() );
  EXPECT_FLOAT_EQ( vec.y(), vec_translated.y() );
  EXPECT_FLOAT_EQ( vec.z(), vec_translated.z() );

  EXPECT_FLOAT_EQ( point.x() + translate.x(), point_translated.x() );
  EXPECT_FLOAT_EQ( point.y() + translate.y(), point_translated.y() );
  EXPECT_FLOAT_EQ( point.z() + translate.z(), point_translated.z() );
}
