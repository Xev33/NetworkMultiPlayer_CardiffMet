#ifndef SOCKETADDRESSESFACTORYTHARNESS_H
#define SOCKETADDRESSESFACTORYTHARNESS_H

#include <limits.h>
#include <gtest/gtest.h>

#include "SocketAddressFactory.h"


class SocketAddressFactoryTestHarness : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

  //The factory has only one static method, so not much to test.

public:

    SocketAddressFactoryTestHarness();
    virtual ~SocketAddressFactoryTestHarness();
};

#endif // SOCKETADDRESSESFACTORYTHARNESS_H
