#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "MoveTestHarness.h"
#include "Move.h"

#include <iostream>
#include <fstream>
#include <thread>

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */

MoveTestHarness::MoveTestHarness()
{

}

MoveTestHarness::~MoveTestHarness()
{

}

void MoveTestHarness::SetUp()
{
  m.reset(new Move());
  m2.reset(new Move(this->is, 1.0f, 1.0f));
}

void MoveTestHarness::TearDown()
{
  m.reset();
  m2.reset();
}

TEST_F(MoveTestHarness,TestDefaultConstructor)
{

  EXPECT_FLOAT_EQ(m->GetTimestamp(), 0.0f);
  EXPECT_FLOAT_EQ(m->GetDeltaTime(), 0.0f);
}

TEST_F(MoveTestHarness,TestOverloadedConstructor)
{

  EXPECT_FLOAT_EQ(m2->GetTimestamp(), 1.0f);
  EXPECT_FLOAT_EQ(m2->GetDeltaTime(), 1.0f);
}

TEST_F(MoveTestHarness,TestSerialiseAndDeserialiseMove)
{
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
  writeOut->Write(*out);

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
  EXPECT_EQ(m->GetTimestamp(), writeOut->GetTimestamp()); //expect constructed objs to be the same.
}
