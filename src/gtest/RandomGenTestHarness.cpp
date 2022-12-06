#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "RandomGenTestHarness.h"
#include "RandGen.h"

#include <iostream>
#include <fstream>
#include <thread>
#include <memory>

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */

template <typename type> bool isBetween(type x, type lower, type upper)
{
  bool result = (x < upper) && (x > lower) ? true : false;
  return result;
}

RandomGenTestHarness::RandomGenTestHarness()
{
  rg = nullptr;
}

RandomGenTestHarness::~RandomGenTestHarness()
{
  rg.reset();
}

void RandomGenTestHarness::SetUp()
{
    this->rg.reset(new RandGen());
}

void RandomGenTestHarness::TearDown()
{
    this->rg.reset();
    this->rg = nullptr;
}

TEST_F(RandomGenTestHarness,constructor_noArgs)
{
  //number generator is unseeded, but should be constrained
  //to a range by the initisation of the constructor.

  float result = rg->GetRandomFloat();

  EXPECT_PRED3(isBetween<float>, result, 0.0f, 1.0f);
}

TEST_F(RandomGenTestHarness,SeedTest)
{
  rg->Seed(123);

  float first = rg->GetRandomFloat();

  EXPECT_PRED3(isBetween<float>, first, 0.0f, 1.0f);

  // Starting from the same seed twice should give
  // the same initial random number.

  rg->Seed(123);

  float second = rg->GetRandomFloat();

  EXPECT_PRED3(isBetween<float>, second, 0.0f, 1.0f);

  EXPECT_FLOAT_EQ(first, second);
}

TEST_F(RandomGenTestHarness,StaticInit)
{
  RandGen::StaticInit();

  float result = RandGen::sInstance->GetRandomFloat();

  EXPECT_PRED3(isBetween<float>, result, 0.0f, 1.0f);
}

TEST_F(RandomGenTestHarness,GetRandomFloatTest1)
{
  rg->Seed(123);

  float result = rg->GetRandomFloat();

  EXPECT_PRED3(isBetween<float>, result, 0.0f, 1.0f);
}

TEST_F(RandomGenTestHarness,GetRandomFloatTest2)
{
  rg->Seed(123);

  float result = rg->GetRandomFloat();

  EXPECT_PRED3(isBetween<float>, result, -1.0f, 1.0f);
}

TEST_F(RandomGenTestHarness,GetRandomIntTest1)
{
  rg->Seed(123);

  int32_t result = rg->GetRandomInt(0,10);

  EXPECT_PRED3(isBetween<int32_t>, result, 0, 10);
}

TEST_F(RandomGenTestHarness,GetRandomIntTest2)
{
  rg->Seed(123);

  int32_t result = rg->GetRandomInt(-10, 10);

  EXPECT_PRED3(isBetween<int32_t>, result, -10, 10);
}

TEST_F(RandomGenTestHarness,GetRandomIntTest3)
{
  rg->Seed(123);

  int32_t result = rg->GetRandomInt(-200,200);

  EXPECT_PRED3(isBetween<int32_t>, result, -200, 200);
}

TEST_F(RandomGenTestHarness,GetRandomUIntTest1)
{
  rg->Seed(123);

  uint32_t result = rg->GetRandomUInt32(0,10);

  EXPECT_PRED3(isBetween<uint32_t>, result, 0, 10);
}

TEST_F(RandomGenTestHarness,GetRandomUInt32Test2)
{
  rg->Seed(123);

  uint32_t result = rg->GetRandomUInt32(100,200);

  EXPECT_PRED3(isBetween<uint32_t>, result, 100, 200);
}

TEST_F(RandomGenTestHarness,GetRandomVectorTest1)
{
  float min = 0.0f;
  float max = 1.0f;

  rg->Seed(123);

  Vector3 ret = rg->GetRandomVector(Vector3(min,min,min),
                                    Vector3(max,max,max));

  EXPECT_PRED3(isBetween<float>, ret.mX, min, max);
  EXPECT_PRED3(isBetween<float>, ret.mY, min, max);
  EXPECT_PRED3(isBetween<float>, ret.mZ, min, max);
}

TEST_F(RandomGenTestHarness,GetRandomVectorTest2)
{
  float min = -1.0f;
  float max = 1.0f;

  rg->Seed(123);

  Vector3 ret = rg->GetRandomVector(Vector3(min,min,min),
                                    Vector3(max,max,max));

  EXPECT_PRED3(isBetween<float>, ret.mX, min, max);
  EXPECT_PRED3(isBetween<float>, ret.mY, min, max);
  EXPECT_PRED3(isBetween<float>, ret.mZ, min, max);
}

TEST_F(RandomGenTestHarness,GetRandomVectorTest3)
{
  float min = -10.0f;
  float max = 10.0f;

  rg->Seed(123);

  Vector3 ret = rg->GetRandomVector(Vector3(min,min,min),
                                    Vector3(max,max,max));

  EXPECT_PRED3(isBetween<float>, ret.mX, min, max);
  EXPECT_PRED3(isBetween<float>, ret.mY, min, max);
  EXPECT_PRED3(isBetween<float>, ret.mZ, min, max);
}
