#ifndef UDP_SOCKET_TEST_HARNESS_H
#define UDP_SOCKET_TEST_HARNESS_H

#include <limits.h>
#include <gtest/gtest.h>

#include "UDPSocket.h"
#include "SocketUtil.h"
#include "SocketAddressFactory.h"

class UDPSocketTestHarness : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

  UDPSocketPtr server;
  UDPSocketPtr client;

public:
    UDPSocketTestHarness();
    virtual ~UDPSocketTestHarness();
};

#endif // UDP_SOCKET_TEST_HARNESS_H
