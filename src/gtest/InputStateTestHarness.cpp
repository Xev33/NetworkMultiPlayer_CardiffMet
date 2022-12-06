#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "InputStateTestHarness.h"
#include "InputState.h"

// #include "InputManager.h"

#include <iostream>
#include <fstream>
#include <thread>

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */

InputStateTestHarness::InputStateTestHarness()
{
  //an input manager is required for the tests.
  //InputManager::StaticInit();
}

InputStateTestHarness::~InputStateTestHarness()
{

}

void InputStateTestHarness::SetUp()
{
  is.reset(new InputState());
}

void InputStateTestHarness::TearDown()
{
  is.reset();
  is2.reset();
}

TEST_F(InputStateTestHarness,TestDefaultConstructor)
{
  EXPECT_EQ(is->GetDesiredHorizontalDelta(), 0);
  EXPECT_EQ(is->GetDesiredVerticalDelta(), 0);
  EXPECT_EQ(is->IsShooting(), false);
}

//Following tests require classes from the client package!
/*
TEST_F(InputStateTestHarness,InputManagerInterface1)
{
  InputManager::sInstance->HandleInput( EInputAction::EIA_Pressed, 'a' );

  is.reset(InputManager::sInstance->GetState())

  EXPECT_FLOAT_EQ(is->GetDesiredHorizontalDelta(), -1);
  EXPECT_FLOAT_EQ(is->GetDesiredVerticalDelta(), 0);
  EXPECT_EQ(is->IsShooting(), false);
}
*/

TEST_F(InputStateTestHarness,TestSerialiseAndDeserialiseInputState)
{
  /*
  std::shared_ptr<OutputMemoryBitStream> out;
  std::shared_ptr<InputMemoryBitStream> in;

  const int BUFF_MAX = 512;
  char* bigBuffer = new char[BUFF_MAX]; //testing only - gets replaced.
  in.reset(new InputMemoryBitStream(bigBuffer,BUFF_MAX));
  out.reset(new OutputMemoryBitStream());

  MovePtr writeOut;
  writeOut.reset(new Move());

  EXPECT_EQ(m->GetTimestamp(), writeOut->GetTimestamp());

  //restrict to time detal
  writeOut->SetTimestamp(3.3f);

  EXPECT_NE(m->GetTimestamp(), writeOut->GetTimestamp()); //with one changed should be different.

  //write it into a buffer.
  writeOut->Write(*out,state);

  // ... imagine networking goes on and we get an
  // actually we're connecting the output buffer to the input.
  // copy the buffer first (or we get double de-allocation)
  int copyLen = out->GetByteLength();
  char* copyBuff = new char[copyLen];
  memcpy(copyBuff, out->GetBufferPtr(), copyLen);

  in.reset(new InputMemoryBitStream(copyBuff, copyLen));

  // update from our server.
  m->Read(*in);

  // expect these to now be the same.
  EXPECT_EQ(m->GetTimestamp(), writeOut->GetTimestamp()); //expect constructed objs to be the same. */
}
