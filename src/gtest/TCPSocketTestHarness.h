#ifndef TCP_SOCKET_TEST_HARNESS_H
#define TCP_SOCKET_TEST_HARNESS_H

#include <limits.h>
#include <gtest/gtest.h>

#include "TCPSocket.h"
#include "SocketUtil.h"
#include "SocketAddressFactory.h"

class TCPSocketTestHarness : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

  TCPSocketPtr server;
  TCPSocketPtr client;

public:

    TCPSocketTestHarness();
    virtual ~TCPSocketTestHarness();
};

#endif // TCP_SOCKET_TEST_HARNESS_H
