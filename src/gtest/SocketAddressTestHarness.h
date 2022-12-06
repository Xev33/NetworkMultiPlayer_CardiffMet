#ifndef SOCKETADDRESSESTHARNESS_H
#define SOCKETADDRESSESTHARNESS_H

#include <limits.h>
#include <gtest/gtest.h>

#include "SocketAddress.h"

class SocketAddressTestHarenss : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

  friend class SocketAddress;
  SocketAddressPtr sa;

public:

    SocketAddressTestHarenss();
    virtual ~SocketAddressTestHarenss();
};

#endif // RANDGENTESTHARNESS_H
