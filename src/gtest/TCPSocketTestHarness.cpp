#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "TCPSocketTestHarness.h"
#include "TCPSocket.h"
#include "SocketUtil.h"

#include <iostream>
#include <fstream>
#include <thread>

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */

// At home
// #define ECHO_TCP "52.20.16.20:30000"


// On Campus
// Note campus machines need an active echo service (https://www.howtogeek.com/250228/what-windows-10s-optional-features-do-and-how-to-turn-them-on-or-off/). 
#define ECHO_TCP "127.0.0.1:7"

TCPSocketTestHarness::TCPSocketTestHarness()
{
  server = nullptr;
  client = nullptr;
}

TCPSocketTestHarness::~TCPSocketTestHarness()
{
  server.reset();
  client.reset();
}

void TCPSocketTestHarness::SetUp()
{
  //Allows me to setup for other tests
  //Flaw here in that if one of these fails
  //there's not test forit.
  SocketUtil::StaticInit();

  server = SocketUtil::CreateTCPSocket(SocketAddressFamily::INET);
  client = SocketUtil::CreateTCPSocket(SocketAddressFamily::INET);

}

void TCPSocketTestHarness::TearDown()
{
  SocketUtil::CleanUp();
}

TEST_F(TCPSocketTestHarness,Bind)
{
    // Create a new socket address
    const SocketAddressPtr socketAddress = SocketAddressFactory::CreateIPv4FromString("0.0.0.0:54321");

    int retVal = server->Bind(*socketAddress);

    EXPECT_EQ(retVal, NO_ERROR);

    int errorNo = SocketUtil::GetLastError();

    if(errorNo > 0)
      SocketUtil::ReportError( "Error in: Bind test");

    EXPECT_EQ(errorNo,0);
}

TEST_F(TCPSocketTestHarness,Listen)
{
  // Create a new socket address
  const SocketAddressPtr socketAddress = SocketAddressFactory::CreateIPv4FromString("0.0.0.0:54321");

  int retVal = server->Bind(*socketAddress);

  ASSERT_EQ(retVal, NO_ERROR);

  int errorNo = SocketUtil::GetLastError();
  ASSERT_EQ(errorNo,0);

  if(errorNo > 0)
    SocketUtil::ReportError( "Error in: Listen test");

  retVal = server->Listen(5);

  EXPECT_EQ(retVal,NO_ERROR);

  errorNo = SocketUtil::GetLastError();
  EXPECT_EQ(errorNo,0);

  if(errorNo > 0)
    SocketUtil::ReportError( "Error in: Listen test");
}

/* Test passes but requires manual intervention, commented for now */

TEST_F(TCPSocketTestHarness,Accept)
{
  // Create a new socket address
  const SocketAddressPtr socketAddress = SocketAddressFactory::CreateIPv4FromString("0.0.0.0:54321");

  int retVal = server->Bind(*socketAddress);

  ASSERT_EQ(retVal, NO_ERROR);

  int errorNo = SocketUtil::GetLastError();
  ASSERT_EQ(errorNo,0);

  if(errorNo > 0)
    SocketUtil::ReportError( "Error in: Accept test");

  retVal = server->Listen(5);

  EXPECT_EQ(retVal,NO_ERROR);

  errorNo = SocketUtil::GetLastError();
  EXPECT_EQ(errorNo,0);

  if(errorNo > 0)
    SocketUtil::ReportError( "Error in: Accept test");

  SocketAddressPtr otherAddress(new SocketAddress());

  std::cout << "Call to Accept has blocked! Make a tcp connection to port 54321" << std::endl;
  std::cout << "Or from bash: echo \"This is my data\" > /dev/tcp/127.0.0.1/54321" << std::endl;

  TCPSocketPtr otherSocket = server->Accept(*otherAddress);

  EXPECT_NE(otherSocket,nullptr);

  if(otherAddress != nullptr)
  {
    //TODO add some support functions to get these printed in a better format.
    std::cout << "Address (not string format):" << otherAddress->getIP4() << std::endl;
    std::cout << "Port (not string format):" << otherAddress->getPort() << std::endl;
    std::cout << "Family (not string format):" << otherAddress->getFamily() << std::endl;
  }

  errorNo = SocketUtil::GetLastError();
  EXPECT_EQ(errorNo,0);

  if(errorNo > 0)
    SocketUtil::ReportError( "Error in: Accept test");

}

/*
* This is a tricky test to write, my solution is to use an online
* echo server.  Echo is one of a number of simple services or small
* servers provided on unix/linux hosts for network code debugging.
* someone has made a public version here - http://tcpbin.org/
*
* Essentially echo sends back the bytes sent.
*/
TEST_F(TCPSocketTestHarness,Connect)
{
  // Create a new socket address
  const SocketAddressPtr socketAddress = SocketAddressFactory::CreateIPv4FromString(ECHO_TCP);

  int retVal = client->Connect(*socketAddress);

  EXPECT_EQ(retVal,NO_ERROR);

  // shared_ptr automatically calls the destructor when the
  //object goes out of scope - the destructor calls
  //close on the socket.
}

/*
* This is a tricky test to write, my solution is to use an online
* echo server.  Echo is one of a number of simple services or small
* servers provided on unix/linux hosts for network code debugging.
* someone has made a public version here - http://tcpbin.org/
*
* Essentially echo sends back the bytes sent.
*/
TEST_F(TCPSocketTestHarness,EchoTest)
{
  // Create a new socket address
  const SocketAddressPtr socketAddress = SocketAddressFactory::CreateIPv4FromString(ECHO_TCP);

  int retVal = client->Connect(*socketAddress);

  ASSERT_EQ(retVal,NO_ERROR);

  // Echo test.

  string sendStr("Hello World!");

  // send a string to the echo server.

  int writeCount = client->Send(static_cast<const void*>(sendStr.c_str()),sendStr.length()+1);

  // the echo server will send it back

  const int BUFF_MAX = 32;
  char buff[BUFF_MAX];

  int readCount = client->Receive(static_cast<void*>(buff),BUFF_MAX);

  EXPECT_GT(readCount, 0);

  string recStr(buff);

  std::cout << "Echo test visual inspection" << std::endl;
  std::cout << "Sent: " << sendStr << std::endl;
  std::cout << "Recieved: " << recStr << std::endl;

  EXPECT_EQ(writeCount, readCount);
  EXPECT_EQ(sendStr.length(), recStr.length());
  EXPECT_EQ(sendStr, recStr);
}
