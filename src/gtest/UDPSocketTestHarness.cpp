#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "UDPSocketTestHarness.h"
#include "UDPSocket.h"
#include "SocketUtil.h"

#include <iostream>
#include <fstream>
#include <thread>

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */

 //At home - use online echo server.
 // #define ECHO_UDP "52.20.16.20:40000"


// On Campus
#define ECHO_UDP "127.0.0.1:7"

UDPSocketTestHarness::UDPSocketTestHarness()
{
  server = nullptr;
  client = nullptr;
}

UDPSocketTestHarness::~UDPSocketTestHarness()
{
  server.reset();
  client.reset();
}

void UDPSocketTestHarness::SetUp()
{
  //Allows me to setup for other tests
  //Flaw here in that if one of these fails
  //there's not test forit.
  SocketUtil::StaticInit();

  server = SocketUtil::CreateUDPSocket(SocketAddressFamily::INET);
  client = SocketUtil::CreateUDPSocket(SocketAddressFamily::INET);

}

void UDPSocketTestHarness::TearDown()
{
  SocketUtil::CleanUp();
}

TEST_F(UDPSocketTestHarness,Bind)
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

TEST_F(UDPSocketTestHarness,RecieveFromBound)
{
    // Create a new socket address
    const SocketAddressPtr socketAddress = SocketAddressFactory::CreateIPv4FromString("0.0.0.0:54321");

    int retVal = server->Bind(*socketAddress);

    ASSERT_EQ(retVal, NO_ERROR);

    int errorNo = SocketUtil::GetLastError();

    if(errorNo > 0)
      SocketUtil::ReportError( "Error in: Recieve from Bound test");

    ASSERT_EQ(errorNo,0);

    const int BUFF_MAX = 32;
    char buff[BUFF_MAX];

    SocketAddressPtr otherAddress(new SocketAddress());

    std::cout << "Call to Receive from has blocked! Please send a UDP packet to port: 54321" << std::endl;
    std::cout << "From bash: echo \"This is my data\" > /dev/udp/127.0.0.1/54321" << std::endl;

    int readCount = server->ReceiveFrom(static_cast<void*>(buff),BUFF_MAX,*otherAddress);

    EXPECT_NE(otherAddress,nullptr);

    if(otherAddress != nullptr)
    {
      //TODO add some support functions to get these printed in a better format.
      std::cout << "Address (not string format):" << otherAddress->getIP4() << std::endl;
      std::cout << "Port (not string format):" << otherAddress->getPort() << std::endl;
      std::cout << "Family (not string format):" << otherAddress->getFamily() << std::endl;
    }

    // Null terminator is not read from the stream, put this back. 
    buff[readCount] = '\0';
    string output(buff);


    if(readCount > 0)
      std::cout << "Got: " << output << std::endl;

    //not the greatest test, make sure we got something back.
    EXPECT_GT(readCount, 0);
}

/*
* This is a tricky test to write, my solution is to use an online
* echo server.  Echo is one of a number of simple services or small
* servers provided on unix/linux hosts for network code debugging.
* someone has made a public version here - http://tcpbin.org/
*
* Essentially echo sends back the bytes sent.
*/
TEST_F(UDPSocketTestHarness,EchoTest)
{
  // Create a new socket address
  const SocketAddressPtr socketAddress = SocketAddressFactory::CreateIPv4FromString(ECHO_UDP);

  // Echo test.

  string sendStr("Hello World!");

  // send a string to the echo server.

  int writeCount = client->SendTo(static_cast<const void*>(sendStr.c_str()),sendStr.length()+1,*socketAddress);

  // the echo server will send it back

  const int BUFF_MAX = 32;
  char buff[BUFF_MAX];

  SocketAddressPtr otherAddress(new SocketAddress());

  int readCount = client->ReceiveFrom(static_cast<void*>(buff),BUFF_MAX,*otherAddress);

  EXPECT_NE(otherAddress,nullptr);

  if(otherAddress != nullptr)
  {
    //TODO add some support functions to get these printed in a better format.
    std::cout << "Address (not string format):" << otherAddress->getIP4() << std::endl;
    std::cout << "Port (not string format):" << otherAddress->getPort() << std::endl;
    std::cout << "Family (not string format):" << otherAddress->getFamily() << std::endl;
  }

  string recStr(buff);

  std::cout << "Echo test visual inspection" << std::endl;
  std::cout << "Sent: " << sendStr << std::endl;
  std::cout << "Recieved: " << recStr << std::endl;

  EXPECT_EQ(writeCount, readCount);
  EXPECT_EQ(sendStr.length(), recStr.length());
  EXPECT_EQ(sendStr, recStr);
}

/* Test non blocking:
1. Create a non blocking socket bound on a port.
2. Send a packet to it.
3. Read the packet from it.
*/
TEST_F(UDPSocketTestHarness,NonBlockingModeTest)
{
  // Create a new socket addresses
  const SocketAddressPtr recieveFromAddr = SocketAddressFactory::CreateIPv4FromString("0.0.0.0:54321");

  // Note: This has to be the socket address 0.0.0.0 as a listening address is OK, but not
  // as a destination.
  const SocketAddressPtr sendToAddr = SocketAddressFactory::CreateIPv4FromString("127.0.0.1:54321");

  int retVal = server->Bind(*recieveFromAddr);

  ASSERT_EQ(retVal, NO_ERROR);

  int errorNo = SocketUtil::GetLastError();

  if(errorNo > 0)
    SocketUtil::ReportError( "Error in: NonBlockingMode test");

  ASSERT_EQ(errorNo,0);

  retVal = server->SetNonBlockingMode(true);

  ASSERT_EQ(retVal, NO_ERROR);

  errorNo = SocketUtil::GetLastError();

  if(errorNo > 0)
    SocketUtil::ReportError( "Error in: NonBlockingMode test");

  ASSERT_EQ(errorNo,0);

  // Echo test.

  string sendStr("Hello World!");

  // send a string to the echo server.

  int writeCount = client->SendTo(static_cast<const void*>(sendStr.c_str()),sendStr.length()+1,*sendToAddr);

  // the echo server will send it back

  const int BUFF_MAX = 32;
  char buff[BUFF_MAX];

  int readCount = server->ReceiveFrom(static_cast<void*>(buff),BUFF_MAX,*recieveFromAddr);

  string recStr(buff);

  std::cout << "Echo test visual inspection" << std::endl;
  std::cout << "Sent: " << sendStr << std::endl;
  std::cout << "Recieved: " << recStr << std::endl;

  EXPECT_EQ(writeCount, readCount);
  EXPECT_EQ(sendStr.length(), recStr.length());
  EXPECT_EQ(sendStr, recStr);

}
