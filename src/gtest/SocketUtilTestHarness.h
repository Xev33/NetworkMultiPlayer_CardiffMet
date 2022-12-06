#ifndef SOCKET_UTIL_TEST_HARENSS_H_
#define SOCKET_UTIL_TEST_HARENSS_H_

#include <limits.h>
#include <gtest/gtest.h>

#include "SocketUtil.h"


class SocketUtilTestHarness : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

  //Static methods only, no point in instatitating.

public:

    SocketUtilTestHarness();
    virtual ~SocketUtilTestHarness();
};

#endif // SOCKET_UTIL_TEST_HARENSS_H_
