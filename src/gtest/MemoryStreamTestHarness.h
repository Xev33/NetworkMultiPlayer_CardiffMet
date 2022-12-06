#ifndef MEMORY_STREAM_TESTHARNESS_H_
#define MEMORY_STREAM_TESTHARNESS_H_

#include <limits.h>
#include <gtest/gtest.h>

#include <memory>
using std::shared_ptr;

#include "InputMemoryStream.h"
#include "OutputMemoryStream.h"

class MemoryStreamTestHarness : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

  static const int BUFF_MAX = 512;
  char *bigBuffer; //can't staticly allocate - Input memory stream wants to deallocate!

  shared_ptr<OutputMemoryStream> out;
  shared_ptr<InputMemoryStream> in;

public:

    MemoryStreamTestHarness();
    virtual ~MemoryStreamTestHarness();
};

#endif // MEMORY_STREAM_TESTHARNESS_H_
