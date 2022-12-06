#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "Vector3TestHarness.h"
#include "Vector3.h"

#include <iostream>
#include <fstream>
#include <thread>

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */

Vector3TestHarness::Vector3TestHarness()
{
  vec = nullptr;
}

Vector3TestHarness::~Vector3TestHarness()
{
  vec.reset();
}

void Vector3TestHarness::SetUp()
{
    this->vec.reset(new Vector3());
}

void Vector3TestHarness::TearDown()
{
    this->vec.reset();
    this->vec = nullptr;
}

TEST_F(Vector3TestHarness,constructor_noArgs)
{
    // Check defaults are set
    EXPECT_FLOAT_EQ(vec->mX, 0.0f);
    EXPECT_FLOAT_EQ(vec->mY, 0.0f);
    EXPECT_FLOAT_EQ(vec->mZ, 0.0f);
}

TEST_F(Vector3TestHarness,constructor_args)
{
  //Check second constructor
  this->vec.reset();
  this->vec = nullptr;

  // Create with overloaded constructor.
  this->vec.reset(new Vector3(1.1f, 2.2f, 3.3f));

  // Check values
  EXPECT_FLOAT_EQ(vec->mX, 1.1f);
  EXPECT_FLOAT_EQ(vec->mY, 2.2f);
  EXPECT_FLOAT_EQ(vec->mZ, 3.3f);
}

TEST_F(Vector3TestHarness,Set)
{
  //set values
  this->vec->Set(1.1f,2.2f,3.3f);

  // Check values
  EXPECT_FLOAT_EQ(vec->mX, 1.1f);
  EXPECT_FLOAT_EQ(vec->mY, 2.2f);
  EXPECT_FLOAT_EQ(vec->mZ, 3.3f);
}

TEST_F(Vector3TestHarness,Plus)
{
  // Could use shared pointers here
  // but it overcomplicates things.
  Vector3 v1(1.0f, 1.0f, 1.0f);
  Vector3 v2(1.0f, 1.0f, 1.0f);
  Vector3 result = v1 + v2;

  // Check values
  EXPECT_FLOAT_EQ(result.mX, 2.0f);
  EXPECT_FLOAT_EQ(result.mY, 2.0f);
  EXPECT_FLOAT_EQ(result.mZ, 2.0f);

}

TEST_F(Vector3TestHarness,Minus)
{
  // Could use shared pointers here
  // but it overcomplicates things.
  Vector3 v1(2.0f, 2.0f, 2.0f);
  Vector3 v2(1.0f, 1.0f, 1.0f);
  Vector3 result = v1 - v2;

  // Check values
  EXPECT_FLOAT_EQ(result.mX, 1.0f);
  EXPECT_FLOAT_EQ(result.mY, 1.0f);
  EXPECT_FLOAT_EQ(result.mZ, 1.0f);
}


TEST_F(Vector3TestHarness,CompMult)
{
  // Could use shared pointers here
  // but it overcomplicates things.
  Vector3 v1(2.0f, 2.0f, 2.0f);
  Vector3 v2(2.0f, 2.0f, 2.0f);
  Vector3 result = v1 * v2;

  // Check values
  EXPECT_FLOAT_EQ(result.mX, 4.0f);
  EXPECT_FLOAT_EQ(result.mY, 4.0f);
  EXPECT_FLOAT_EQ(result.mZ, 4.0f);
}

// vector3 * scalar
TEST_F(Vector3TestHarness,Scalar1)
{
  //set values
  this->vec->Set(1.1f,2.2f,3.3f);
  float scalar = 2.0f;

  Vector3 result = *this->vec * scalar;

  // Check values
  EXPECT_FLOAT_EQ(result.mX, 2.2f);
  EXPECT_FLOAT_EQ(result.mY, 4.4f);
  EXPECT_FLOAT_EQ(result.mZ, 6.6f);
}

// sclar * vector3
TEST_F(Vector3TestHarness,Scalar2)
{
  //set values
  this->vec->Set(1.1f,2.2f,3.3f);
  float scalar = 2.0f;

  Vector3 result = *this->vec * scalar;

  // Check values
  EXPECT_FLOAT_EQ(result.mX, 2.2f);
  EXPECT_FLOAT_EQ(result.mY, 4.4f);
  EXPECT_FLOAT_EQ(result.mZ, 6.6f);
}

TEST_F(Vector3TestHarness,PlusEquals)
{
  this->vec->Set(1.0f, 2.0f, 3.0f);
  Vector3 v2(1.0f, 1.0f, 1.0f);
  (*this->vec) += v2;

  // Check values
  EXPECT_FLOAT_EQ(this->vec->mX, 2.0f);
  EXPECT_FLOAT_EQ(this->vec->mY, 3.0f);
  EXPECT_FLOAT_EQ(this->vec->mZ, 4.0f);

}

