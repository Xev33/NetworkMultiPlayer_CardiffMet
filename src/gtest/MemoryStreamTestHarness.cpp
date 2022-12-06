#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "MemoryStreamTestHarness.h"
#include "TestObject.h"
#include "Maths.h"
#include "Colors.h"

#include <iostream>
#include <fstream>
#include <thread>

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */


MemoryStreamTestHarness::MemoryStreamTestHarness()
{
  in = nullptr;
  out = nullptr;
}

MemoryStreamTestHarness::~MemoryStreamTestHarness()
{
  in.reset();
  out.reset();
}

void MemoryStreamTestHarness::SetUp()
{
    bigBuffer = new char[BUFF_MAX]; //testing only - gets replaced.
    this->in.reset(new InputMemoryStream(bigBuffer,BUFF_MAX));
    this->out.reset(new OutputMemoryStream());
}

void MemoryStreamTestHarness::TearDown()
{
    this->in.reset();
    this->in = nullptr;

    this->out.reset();
    this->out = nullptr;
}

TEST_F(MemoryStreamTestHarness, WriteTestIntMax)
{
  int test = std::numeric_limits<int>::max();
  this->out->Write((const void*)&test,sizeof(int));

  EXPECT_EQ(this->out->GetLength(), sizeof(int));

  const char* buffer = this->out->GetBufferPtr();

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    int out = *((int*)buffer); //cast to int* and de-ref.
    EXPECT_EQ(out, test);
  }
  else
  {
    int testSwapped = ByteSwap( test );
    EXPECT_EQ((int)*buffer, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ConvWriteTestIntMax)
{
  int test = std::numeric_limits<int>::max();
  this->out->Write(test);

  EXPECT_EQ(this->out->GetLength(), sizeof(int));

  const char* buffer = this->out->GetBufferPtr();

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    int out = *((int*)buffer); //cast to int* and de-ref.
    EXPECT_EQ(out, test);
  }
  else
  {
    int testSwapped = ByteSwap( test );
    EXPECT_EQ((int)*buffer, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, WriteTestFloatMax)
{
  float test = std::numeric_limits<float>::max();
  this->out->Write((const void*)&test,sizeof(float));

  EXPECT_EQ(this->out->GetLength(), sizeof(float));

  const char* buffer = this->out->GetBufferPtr();

  float out = *((float*)buffer); //cast to int* and de-ref.
  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(out, test);
  }
  else
  {
    float testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(out, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ConvWriteTestFloatMax)
{
  float test = std::numeric_limits<float>::max();
  this->out->Write(test);

  EXPECT_EQ(this->out->GetLength(), sizeof(float));

  const char* buffer = this->out->GetBufferPtr();

  float out = *((float*)buffer); //cast to int* and de-ref.
  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(out, test);
  }
  else
  {
    float testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(out, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, WriteTestLongMax)
{
  long test = std::numeric_limits<long>::max();
  this->out->Write((const void*)&test,sizeof(long));

  EXPECT_EQ(this->out->GetLength(), sizeof(long));

  const char* buffer = this->out->GetBufferPtr();

  long out = *((long*)buffer); //cast to int* and de-ref.
  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(out, test);
  }
  else
  {
    float testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(out, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ConvWriteTestLongMax)
{
  long test = std::numeric_limits<long>::max();
  this->out->Write(test);

  EXPECT_EQ(this->out->GetLength(), sizeof(long));

  const char* buffer = this->out->GetBufferPtr();

  long out = *((long*)buffer); //cast to int* and de-ref.
  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(out, test);
  }
  else
  {
    float testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(out, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, WriteTestDoubleMax)
{
  double test = std::numeric_limits<double>::max();
  this->out->Write((const void*)&test,sizeof(double));

  EXPECT_EQ(this->out->GetLength(), sizeof(double));

  const char* buffer = this->out->GetBufferPtr();

  double out = *((double*)buffer); //cast to int* and de-ref.
  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(out, test);
  }
  else
  {
    double testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(out, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ConvWriteTestDoubleMax)
{
  double test = std::numeric_limits<double>::max();
  this->out->Write(test);

  EXPECT_EQ(this->out->GetLength(), sizeof(double));

  const char* buffer = this->out->GetBufferPtr();

  double out = *((double*)buffer); //cast to int* and de-ref.
  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(out, test);
  }
  else
  {
    double testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(out, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, WriteTestIntMin)
{
  int test = std::numeric_limits<int>::min();
  this->out->Write((const void*)&test,sizeof(int));

  EXPECT_EQ(this->out->GetLength(), sizeof(int));

  const char* buffer = this->out->GetBufferPtr();

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    int out = *((int*)buffer); //cast to int* and de-ref.
    EXPECT_EQ(out, test);
  }
  else
  {
    int testSwapped = ByteSwap( test );
    EXPECT_EQ((int)*buffer, testSwapped);
  }
}


TEST_F(MemoryStreamTestHarness, ConvWriteTestIntMin)
{
  int test = std::numeric_limits<int>::min();
  this->out->Write(test);

  EXPECT_EQ(this->out->GetLength(), sizeof(int));

  const char* buffer = this->out->GetBufferPtr();

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    int out = *((int*)buffer); //cast to int* and de-ref.
    EXPECT_EQ(out, test);
  }
  else
  {
    int testSwapped = ByteSwap( test );
    EXPECT_EQ((int)*buffer, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, WriteTestFloatMin)
{
  float test = std::numeric_limits<float>::min();
  this->out->Write((const void*)&test,sizeof(float));

  EXPECT_EQ(this->out->GetLength(), sizeof(float));

  const char* buffer = this->out->GetBufferPtr();

  float out = *((float*)buffer); //cast to int* and de-ref.
  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(out, test);
  }
  else
  {
    float testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(out, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ConvWriteTestFloatMin)
{
  float test = std::numeric_limits<float>::min();
  this->out->Write(test);

  EXPECT_EQ(this->out->GetLength(), sizeof(float));

  const char* buffer = this->out->GetBufferPtr();

  float out = *((float*)buffer); //cast to int* and de-ref.
  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(out, test);
  }
  else
  {
    float testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(out, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, WriteTestLongMin)
{
  long test = std::numeric_limits<long>::min();
  this->out->Write((const void*)&test,sizeof(long));

  EXPECT_EQ(this->out->GetLength(), sizeof(long));

  const char* buffer = this->out->GetBufferPtr();

  long out = *((long*)buffer); //cast to int* and de-ref.
  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(out, test);
  }
  else
  {
    float testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(out, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ConvWriteTestLongMin)
{
  long test = std::numeric_limits<long>::min();
  this->out->Write(test);

  EXPECT_EQ(this->out->GetLength(), sizeof(long));

  const char* buffer = this->out->GetBufferPtr();

  long out = *((long*)buffer); //cast to int* and de-ref.
  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(out, test);
  }
  else
  {
    float testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(out, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, WriteTestDoubleMin)
{
  double test = std::numeric_limits<double>::min();
  this->out->Write((const void*)&test,sizeof(double));

  EXPECT_EQ(this->out->GetLength(), sizeof(double));

  const char* buffer = this->out->GetBufferPtr();

  double out = *((double*)buffer); //cast to int* and de-ref.
  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(out, test);
  }
  else
  {
    double testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(out, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ConvWriteTestDoubleMin)
{
  double test = std::numeric_limits<double>::min();
  this->out->Write(test);

  EXPECT_EQ(this->out->GetLength(), sizeof(double));

  const char* buffer = this->out->GetBufferPtr();

  double out = *((double*)buffer); //cast to int* and de-ref.
  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(out, test);
  }
  else
  {
    double testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(out, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ReadTestIntMax)
{
  int test = std::numeric_limits<int>::max();
  int* testBuffer = &test;
  int testBufferSize = sizeof(int);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryStream(buffer, BUFF_MAX));

  int result;
  in->Read(&result, sizeof(int));

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_EQ(result, test);
  }
  else
  {
    int testSwapped = ByteSwap( test );
    EXPECT_EQ(result, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ConvReadTestIntMax)
{
  int test = std::numeric_limits<int>::max();
  int* testBuffer = &test;
  int testBufferSize = sizeof(int);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryStream(buffer, BUFF_MAX));

  int result;
  in->Read(result);

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_EQ(result, test);
  }
  else
  {
    int testSwapped = ByteSwap( test );
    EXPECT_EQ(result, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ReadTestIntMin)
{
  int test = std::numeric_limits<int>::min();
  int* testBuffer = &test;
  int testBufferSize = sizeof(int);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryStream(buffer, BUFF_MAX));

  int result;
  in->Read(&result, sizeof(int));

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_EQ(result, test);
  }
  else
  {
    int testSwapped = ByteSwap( test );
    EXPECT_EQ(result, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ConvReadTestIntMin)
{
  int test = std::numeric_limits<int>::min();
  int* testBuffer = &test;
  int testBufferSize = sizeof(int);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryStream(buffer, BUFF_MAX));

  int result;
  in->Read(result);

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_EQ(result, test);
  }
  else
  {
    int testSwapped = ByteSwap( test );
    EXPECT_EQ(result, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ReadTestLongMax)
{
  long test = std::numeric_limits<long>::max();
  long* testBuffer = &test;
  int testBufferSize = sizeof(long);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryStream(buffer, BUFF_MAX));

  long result;
  in->Read(&result, sizeof(long));

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_EQ(result, test);
  }
  else
  {
    long testSwapped = ByteSwap( test );
    EXPECT_EQ(result, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ConvReadTestLongMax)
{
  long test = std::numeric_limits<long>::max();
  long* testBuffer = &test;
  int testBufferSize = sizeof(long);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryStream(buffer, BUFF_MAX));

  long result;
  in->Read(result);

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_EQ(result, test);
  }
  else
  {
    long testSwapped = ByteSwap( test );
    EXPECT_EQ(result, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ReadTestLongMin)
{
  long test = std::numeric_limits<long>::min();
  long* testBuffer = &test;
  int testBufferSize = sizeof(long);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryStream(buffer, BUFF_MAX));

  long result;
  in->Read(&result, sizeof(long));

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_EQ(result, test);
  }
  else
  {
    long testSwapped = ByteSwap( test );
    EXPECT_EQ(result, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ConvReadTestLongMin)
{
  long test = std::numeric_limits<long>::min();
  long* testBuffer = &test;
  int testBufferSize = sizeof(long);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryStream(buffer, BUFF_MAX));

  long result;
  in->Read(result);

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_EQ(result, test);
  }
  else
  {
    long testSwapped = ByteSwap( test );
    EXPECT_EQ(result, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ReadTestFloatMax)
{
  float test = std::numeric_limits<float>::max();
  float* testBuffer = &test;
  int testBufferSize = sizeof(float);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryStream(buffer, BUFF_MAX));

  float result;
  in->Read(&result, sizeof(float));

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(result, test);
  }
  else
  {
    int testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(result, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ConvReadTestFloatMax)
{
  float test = std::numeric_limits<float>::max();
  float* testBuffer = &test;
  int testBufferSize = sizeof(float);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryStream(buffer, BUFF_MAX));

  float result;
  in->Read(result);

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(result, test);
  }
  else
  {
    int testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(result, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ReadTestFloatMin)
{
  float test = std::numeric_limits<float>::min();
  float* testBuffer = &test;
  int testBufferSize = sizeof(float);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryStream(buffer, BUFF_MAX));

  float result;
  in->Read(&result, sizeof(float));

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(result, test);
  }
  else
  {
    float testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(result, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ConvReadTestFloatMin)
{
  float test = std::numeric_limits<float>::min();
  float* testBuffer = &test;
  int testBufferSize = sizeof(float);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryStream(buffer, BUFF_MAX));

  float result;
  in->Read(result);

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(result, test);
  }
  else
  {
    float testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(result, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ReadTestDoubleMax)
{
  double test = std::numeric_limits<double>::max();
  double* testBuffer = &test;
  int testBufferSize = sizeof(double);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryStream(buffer, BUFF_MAX));

  double result;
  in->Read(&result, sizeof(double));

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(result, test);
  }
  else
  {
    double testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(result, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ConvReadTestDoubleMax)
{
  double test = std::numeric_limits<double>::max();
  double* testBuffer = &test;
  int testBufferSize = sizeof(double);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryStream(buffer, BUFF_MAX));

  double result;
  in->Read(result);

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(result, test);
  }
  else
  {
    double testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(result, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ReadTestDoubleMin)
{
  double test = std::numeric_limits<double>::min();
  double* testBuffer = &test;
  int testBufferSize = sizeof(double);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryStream(buffer, BUFF_MAX));

  double result;
  in->Read(&result, sizeof(double));

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(result, test);
  }
  else
  {
    double testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(result, testSwapped);
  }
}

TEST_F(MemoryStreamTestHarness, ConvReadTestDoubleMin)
{
  double test = std::numeric_limits<double>::min();
  double* testBuffer = &test;
  int testBufferSize = sizeof(double);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryStream(buffer, BUFF_MAX));

  double result;
  in->Read(result);

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(result, test);
  }
  else
  {
    double testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(result, testSwapped);
  }
}


/* Can't use Player - works with bit streams
TEST_F(MemoryStreamTestHarness,serialiseAndDeserialise)
{
  PlayerPtr testInput(Player::StaticCreate());
  PlayerPtr testOutput(Player::StaticCreate());

  EXPECT_TRUE(*testInput == *testOutput); //expect constructed objs to be the same.

  // change this one a bit so I know the changes have copied over.
  testOutput->SetPlayerId(20);

  //OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState
  uint32_t state = 0x000F;

  EXPECT_FALSE(*testInput == *testOutput); //with one changed should be different.

  //write it into a buffer.
  testOutput->Write(*out,state);

  // ... imagine networking goes on and we get an
  // update from our server.
  testInput->Read(*in);

  // expect these to now be the same.
  EXPECT_TRUE(*testInput == *testOutput); //expect constructed objs to be the same.
} */

TEST_F(MemoryStreamTestHarness,serialiseAndDeserialise)
{
  TestObject testInput;
  TestObject testOutput;

  EXPECT_TRUE(testInput == testOutput); //expect constructed objs to be the same.

  // change this one a bit so I know the changes have copied over.
  testOutput.setA(20);

  EXPECT_FALSE(testInput == testOutput); //with one changed should be different.

  //write it into a buffer.
  testOutput.Write(*out);

  // ... imagine networking goes on and we get an
  // actually we're connecting the output buffer to the input.
  // copy the buffer first (or we get double de-allocation)
  int copyLen = out->GetLength();
  char* copyBuff = new char[copyLen];
  memcpy(copyBuff, out->GetBufferPtr(), copyLen);

  this->in.reset(new InputMemoryStream(copyBuff, copyLen));

  // update from our server.
  testInput.Read(*in);

  // expect these to now be the same.
  EXPECT_TRUE(testInput == testOutput); //expect constructed objs to be the same.

  if((testInput == testOutput) == false)
  {
    std::cout << testInput.getA() << ", " << testInput.getB() << ", " << testInput.getName() << std::endl;
    std::cout << testOutput.getA() << ", " << testOutput.getB() << ", " << testOutput.getName() << std::endl;
  }
}

TEST_F(MemoryStreamTestHarness,serialiseAndDeserialise2)
{
  TestObject testInput;
  TestObject testOutput;

  EXPECT_TRUE(testInput == testOutput); //expect constructed objs to be the same.

  // change this one a bit so I know the changes have copied over.
  testOutput.setA(20);
  testOutput.setB(12.0f);
  testOutput.setName("Donkey");

  EXPECT_FALSE(testInput == testOutput); //with one changed should be different.

  //write it into a buffer.
  testOutput.Write(*out);

  // ... imagine networking goes on and we get an
  // actually we're connecting the output buffer to the input.
  // copy the buffer first (or we get double de-allocation)
  int copyLen = out->GetLength();
  char* copyBuff = new char[copyLen];
  memcpy(copyBuff, out->GetBufferPtr(), copyLen);

  this->in.reset(new InputMemoryStream(copyBuff, copyLen));

  // update from our server.
  testInput.Read(*in);

  // expect these to now be the same.
  EXPECT_TRUE(testInput == testOutput); //expect constructed objs to be the same.

  if((testInput == testOutput) == false)
  {
    std::cout << testInput.getA() << ", " << testInput.getB() << ", " << testInput.getName() << std::endl;
    std::cout << testOutput.getA() << ", " << testOutput.getB() << ", " << testOutput.getName() << std::endl;
  }
}
