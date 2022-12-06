#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "SocketUtil.h"
#include "SocketAddressTestHarness.h"
#include "SocketAddress.h"

#include <iostream>
#include <fstream>
#include <thread>

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */

SocketAddressTestHarenss::SocketAddressTestHarenss()
{
  sa = nullptr;
}

SocketAddressTestHarenss::~SocketAddressTestHarenss()
{
  sa.reset();
}

void SocketAddressTestHarenss::SetUp()
{
    SocketUtil::StaticInit();
    this->sa.reset(new SocketAddress(INADDR_ANY,0));
}

void SocketAddressTestHarenss::TearDown()
{
    SocketUtil::CleanUp();
    this->sa.reset();
    this->sa = nullptr;
}

TEST_F(SocketAddressTestHarenss,constructor_noArgs)
{
    // need to cheat a bit, the harness uses the overloaded constructor.
    this->sa.reset();
    this->sa = nullptr;

    // make a new one - with the default constructor.
    this->sa.reset(new SocketAddress());

    // Check defaults are set
    EXPECT_EQ(sa->getIP4(), INADDR_ANY);
    EXPECT_EQ(sa->getPort(), 0);
    EXPECT_EQ(sa->getFamily(), AF_INET);
}

TEST_F(SocketAddressTestHarenss,constructor_withArgs)
{
    // Check defaults are set
    EXPECT_EQ(sa->getIP4(), INADDR_ANY);
    EXPECT_EQ(sa->getPort(), 0);
    EXPECT_EQ(sa->getFamily(), AF_INET);
}

TEST_F(SocketAddressTestHarenss,ToString)
{
  std::string str = this->sa->ToString();
  EXPECT_EQ("0.0.0.0:0", str);
}
