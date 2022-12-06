#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "MemoryBitStreamTestHarness.h"
#include "TestObject.h"
#include "Maths.h"
#include "Colors.h"
#include "ByteSwap.h"
#include "Player.h"

#include <iostream>
#include <fstream>
#include <thread>

#include "PlayerClient.h"

// Required to test player
#include "RenderManager.h"
#include "TextureManager.h"
#include "WindowManager.h"
#include "GraphicsDriver.h"

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */


MemoryBitStreamTestHarenss::MemoryBitStreamTestHarenss()
{
  in = nullptr;
  out = nullptr;
}

MemoryBitStreamTestHarenss::~MemoryBitStreamTestHarenss()
{
  in.reset();
  out.reset();
}

void MemoryBitStreamTestHarenss::SetUp()
{
    bigBuffer = new char[BUFF_MAX]; //testing only - gets replaced.
    this->in.reset(new InputMemoryBitStream(bigBuffer,BUFF_MAX));
    this->out.reset(new OutputMemoryBitStream());
}

void MemoryBitStreamTestHarenss::TearDown()
{
    this->in.reset();
    this->in = nullptr;

    this->out.reset();
    this->out = nullptr;
}

TEST_F(MemoryBitStreamTestHarenss, WriteTestIntMax)
{
  int test = std::numeric_limits<int>::max();
  this->out->WriteBytes((const void*)&test,sizeof(int));

  EXPECT_EQ(this->out->GetByteLength(), sizeof(int));

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

TEST_F(MemoryBitStreamTestHarenss, ConvWriteTestIntMax)
{
  int test = std::numeric_limits<int>::max();
  this->out->Write(test);

  EXPECT_EQ(this->out->GetByteLength(), sizeof(int));

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

TEST_F(MemoryBitStreamTestHarenss, WriteTestFloatMax)
{
  float test = std::numeric_limits<float>::max();
  this->out->WriteBytes((const void*)&test,sizeof(float));

  EXPECT_EQ(this->out->GetByteLength(), sizeof(float));

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

TEST_F(MemoryBitStreamTestHarenss, ConvWriteTestFloatMax)
{
  float test = std::numeric_limits<float>::max();
  this->out->Write(test);

  EXPECT_EQ(this->out->GetByteLength(), sizeof(float));

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

TEST_F(MemoryBitStreamTestHarenss, WriteTestLongMax)
{
  long test = std::numeric_limits<long>::max();
  this->out->WriteBytes((const void*)&test,sizeof(long));

  EXPECT_EQ(this->out->GetByteLength(), sizeof(long));

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

TEST_F(MemoryBitStreamTestHarenss, ConvWriteTestLongMax)
{
  long test = std::numeric_limits<long>::max();
  this->out->Write(test);

  EXPECT_EQ(this->out->GetByteLength(), sizeof(long));

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

TEST_F(MemoryBitStreamTestHarenss, WriteTestDoubleMax)
{
  double test = std::numeric_limits<double>::max();
  this->out->WriteBytes((const void*)&test,sizeof(double));

  EXPECT_EQ(this->out->GetByteLength(), sizeof(double));

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


TEST_F(MemoryBitStreamTestHarenss, ConvWriteTestDoubleMax)
{
  double test = std::numeric_limits<double>::max();
  this->out->Write(test);

  EXPECT_EQ(this->out->GetByteLength(), sizeof(double));

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

TEST_F(MemoryBitStreamTestHarenss, WriteTestIntMin)
{
  int test = std::numeric_limits<int>::min();
  this->out->WriteBytes((const void*)&test,sizeof(int));

  EXPECT_EQ(this->out->GetByteLength(), sizeof(int));

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

TEST_F(MemoryBitStreamTestHarenss, ConvWriteTestIntMin)
{
  int test = std::numeric_limits<int>::min();
  this->out->Write(test);

  EXPECT_EQ(this->out->GetByteLength(), sizeof(int));

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

TEST_F(MemoryBitStreamTestHarenss, WriteTestFloatMin)
{
  float test = std::numeric_limits<float>::min();
  this->out->WriteBytes((const void*)&test,sizeof(float));

  EXPECT_EQ(this->out->GetByteLength(), sizeof(float));

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

TEST_F(MemoryBitStreamTestHarenss, ConvWriteTestFloatMin)
{
  float test = std::numeric_limits<float>::min();
  this->out->Write(test);

  EXPECT_EQ(this->out->GetByteLength(), sizeof(float));

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

TEST_F(MemoryBitStreamTestHarenss, WriteTestLongMin)
{
  long test = std::numeric_limits<long>::min();
  this->out->WriteBytes((const void*)&test,sizeof(long));

  EXPECT_EQ(this->out->GetByteLength(), sizeof(long));

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

TEST_F(MemoryBitStreamTestHarenss, ConvWriteTestLongMin)
{
  long test = std::numeric_limits<long>::min();
  this->out->Write(test);

  EXPECT_EQ(this->out->GetByteLength(), sizeof(long));

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

TEST_F(MemoryBitStreamTestHarenss, ConvWriteTestDoubleMin)
{
  double test = std::numeric_limits<double>::min();
  this->out->Write(test);

  EXPECT_EQ(this->out->GetByteLength(), sizeof(double));

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

TEST_F(MemoryBitStreamTestHarenss, ReadTestIntMax)
{
  int test = std::numeric_limits<int>::max();
  int* testBuffer = &test;
  int testBufferSize = sizeof(int);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

  int result;
  in->ReadBytes(&result, sizeof(int));

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

TEST_F(MemoryBitStreamTestHarenss, ConvReadTestIntMax)
{
  int test = std::numeric_limits<int>::max();
  int* testBuffer = &test;
  int testBufferSize = sizeof(int);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

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

TEST_F(MemoryBitStreamTestHarenss, ReadTestIntMin)
{
  int test = std::numeric_limits<int>::min();
  int* testBuffer = &test;
  int testBufferSize = sizeof(int);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

  int result;
  in->ReadBytes(&result, sizeof(int));

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

TEST_F(MemoryBitStreamTestHarenss, ConvReadTestIntMin)
{
  int test = std::numeric_limits<int>::min();
  int* testBuffer = &test;
  int testBufferSize = sizeof(int);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

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

TEST_F(MemoryBitStreamTestHarenss, ReadTestLongMax)
{
  long test = std::numeric_limits<long>::max();
  long* testBuffer = &test;
  int testBufferSize = sizeof(long);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

  long result;
  in->ReadBytes(&result, sizeof(long));

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

TEST_F(MemoryBitStreamTestHarenss, ConvReadTestLongMax)
{
  long test = std::numeric_limits<long>::max();
  long* testBuffer = &test;
  int testBufferSize = sizeof(long);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

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

TEST_F(MemoryBitStreamTestHarenss, ReadTestLongMin)
{
  long test = std::numeric_limits<long>::min();
  long* testBuffer = &test;
  int testBufferSize = sizeof(long);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

  long result;
  in->ReadBytes(&result, sizeof(long));

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

TEST_F(MemoryBitStreamTestHarenss, ConvReadTestLongMin)
{
  long test = std::numeric_limits<long>::min();
  long* testBuffer = &test;
  int testBufferSize = sizeof(long);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

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

TEST_F(MemoryBitStreamTestHarenss, ReadTestFloatMax)
{
  float test = std::numeric_limits<float>::max();
  float* testBuffer = &test;
  int testBufferSize = sizeof(float);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

  float result;
  in->ReadBytes(&result, sizeof(float));

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

TEST_F(MemoryBitStreamTestHarenss, ConvReadTestFloatMax)
{
  float test = std::numeric_limits<float>::max();
  float* testBuffer = &test;
  int testBufferSize = sizeof(float);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

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

TEST_F(MemoryBitStreamTestHarenss, ReadTestFloatMin)
{
  float test = std::numeric_limits<float>::min();
  float* testBuffer = &test;
  int testBufferSize = sizeof(float);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

  float result;
  in->ReadBytes(&result, sizeof(float));

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


TEST_F(MemoryBitStreamTestHarenss, ConvReadTestFloatMin)
{
  float test = std::numeric_limits<float>::min();
  float* testBuffer = &test;
  int testBufferSize = sizeof(float);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

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

TEST_F(MemoryBitStreamTestHarenss, ReadTestDoubleMax)
{
  double test = std::numeric_limits<double>::max();
  double* testBuffer = &test;
  int testBufferSize = sizeof(double);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

  double result;
  in->ReadBytes(&result, sizeof(double));

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


TEST_F(MemoryBitStreamTestHarenss, ConvReadTestDoubleMax)
{
  double test = std::numeric_limits<double>::max();
  double* testBuffer = &test;
  int testBufferSize = sizeof(double);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

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

TEST_F(MemoryBitStreamTestHarenss, ReadTestDoubleMin)
{
  double test = std::numeric_limits<double>::min();
  double* testBuffer = &test;
  int testBufferSize = sizeof(double);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

  double result;
  in->ReadBytes(&result, sizeof(double));

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


TEST_F(MemoryBitStreamTestHarenss, ConvReadTestDoubleMin)
{
  double test = std::numeric_limits<double>::min();
  double* testBuffer = &test;
  int testBufferSize = sizeof(double);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

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

TEST_F(MemoryBitStreamTestHarenss, ReadTestBool)
{
  bool test = true;
  bool* testBuffer = &test;
  int testBufferSize = sizeof(bool);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

  bool result;
  in->ReadBytes(&result, sizeof(bool));

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(result, test);
  }
  else
  {
    bool testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(result, testSwapped);
  }
}

TEST_F(MemoryBitStreamTestHarenss, ConvReadTestBool)
{
  bool test = true;
  bool* testBuffer = &test;
  int testBufferSize = sizeof(bool);

  static const int BUFF_MAX = 32;
  char* buffer = new char[BUFF_MAX]; //got to be dynamic!

  //overkill perhaps, but gets a buffer that InputStream can take
  //ownership of (i.e. delete) and puts into int a single int.
  memcpy(buffer, testBuffer, testBufferSize);

  this->in.reset(new InputMemoryBitStream(buffer, BUFF_MAX));

  bool result;
  in->Read(result);

  if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
  {
    EXPECT_FLOAT_EQ(result, test);
  }
  else
  {
    bool testSwapped = ByteSwap( test );
    EXPECT_FLOAT_EQ(result, testSwapped);
  }
}

TEST_F(MemoryBitStreamTestHarenss, StringReadWrite)
{
  std::string testInput;
  std::string testOutput;

  EXPECT_TRUE(testInput == testOutput); //expect constructed objs to be the same.

  // change this one a bit so I know the changes have copied over.
  testOutput = "Hello World!";

  EXPECT_FALSE(testInput == testOutput); //with one changed should be different.

  //write it into a buffer.
  out->Write(testOutput);

    // ... imagine networking goes on and we get an
  // actually we're connecting the output buffer to the input.
  // copy the buffer first (or we get double de-allocation)
  int copyLen = out->GetByteLength();
  char* copyBuff = new char[copyLen];
  memcpy(copyBuff, out->GetBufferPtr(), copyLen);

  this->in.reset(new InputMemoryBitStream(copyBuff, copyLen));

  // update from our server.
  in->Read(testInput);

  // expect these to now be the same.
  EXPECT_TRUE(testInput == testOutput); //expect constructed objs to be the same.
}

TEST_F(MemoryBitStreamTestHarenss, VectorReadWrite)
{
  Vector3 testInput;
  Vector3 testOutput;

  EXPECT_TRUE(Maths::Is3DVectorEqual(testInput,testOutput)); //expect constructed objs to be the same.

  // change this one a bit so I know the changes have copied over.
  testOutput.Set(1.1f, 2.2f, 3.3f);

  EXPECT_FALSE(Maths::Is3DVectorEqual(testInput,testOutput)); //with one changed should be different.

  //write it into a buffer.
  out->Write(testOutput);

    // ... imagine networking goes on and we get an
  // actually we're connecting the output buffer to the input.
  // copy the buffer first (or we get double de-allocation)
  int copyLen = out->GetByteLength();
  char* copyBuff = new char[copyLen];
  memcpy(copyBuff, out->GetBufferPtr(), copyLen);

  this->in.reset(new InputMemoryBitStream(copyBuff, copyLen));

  // update from our server.
  in->Read(testInput);

  // expect these to now be the same.
  EXPECT_TRUE(Maths::Is3DVectorEqual(testInput,testOutput)); //expect constructed objs to be the same.
}
/*
TEST_F(MemoryBitStreamTestHarenss,serialiseAndDeserialisePlayer)
{
    // Creating a player now requires SDL inc. rendering etc. 
    // Setup SDL (normall Engine or one of its children do this.)
  const int SDL_OKAY = 0;

	SDL_SetMainReady(); //don't use sdl_main
	int sdlStatus = SDL_Init(SDL_INIT_EVERYTHING);
	
	if (sdlStatus != SDL_OKAY)
		throw "SDL init error";

  WindowManager::StaticInit();
  GraphicsDriver::StaticInit( WindowManager::sInstance->GetMainWindow() );

  TextureManager::StaticInit();
	RenderManager::StaticInit();

  PlayerPtr testOutput(static_cast<Player*>(Player::StaticCreate()));
  PlayerClientPtr testInput(static_cast<PlayerClient*>(PlayerClient::StaticCreate().get()));

  EXPECT_TRUE(*testOutput == *testInput); //expect constructed objs to be the same.
                                          //TestInput should downcast to a Player

  // change this one a bit so I know the changes have copied over.
  testOutput->SetPlayerId(20);

  EXPECT_FALSE(*testOutput == *testInput); //with one changed should be different.


  //OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState
  uint32_t state = 0x000F;

  EXPECT_FALSE(*testInput == *testOutput); //with one changed should be different.

  //write it into a buffer.
  testOutput->Write(*out,state);

   // ... imagine networking goes on and we get an
  // actually we're connecting the output buffer to the input.
  // copy the buffer first (or we get double de-allocation)
  int copyLen = out->GetByteLength();
  char* copyBuff = new char[copyLen];
  memcpy(copyBuff, out->GetBufferPtr(), copyLen);

  this->in.reset(new InputMemoryBitStream(copyBuff, copyLen));

  // update from our server.
  testInput->Read(*in);

  // expect these to now be the same.
  EXPECT_TRUE(*testOutput == *testInput); //expect read object to match written 
  SDL_Quit();
}
*/