#include "mirage_math/vec3.hpp"
#include <gtest/gtest.h>

using MirageMath::Vec3;

class Vec3Test : public ::testing::Test
{
protected:
  Vec3 v1{ 1.0F, 2.0F, 3.0F };
  Vec3 v2{ 4.0F, 5.0F, 6.0F };
};

TEST_F(Vec3Test, DefaultConstructor)
{
  Vec3 vec3;
  EXPECT_EQ(vec3.x, 0.0F);
  EXPECT_EQ(vec3.y, 0.0F);
  EXPECT_EQ(vec3.z, 0.0F);
}

TEST_F(Vec3Test, ParameterizedConstructor)
{
  EXPECT_EQ(v1.x, 1.0F);
  EXPECT_EQ(v1.y, 2.0F);
  EXPECT_EQ(v1.z, 3.0F);
}

TEST_F(Vec3Test, IndexingOperator)
{
  EXPECT_EQ(v1[0], 1.0F);
  EXPECT_EQ(v1[1], 2.0F);
  EXPECT_EQ(v1[2], 3.0F);

  EXPECT_DEATH({ v1[3]; }, "Index > 2");
}

TEST_F(Vec3Test, AdditionOperator)
{
  Vec3 result = v1 + v2;
  EXPECT_EQ(result.x, 5.0F);
  EXPECT_EQ(result.y, 7.0F);
  EXPECT_EQ(result.z, 9.0F);
}

TEST_F(Vec3Test, SubtractionOperator)
{
  Vec3 result = v1 - v2;
  EXPECT_EQ(result.x, -3.0F);
  EXPECT_EQ(result.y, -3.0F);
  EXPECT_EQ(result.z, -3.0F);
}

TEST_F(Vec3Test, MultiplicationOperatorScalar)
{
  Vec3 result = v1 * 2.0F;
  EXPECT_EQ(result.x, 2.0F);
  EXPECT_EQ(result.y, 4.0F);
  EXPECT_EQ(result.z, 6.0F);
}

TEST_F(Vec3Test, DivisionOperatorScalar)
{
  Vec3 result = v2 / 2.0F;
  EXPECT_EQ(result.x, 2.0F);
  EXPECT_EQ(result.y, 2.5F);
  EXPECT_EQ(result.z, 3.0F);

  EXPECT_DEATH({ v2 / 0.0F; }, "Can't divide by 0");
}

TEST_F(Vec3Test, UnaryNegationOperator)
{
  Vec3 result = -v1;
  EXPECT_EQ(result.x, -1.0F);
  EXPECT_EQ(result.y, -2.0F);
  EXPECT_EQ(result.z, -3.0F);
}

TEST_F(Vec3Test, CompoundAdditionAssignmentOperator)
{
  Vec3 result = v1;
  result += 2.0F;
  EXPECT_EQ(result.x, 3.0F);
  EXPECT_EQ(result.y, 4.0F);
  EXPECT_EQ(result.z, 5.0F);
}

TEST_F(Vec3Test, CompoundSubtractionAssignmentOperator)
{
  Vec3 result = v2;
  result -= 1.0F;
  EXPECT_EQ(result.x, 3.0F);
  EXPECT_EQ(result.y, 4.0F);
  EXPECT_EQ(result.z, 5.0F);
}

TEST_F(Vec3Test, CompoundMultiplicationAssignmentOperator)
{
  Vec3 result = v1;
  result *= 2.0F;
  EXPECT_EQ(result.x, 2.0F);
  EXPECT_EQ(result.y, 4.0F);
  EXPECT_EQ(result.z, 6.0F);
}

TEST_F(Vec3Test, CompoundDivisionAssignmentOperator)
{
  Vec3 result = v2;
  result /= 2.0F;
  EXPECT_EQ(result.x, 2.0F);
  EXPECT_EQ(result.y, 2.5F);
  EXPECT_EQ(result.z, 3.0F);

  EXPECT_DEATH({ result /= 0.0F; }, "Can't divide by 0");
}

TEST_F(Vec3Test, Magnitude)
{
  EXPECT_FLOAT_EQ(magnitude(v1), sqrt(14.0F));
  EXPECT_FLOAT_EQ(magnitude(v2), sqrt(77.0F));
}

TEST_F(Vec3Test, Normalize)
{
  Vec3 normalized_v1 = normalize(v1);
  Vec3 normalized_v2 = normalize(v2);

  float magnitude_v1 = magnitude(v1);
  float magnitude_v2 = magnitude(v2);

  EXPECT_FLOAT_EQ(magnitude(normalized_v1), 1.0F);
  EXPECT_FLOAT_EQ(magnitude(normalized_v2), 1.0F);

  for (int i = 0; i < 3; ++i) {
    EXPECT_FLOAT_EQ(normalized_v1[i], v1[i] / magnitude_v1);
    EXPECT_FLOAT_EQ(normalized_v2[i], v2[i] / magnitude_v2);
  }
}

TEST_F(Vec3Test, DotProduct)
{
  Vec3 v1{ 1, 0, 0 };
  Vec3 v2{ 0, 1, 0 };
  Vec3 v3{ 1, 1, 0 };

  EXPECT_FLOAT_EQ(dot(v1, v2), 0.0F);
  EXPECT_FLOAT_EQ(dot(v1, v3), 1.0F);
  EXPECT_FLOAT_EQ(dot(v1, v3), dot(v3, v1));
}

TEST_F(Vec3Test, CrossProduct)
{
  Vec3 v1{ 1, 0, 0 };
  Vec3 v2{ 0, 1, 0 };
  Vec3 v3{ 0, 0, 1 };

  Vec3 cross_result = cross(v1, v2);
  EXPECT_FLOAT_EQ(cross_result.x, 0.0F);
  EXPECT_FLOAT_EQ(cross_result.y, 0.0F);
  EXPECT_FLOAT_EQ(cross_result.z, 1.0F);

  Vec3 parallel_cross_result = cross(v1, Vec3{ 2, 0, 0 });
  EXPECT_FLOAT_EQ(parallel_cross_result.x, 0.0F);
  EXPECT_FLOAT_EQ(parallel_cross_result.y, 0.0F);
  EXPECT_FLOAT_EQ(parallel_cross_result.z, 0.0F);

  Vec3 negative_cross_result = cross(v2, v1);
  EXPECT_FLOAT_EQ(negative_cross_result.x, -cross_result.x);
  EXPECT_FLOAT_EQ(negative_cross_result.y, -cross_result.y);
  EXPECT_FLOAT_EQ(negative_cross_result.z, -cross_result.z);
}