TEST_F(Vector3TestHarness,MinusEquals)
{
  this->vec->Set(4.0f, 3.0f, 2.0f);
  Vector3 v2(1.0f, 1.0f, 1.0f);
  (*this->vec) -= v2;

  // Check values
  EXPECT_FLOAT_EQ(this->vec->mX, 3.0f);
  EXPECT_FLOAT_EQ(this->vec->mY, 2.0f);
  EXPECT_FLOAT_EQ(this->vec->mZ, 1.0f);

}

TEST_F(Vector3TestHarness,Length1)
{
  this->vec->Set(1.0f, 0.0f, 0.0f);

  float length = this->vec->Length();
  EXPECT_FLOAT_EQ(length, 1.0f);
}

TEST_F(Vector3TestHarness,Length2)
{
  this->vec->Set(0.0f, 1.0f, 0.0f);

  float length = this->vec->Length();
  EXPECT_FLOAT_EQ(length, 1.0f);
}

TEST_F(Vector3TestHarness,Length3)
{
  this->vec->Set(0.0f, 0.0f, 1.0f);

  float length = this->vec->Length();
  EXPECT_FLOAT_EQ(length, 1.0f);
}

TEST_F(Vector3TestHarness,Length4)
{
  this->vec->Set(1.0f, 1.0f, 0.0f);

  float length = this->vec->Length();
  EXPECT_FLOAT_EQ(length, 1.414214f);
}

TEST_F(Vector3TestHarness,Length5)
{
  this->vec->Set(0.0f, 1.0f, 1.0f);

  float length = this->vec->Length();
  EXPECT_FLOAT_EQ(length, 1.414214f);
}

TEST_F(Vector3TestHarness,Length2D)
{
  this->vec->Set(1.0f, 1.0f, 0.0f);

  float length = this->vec->Length2D();
  EXPECT_FLOAT_EQ(length, 1.414214f);
}

TEST_F(Vector3TestHarness,LengthSq)
{
  this->vec->Set(0.0f, 1.0f, 1.0f);

  float length = this->vec->LengthSq();
  EXPECT_FLOAT_EQ(length, 2.0f);
}

TEST_F(Vector3TestHarness,LengthSq1)
{
  this->vec->Set(2.0f, 2.0f, 2.0f);

  float length = this->vec->LengthSq();
  EXPECT_FLOAT_EQ(length, 12.0f);
}

TEST_F(Vector3TestHarness,Normalise)
{
  this->vec->Set(2.0f, 2.0f, 2.0f);

  float length = this->vec->Length();
  EXPECT_GT(length, 1.0f);

  this->vec->Normalize();

  length = this->vec->Length();
  EXPECT_FLOAT_EQ(length, 1.0f);
}

TEST_F(Vector3TestHarness,Normalise2D)
{
  this->vec->Set(2.0f, 2.0f, 0.0f);

  float length = this->vec->Length();
  EXPECT_GT(length, 1.0f);

  this->vec->Normalize();

  length = this->vec->Length();
  EXPECT_FLOAT_EQ(length, 1.0f);
}

