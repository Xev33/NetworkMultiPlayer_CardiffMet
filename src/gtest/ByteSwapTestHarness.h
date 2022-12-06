#ifndef BYTE_SWAP_TESTHARNESS_H_
#define BYTE_SWAP_TESTHARNESS_H_

#include <limits.h>
#include <gtest/gtest.h>

#include "ByteSwap.h"

#include <memory>
using std::shared_ptr;

class ByteSwapTestHarness : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

public:

    ByteSwapTestHarness();
    virtual ~ByteSwapTestHarness();
};

#endif // BYTE_SWAP_TESTHARNESS_H_
