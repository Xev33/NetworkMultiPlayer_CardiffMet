#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"
#include "Maths.h"

#include "ByteSwapTestHarness.h"

#include <iostream>
#include <fstream>
#include <thread>

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */

ByteSwapTestHarness::ByteSwapTestHarness()
{

}

ByteSwapTestHarness::~ByteSwapTestHarness()
{

}

void ByteSwapTestHarness::SetUp()
{

}

void ByteSwapTestHarness::TearDown()
{

}

TEST_F(ByteSwapTestHarness,SwapIntTest)
{
    int32_t test = 0x12345678;
    // 0x78563412 - each hex value is a byte, so the swap
    // is easy to work out.
    int32_t answer = 0x78563412;

    //printf( "swapped 0x%x is 0x%x\n", test, ByteSwap( test ) );

    int32_t result = ByteSwap(test);

    EXPECT_EQ(answer,result);
}

TEST_F(ByteSwapTestHarness,SwapFloatTest)
{
    float floatTest = 1.1f;
    // 0x3f8ccccd - each hex value is a byte, so the swap
    // is easy to work out.
    uint32_t result = 0xcdcc8c3f;

    float swapped = ByteSwap(floatTest);

    EXPECT_FALSE(Maths::FP_EQUAL(swapped, floatTest));

    printf( "swapped %f is %f\n", floatTest, swapped );

    // Type TypeAliaser essentially changes the type.
    int32_t fTest = TypeAliaser< float, uint32_t >( floatTest ).Get();
    int32_t swp = TypeAliaser< float, uint32_t >( ByteSwap( floatTest ) ).Get();
    printf( "swapped 0x%x is 0x%x\n", fTest, swp );

    EXPECT_EQ(swp,result);
}
