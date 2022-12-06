#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "SocketUtilTestHarness.h"
#include "SocketUtil.h"

#include <iostream>
#include <fstream>
#include <thread>

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */

SocketUtilTestHarness::SocketUtilTestHarness()
{

}

SocketUtilTestHarness::~SocketUtilTestHarness()
{

}

void SocketUtilTestHarness::SetUp()
{
  //Allows me to setup for other tests
  //Flaw here in that if one of these fails
  //there's not test forit.
  SocketUtil::StaticInit();
}

void SocketUtilTestHarness::TearDown()
{
  SocketUtil::CleanUp();
}

TEST_F(SocketUtilTestHarness,StaticInit)
{
  //This returns the BSD/WSA error number
  //non zero is an error.
  int errorNo = SocketUtil::GetLastError();

  EXPECT_EQ(errorNo,0);
}

TEST_F(SocketUtilTestHarness,CreateTCPSocket)
{
  TCPSocketPtr t = SocketUtil::CreateTCPSocket(SocketAddressFamily::INET);
  EXPECT_NE(t, nullptr);

  int errorNo = SocketUtil::GetLastError();
  EXPECT_EQ(errorNo,0);

  if(errorNo > 0)
    SocketUtil::ReportError( "Error in: CreateTCPSocket test");
}

TEST_F(SocketUtilTestHarness,CreateUDPSocket)
{
  UDPSocketPtr u = SocketUtil::CreateUDPSocket(SocketAddressFamily::INET);
  EXPECT_NE(u, nullptr);

  int errorNo = SocketUtil::GetLastError();
  EXPECT_EQ(errorNo,0);

  if(errorNo > 0)
    SocketUtil::ReportError( "Error in: CreateUDPSocket test");
}
