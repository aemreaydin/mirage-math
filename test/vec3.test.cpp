#include "vec3.hpp"
#include <gtest/gtest.h>

class Vec3Test : public ::testing::Test {
protected:
  Vec3 v1{1.0f, 2.0f, 3.0f};
  Vec3 v2{4.0f, 5.0f, 6.0f};
};

TEST_F(Vec3Test, DefaultConstructor) {
  Vec3 v;
  EXPECT_EQ(v.x, 0.0f);
  EXPECT_EQ(v.y, 0.0f);
  EXPECT_EQ(v.z, 0.0f);
}

TEST_F(Vec3Test, ParameterizedConstructor) {
  EXPECT_EQ(v1.x, 1.0f);
  EXPECT_EQ(v1.y, 2.0f);
  EXPECT_EQ(v1.z, 3.0f);
}

TEST_F(Vec3Test, IndexingOperator) {
  EXPECT_EQ(v1[0], 1.0f);
  EXPECT_EQ(v1[1], 2.0f);
  EXPECT_EQ(v1[2], 3.0f);

  EXPECT_DEATH({ v1[3]; }, "Index > 2");
}

TEST_F(Vec3Test, AdditionOperator) {
  Vec3 result = v1 + v2;
  EXPECT_EQ(result.x, 5.0f);
  EXPECT_EQ(result.y, 7.0f);
  EXPECT_EQ(result.z, 9.0f);
}

TEST_F(Vec3Test, SubtractionOperator) {
  Vec3 result = v1 - v2;
  EXPECT_EQ(result.x, -3.0f);
  EXPECT_EQ(result.y, -3.0f);
  EXPECT_EQ(result.z, -3.0f);
}

TEST_F(Vec3Test, MultiplicationOperatorScalar) {
  Vec3 result = v1 * 2.0f;
  EXPECT_EQ(result.x, 2.0f);
  EXPECT_EQ(result.y, 4.0f);
  EXPECT_EQ(result.z, 6.0f);
}

TEST_F(Vec3Test, DivisionOperatorScalar) {
  Vec3 result = v2 / 2.0f;
  EXPECT_EQ(result.x, 2.0f);
  EXPECT_EQ(result.y, 2.5f);
  EXPECT_EQ(result.z, 3.0f);

  EXPECT_DEATH({ v2 / 0.0f; }, "Can't divide by 0");
}

TEST_F(Vec3Test, UnaryNegationOperator) {
  Vec3 result = -v1;
  EXPECT_EQ(result.x, -1.0f);
  EXPECT_EQ(result.y, -2.0f);
  EXPECT_EQ(result.z, -3.0f);
}

TEST_F(Vec3Test, CompoundAdditionAssignmentOperator) {
  Vec3 result = v1;
  result += 2.0f;
  EXPECT_EQ(result.x, 3.0f);
  EXPECT_EQ(result.y, 4.0f);
  EXPECT_EQ(result.z, 5.0f);
}

TEST_F(Vec3Test, CompoundSubtractionAssignmentOperator) {
  Vec3 result = v2;
  result -= 1.0f;
  EXPECT_EQ(result.x, 3.0f);
  EXPECT_EQ(result.y, 4.0f);
  EXPECT_EQ(result.z, 5.0f);
}

TEST_F(Vec3Test, CompoundMultiplicationAssignmentOperator) {
  Vec3 result = v1;
  result *= 2.0f;
  EXPECT_EQ(result.x, 2.0f);
  EXPECT_EQ(result.y, 4.0f);
  EXPECT_EQ(result.z, 6.0f);
}

TEST_F(Vec3Test, CompoundDivisionAssignmentOperator) {
  Vec3 result = v2;
  result /= 2.0f;
  EXPECT_EQ(result.x, 2.0f);
  EXPECT_EQ(result.y, 2.5f);
  EXPECT_EQ(result.z, 3.0f);

  EXPECT_DEATH({ result /= 0.0f; }, "Can't divide by 0");
}

TEST_F(Vec3Test, Magnitude) {
  EXPECT_FLOAT_EQ(Magnitude(v1), sqrt(14.0f));
  EXPECT_FLOAT_EQ(Magnitude(v2), sqrt(77.0f));
}

TEST_F(Vec3Test, Normalize) {
  Vec3 normalized_v1 = Normalize(v1);
  Vec3 normalized_v2 = Normalize(v2);

  float magnitude_v1 = Magnitude(v1);
  float magnitude_v2 = Magnitude(v2);

  EXPECT_FLOAT_EQ(Magnitude(normalized_v1), 1.0f);
  EXPECT_FLOAT_EQ(Magnitude(normalized_v2), 1.0f);

  for (int i = 0; i < 3; ++i) {
    EXPECT_FLOAT_EQ(normalized_v1[i], v1[i] / magnitude_v1);
    EXPECT_FLOAT_EQ(normalized_v2[i], v2[i] / magnitude_v2);
  }
}
