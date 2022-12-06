#include "InputMemoryBitStream.h"

#include "Quaternion.h"
#include "Vector3.h"

InputMemoryBitStream::~InputMemoryBitStream()
{
	if( mIsBufferOwner )
	{
		free( mBuffer );
	};
}

void InputMemoryBitStream::Read( Vector3& outVector )
{
	Read( outVector.mX );
	Read( outVector.mY );
	Read( outVector.mZ );
}

void InputMemoryBitStream::ReadBits( uint8_t& outData, uint32_t inBitCount )
{
	uint32_t byteOffset = mBitHead >> 3;
	uint32_t bitOffset = mBitHead & 0x7;

	outData = static_cast< uint8_t >( mBuffer[ byteOffset ] ) >> bitOffset;

	uint32_t bitsFreeThisByte = 8 - bitOffset;
	if( bitsFreeThisByte < inBitCount )
	{
		//we need another byte
		outData |= static_cast< uint8_t >( mBuffer[ byteOffset + 1 ] ) << bitsFreeThisByte;
	}

	//don't forget a mask so that we only read the bit we wanted...
	outData &= ( ~( 0x00ff << inBitCount ) );

	mBitHead += inBitCount;
}

void InputMemoryBitStream::ReadBits( void* outData, uint32_t inBitCount )
{
	uint8_t* destByte = reinterpret_cast< uint8_t* >( outData );
	//write all the bytes
	while( inBitCount > 8 )
	{
		ReadBits( *destByte, 8 );
		++destByte;
		inBitCount -= 8;
	}
	//write anything left
	if( inBitCount > 0 )
	{
		ReadBits( *destByte, inBitCount );
	}
}

void InputMemoryBitStream::Read( Quaternion& outQuat )
{
	float precision = ( 2.f / 65535.f );

	uint32_t f = 0;

	Read( f, 16 );
	outQuat.mX = ConvertFromFixed( f, -1.f, precision );
	Read( f, 16 );
	outQuat.mY = ConvertFromFixed( f, -1.f, precision );
	Read( f, 16 );
	outQuat.mZ = ConvertFromFixed( f, -1.f, precision );

	outQuat.mW = sqrtf( 1.f -
					   (outQuat.mX * outQuat.mX +
					    outQuat.mY * outQuat.mY +
					    outQuat.mZ * outQuat.mZ));
	bool isNegative;
	Read( isNegative );

	if( isNegative )
	{
		outQuat.mW *= -1;
	}
}
