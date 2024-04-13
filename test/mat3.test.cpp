#include "mirage_math/mat3.hpp"
#include "gtest/gtest.h"

using MirageMath::Mat3;
using MirageMath::Vec3;

class Mat3Test : public ::testing::Test
{
};

TEST_F(Mat3Test, HandlesElementInitialization)
{
  Mat3 matrix{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F };
  EXPECT_FLOAT_EQ(matrix(0, 0), 1.0F);
  EXPECT_FLOAT_EQ(matrix(1, 0), 2.0F);
  EXPECT_FLOAT_EQ(matrix(2, 0), 3.0F);
  EXPECT_FLOAT_EQ(matrix(0, 1), 4.0F);
  EXPECT_FLOAT_EQ(matrix(1, 1), 5.0F);
  EXPECT_FLOAT_EQ(matrix(2, 1), 6.0F);
  EXPECT_FLOAT_EQ(matrix(0, 2), 7.0F);
  EXPECT_FLOAT_EQ(matrix(1, 2), 8.0F);
  EXPECT_FLOAT_EQ(matrix(2, 2), 9.0F);
}

TEST_F(Mat3Test, HandlesVectorInitialization)
{
  Vec3 v1{ 1.0F, 4.0F, 7.0F };
  Vec3 v2{ 2.0F, 5.0F, 8.0F };
  Vec3 v3{ 3.0F, 6.0F, 9.0F };
  Mat3 matrix{ v1, v2, v3 };
  EXPECT_FLOAT_EQ(matrix(0, 0), 1.0F);
  EXPECT_FLOAT_EQ(matrix(0, 1), 4.0F);
  EXPECT_FLOAT_EQ(matrix(0, 2), 7.0F);
  EXPECT_FLOAT_EQ(matrix(1, 0), 2.0F);
  EXPECT_FLOAT_EQ(matrix(1, 1), 5.0F);
  EXPECT_FLOAT_EQ(matrix(1, 2), 8.0F);
  EXPECT_FLOAT_EQ(matrix(2, 0), 3.0F);
  EXPECT_FLOAT_EQ(matrix(2, 1), 6.0F);
  EXPECT_FLOAT_EQ(matrix(2, 2), 9.0F);
}

TEST_F(Mat3Test, HandlesIndexOperator)
{
  Mat3  matrix{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F };
  Vec3& row = matrix[1];
  EXPECT_FLOAT_EQ(row.x, 2.0F);
  EXPECT_FLOAT_EQ(row.y, 5.0F);
  EXPECT_FLOAT_EQ(row.z, 8.0F);

  row.x = 10.0F;
  EXPECT_FLOAT_EQ(matrix(1, 0), 10.0F);
}
