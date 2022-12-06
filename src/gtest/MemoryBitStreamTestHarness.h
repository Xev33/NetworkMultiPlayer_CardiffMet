#ifndef MEMORY_BIT_STREAM_TESTHARNESS_H_
#define MEMORY_BIT_STREAM_TESTHARNESS_H_

#include <limits.h>
#include <gtest/gtest.h>

#include <memory>
using std::shared_ptr;

#include "InputMemoryBitStream.h"
#include "OutputMemoryBitStream.h"

class MemoryBitStreamTestHarenss : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

  static const int BUFF_MAX = 512;
  char *bigBuffer; //can't staticly allocate - Input memory stream wants to deallocate!

  shared_ptr<OutputMemoryBitStream> out;
  shared_ptr<InputMemoryBitStream> in;

public:

    MemoryBitStreamTestHarenss();
    virtual ~MemoryBitStreamTestHarenss();
};

#endif // MEMORY_BIT_STREAM_TESTHARNESS_H_
