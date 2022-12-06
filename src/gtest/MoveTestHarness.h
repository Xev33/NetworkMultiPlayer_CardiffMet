#ifndef MOVE_TEST_HARNESS_H
#define MOVE_TEST_HARNESS_H

#include <limits.h>
#include <gtest/gtest.h>

#include "Move.h"
#include "InputState.h"

class MoveTestHarness : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

  MovePtr m;
  MovePtr m2;

  InputState is;

public:
    MoveTestHarness();
    virtual ~MoveTestHarness();
};

#endif // MOVE_TEST_HARNESS_H
