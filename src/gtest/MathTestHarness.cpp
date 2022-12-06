#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "MathTestHarness.h"
#include "Vector3.h"

#include <iostream>
#include <fstream>
#include <thread>

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */

template <typename type> bool isBetween(type x, type lower, type upper)
{
  bool result = (x < upper) && (x > lower) ? true : false;
  return result;
}

MathTestHarness::MathTestHarness()
{

}

MathTestHarness::~MathTestHarness()
{

}

void MathTestHarness::SetUp()
{

}

void MathTestHarness::TearDown()
{

}

TEST_F(MathTestHarness,GetRandomFloatNonGameTest)
{
  float result = Maths::GetRandomFloatNonGame();

  EXPECT_PRED3(isBetween<float>, result, 0.0f, 1.0f);
}

TEST_F(MathTestHarness,Is2DVectorEqual)
{
  Vector3 v1(1.1f,2.2f,0.0f);
  Vector3 v2(0.1f,0.2f,0.0f);
  Vector3 v3(0.1f,0.2f,0.0f);

  EXPECT_FALSE(Maths::Is2DVectorEqual(v1,v2));
  EXPECT_TRUE(Maths::Is2DVectorEqual(v1,v1));
  EXPECT_FALSE(Maths::Is2DVectorEqual(v1,v3));
  EXPECT_TRUE(Maths::Is2DVectorEqual(v2,v3));
}

TEST_F(MathTestHarness,Is3DVectorEqual)
{
  Vector3 v1(1.1f,2.2f,3.3f);
  Vector3 v2(0.1f,0.2f,0.3f);
  Vector3 v3(0.1f,0.2f,0.3f);

  EXPECT_FALSE(Maths::Is3DVectorEqual(v1,v2));
  EXPECT_TRUE(Maths::Is3DVectorEqual(v1,v1));
  EXPECT_FALSE(Maths::Is3DVectorEqual(v1,v3));
  EXPECT_TRUE(Maths::Is3DVectorEqual(v2,v3));
}

TEST_F(MathTestHarness,ToDegrees)
{
  //pi radians = 180
  //pi/2 radians = 90
  //2pi radians = 360
  EXPECT_FLOAT_EQ(Maths::ToDegrees(Maths::PI),180.0f);
  EXPECT_FLOAT_EQ(Maths::ToDegrees(Maths::PI/2.0f),90.0f);
  EXPECT_FLOAT_EQ(Maths::ToDegrees(Maths::PI*2.0f),360.0f);
}