TEST_F(Vector3TestHarness,Dot)
{
  // Could use shared pointers here
  // but it overcomplicates things.
  Vector3 v1(1.0f, 0.0f, 0.0f);
  Vector3 v2(0.0f, 1.0f, 0.0f);
  float result = Dot(v1,v2);

  // Check values - should be cos(90) - 0.0f
  EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST_F(Vector3TestHarness,Dot2)
{
  // Could use shared pointers here
  // but it overcomplicates things.
  Vector3 v1(1.0f, 0.0f, 0.0f);
  Vector3 v2(-1.0f, 0.0f, 0.0f);
  float result = Dot(v1,v2);

  // Check values - should be cos(180) - -1.0f
  EXPECT_FLOAT_EQ(result, -1.0f);
}

TEST_F(Vector3TestHarness,Dot3)
{
  // Could use shared pointers here
  // but it overcomplicates things.
  Vector3 v1(1.0f, 0.0f, 0.0f);
  Vector3 v2(1.0f, 0.0f, 0.0f);
  float result = Dot(v1,v2);

  // Check values - should be cos(0) - 1.0f
  EXPECT_FLOAT_EQ(result, 1.0f);
}

TEST_F(Vector3TestHarness,Dot2D)
{
  // Could use shared pointers here
  // but it overcomplicates things.
  Vector3 v1(1.0f, 0.0f, 0.0f);
  Vector3 v2(0.0f, 1.0f, 0.0f);
  float result = Dot(v1,v2);

  // Check values - should be cos(90) - 0.0f
  EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST_F(Vector3TestHarness,Cross)
{
  // Could use shared pointers here
  // but it overcomplicates things.
  Vector3 v1(1.0f, 0.0f, 0.0f);
  Vector3 v2(0.0f, 1.0f, 0.0f);
  Vector3 result = Cross(v1,v2);

  // Check values
  EXPECT_FLOAT_EQ(result.mX, 0.0f);
  EXPECT_FLOAT_EQ(result.mY, 0.0f);
  EXPECT_FLOAT_EQ(result.mZ, 1.0f);
}

TEST_F(Vector3TestHarness,Cross2)
{
  // Could use shared pointers here
  // but it overcomplicates things.
  Vector3 v1(1.0f, 0.0f, 0.0f);
  Vector3 v2(0.0f, -1.0f, 0.0f);

  Vector3 result = Cross(v1,v2);

  // Check values
  EXPECT_FLOAT_EQ(result.mX, 0.0f);
  EXPECT_FLOAT_EQ(result.mY, 0.0f);
  EXPECT_FLOAT_EQ(result.mZ, -1.0f);
}

TEST_F(Vector3TestHarness,Lerp)
{
  // Could use shared pointers here
  // but it overcomplicates things.
  Vector3 v1(0.0f, 0.0f, 0.0f);
  Vector3 v2(1.0f, 0.0f, 0.0f);

  Vector3 result = Lerp(v1,v2,0.5f);

  // Check values
  EXPECT_FLOAT_EQ(result.mX, 0.5f);
  EXPECT_FLOAT_EQ(result.mY, 0.0f);
  EXPECT_FLOAT_EQ(result.mZ, 0.0f);
}

TEST_F(Vector3TestHarness,Lerp2)
{
  // Could use shared pointers here
  // but it overcomplicates things.
  Vector3 v1(0.0f, 0.0f, 0.0f);
  Vector3 v2(0.0f, 1.0f, 0.0f);

  Vector3 result = Lerp(v1,v2,0.5f);

  // Check values
  EXPECT_FLOAT_EQ(result.mX, 0.0f);
  EXPECT_FLOAT_EQ(result.mY, 0.5f);
  EXPECT_FLOAT_EQ(result.mZ, 0.0f);
}

TEST_F(Vector3TestHarness,Lerp3)
{
  // Could use shared pointers here
  // but it overcomplicates things.
  Vector3 v1(0.0f, 0.0f, 0.0f);
  Vector3 v2(0.0f, 0.0f, 1.0f);

  Vector3 result = Lerp(v1,v2,0.5f);

  // Check values
  EXPECT_FLOAT_EQ(result.mX, 0.0f);
  EXPECT_FLOAT_EQ(result.mY, 0.0f);
  EXPECT_FLOAT_EQ(result.mZ, 0.5f);
}

TEST_F(Vector3TestHarness,Lerp4)
{
  // Could use shared pointers here
  // but it overcomplicates things.
  Vector3 v1(0.0f, 0.0f, 0.0f);
  Vector3 v2(1.0f, 1.0f, 1.0f);

  Vector3 result = Lerp(v1,v2,0.5f);

  // Check values
  EXPECT_FLOAT_EQ(result.mX, 0.5f);
  EXPECT_FLOAT_EQ(result.mY, 0.5f);
  EXPECT_FLOAT_EQ(result.mZ, 0.5f);
}

TEST_F(Vector3TestHarness,Lerp5)
{
  // Could use shared pointers here
  // but it overcomplicates things.
  Vector3 v1(0.0f, 0.0f, 0.0f);
  Vector3 v2(1.0f, 1.0f, 1.0f);

  Vector3 result = Lerp(v1,v2,0.1f);

  // Check values
  EXPECT_FLOAT_EQ(result.mX, 0.1f);
  EXPECT_FLOAT_EQ(result.mY, 0.1f);
  EXPECT_FLOAT_EQ(result.mZ, 0.1f);
}

TEST_F(Vector3TestHarness,Lerp6)
{
  // Could use shared pointers here
  // but it overcomplicates things.
  Vector3 v1(0.0f, 0.0f, 0.0f);
  Vector3 v2(-1.0f, -1.0f, -1.0f);

  Vector3 result = Lerp(v1,v2,0.1f);

  // Check values
  EXPECT_FLOAT_EQ(result.mX, -0.1f);
  EXPECT_FLOAT_EQ(result.mY, -0.1f);
  EXPECT_FLOAT_EQ(result.mZ, -0.1f);
}
