#ifndef MATH_TEST_HARNESS_H_
#define MATH_TEST_HARNESS_H_

#include <limits.h>
#include <gtest/gtest.h>

#include "Maths.h"

#include <memory>
using std::shared_ptr;

class MathTestHarness : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

public:

    MathTestHarness();
    virtual ~MathTestHarness();
};

#endif // MATH_TEST_HARNESS_H_
