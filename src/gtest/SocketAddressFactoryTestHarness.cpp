#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "SocketAddressFactoryTestHarness.h"
#include "SocketAddressFactory.h"

// Need to init sockets on Windows (setup WSA)
#include "SocketUtil.h"

#include <iostream>
#include <fstream>
#include <thread>

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */

SocketAddressFactoryTestHarness::SocketAddressFactoryTestHarness()
{

}

SocketAddressFactoryTestHarness::~SocketAddressFactoryTestHarness()
{

}

void SocketAddressFactoryTestHarness::SetUp()
{
	SocketUtil::StaticInit();
}

void SocketAddressFactoryTestHarness::TearDown()
{

}

TEST_F(SocketAddressFactoryTestHarness,CreateIPv4FromString)
{
  // Create a new socket address
  SocketAddressPtr sa;
  sa = SocketAddressFactory::CreateIPv4FromString("0.0.0.0:0");

  // Check defaults are set
  EXPECT_EQ(sa->getIP4(), INADDR_ANY);
  EXPECT_EQ(sa->getPort(), 0);
  EXPECT_EQ(sa->getFamily(), AF_INET);
}

TEST_F(SocketAddressFactoryTestHarness,CreateIPv4FromString2)
{
    // Create a new socket address
  SocketAddressPtr sa;
  sa = SocketAddressFactory::CreateIPv4FromString("127.0.0.1:1234");
  std::string str = sa->ToString();
  EXPECT_EQ("127.0.0.1:1234", str);
}
