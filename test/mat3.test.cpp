#include "mirage_math/mat3.hpp"
#include "gtest/gtest.h"

using Mirage::Math::Mat3;
using Mirage::Math::Vec3;

class Mat3Test : public ::testing::Test
{
protected:
  Mat3 testMat1{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F };
  Mat3 testMat2{ 9.0F, 8.0F, 7.0F, 6.0F, 5.0F, 4.0F, 3.0F, 2.0F, 1.0F };
  Vec3 testVec{ 1.0F, 2.0F, 3.0F };
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
  auto& row = matrix[1];
  EXPECT_FLOAT_EQ(row.x, 2.0F);
  EXPECT_FLOAT_EQ(row.y, 5.0F);
  EXPECT_FLOAT_EQ(row.z, 8.0F);

  row.x = 10.0F;
  EXPECT_FLOAT_EQ(matrix(1, 0), 10.0F);

  ASSERT_DEATH(matrix(3, 0), "At least one index > 2");
  ASSERT_DEATH(matrix(0, 3), "At least one index > 2");
  ASSERT_DEATH(matrix[3], "Index > 2");
}

TEST_F(Mat3Test, AdditionOperator)
{
  Mat3 result = testMat1 + testMat2;
  EXPECT_FLOAT_EQ(result(0, 0), 10.0F);
  EXPECT_FLOAT_EQ(result(1, 1), 10.0F);
  EXPECT_FLOAT_EQ(result(2, 2), 10.0F);
}

TEST_F(Mat3Test, SubtractionOperator)
{
  Mat3 result = testMat1 - testMat2;
  EXPECT_FLOAT_EQ(result(0, 0), -8.0F);
  EXPECT_FLOAT_EQ(result(1, 1), 0.0F);
  EXPECT_FLOAT_EQ(result(2, 2), 8.0F);
}

TEST_F(Mat3Test, ScalarMultiplicationOperator)
{
  Mat3 result = testMat1 * 2.0F;
  EXPECT_FLOAT_EQ(result(0, 0), 2.0F);
  EXPECT_FLOAT_EQ(result(1, 1), 10.0F);
  EXPECT_FLOAT_EQ(result(2, 2), 18.0F);
}

TEST_F(Mat3Test, ScalarDivisionOperator)
{
  Mat3 result = testMat1 / 2.0F;
  EXPECT_FLOAT_EQ(result(0, 0), 0.5F);
  EXPECT_FLOAT_EQ(result(1, 1), 2.5F);
  EXPECT_FLOAT_EQ(result(2, 2), 4.5F);

  ASSERT_DEATH(testMat1 / 0.0F, "Can't divide by 0");
}

TEST_F(Mat3Test, Determinant)
{
  Mat3 identity{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };
  EXPECT_FLOAT_EQ(determinant(identity), 1.0F);

  Mat3 matrix{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  EXPECT_FLOAT_EQ(determinant(matrix), 0.0F);

  Mat3 matrix2{ 3, 2, 1, 1, 1, 0, 0, 1, 1 };
  EXPECT_FLOAT_EQ(determinant(matrix2), 2.0F);
}

TEST_F(Mat3Test, Inverse)
{
  const Mat3 m{ 1.0F, 2.0F, 3.0F, 0.0F, 1.0F, 4.0F, 5.0F, 6.0F, 0.0F };
  Mat3       expected_inverse{ Vec3{ -24.0F, 18.0F, 5.0F }, Vec3{ 20.0F, -15.0F, -4.0F }, Vec3{ -5.0F, 4.0F, 1.0F } };
  Mat3       actual_inverse = inverse(m);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_NEAR(actual_inverse(i, j), expected_inverse(i, j), 0.00001F);
    }
  }

  const Mat3 zero_det_mat{ 1.0F, 2.0F, 3.0F, 1.0F, 2.0F, 3.0F, 1.0F, 2.0F, 3.0F };
  ASSERT_DEATH(inverse(zero_det_mat), "Can't divide by 0");
}
