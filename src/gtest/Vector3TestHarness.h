#ifndef VECTOR3TESTHARNESS_H_
#define VECTOR3TESTHARNESS_H_

#include <limits.h>
#include <gtest/gtest.h>

#include "Vector3.h"

#include <memory>
using std::shared_ptr;

class Vector3TestHarness : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

  shared_ptr<Vector3> vec;

public:

    Vector3TestHarness();
    virtual ~Vector3TestHarness();
};

#endif // VECTOR3TESTHARNESS_H_
