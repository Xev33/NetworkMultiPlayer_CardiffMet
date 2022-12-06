#ifndef INPUT_STATE_TEST_HARNESS_H
#define INPUT_STATE_TEST_HARNESS_H

#include <limits.h>
#include <gtest/gtest.h>

#include "InputState.h"

class InputStateTestHarness : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

  InputStatePtr is;
  InputStatePtr is2;

public:
    InputStateTestHarness();
    virtual ~InputStateTestHarness();
};

#endif // INPUT_STATE_TEST_HARNESS_H
