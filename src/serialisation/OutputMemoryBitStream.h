#ifndef OUTPUT_MEMORY_BIT_STREAM_H
#define OUTPUT_MEMORY_BIT_STREAM_H

#include <cstdint>
#include <cstdlib>
#include <string>

class GameObject;

#include "SerialisationCommon.h"
#include "Fixed.h"
#include "BitMan.h"

class Vector3;
class Quaternion;

class OutputMemoryBitStream
{
private:
	void		ReallocBuffer( uint32_t inNewBitCapacity );

	char*		mBuffer;
	uint32_t	mBitHead;
	uint32_t	mBitCapacity;

public:
	OutputMemoryBitStream() :
		mBuffer(nullptr),
		mBitHead(0)
		{
			ReallocBuffer( 1500 * 8 );
		}

	~OutputMemoryBitStream();

	void		WriteBits( uint8_t inData, uint32_t inBitCount );
	void		WriteBits( const void* inData, uint32_t inBitCount );

	const 	char*	GetBufferPtr()		const	{ return mBuffer; }
	uint32_t		GetBitLength()		const	{ return mBitHead; }
	uint32_t		GetByteLength()		const	{ return ( mBitHead + 7 ) >> 3; }

	void WriteBytes( const void* inData, uint32_t inByteCount )	{ WriteBits( inData, inByteCount << 3 ); }

	/*
	void Write( uint32_t inData, uint32_t inBitCount = 32 )	{ WriteBits( &inData, inBitCount ); }
	void Write( int inData, uint32_t inBitCount = 32 )		{ WriteBits( &inData, inBitCount ); }
	void Write( float inData )								{ WriteBits( &inData, 32 ); }

	void Write( uint16_t inData, uint32_t inBitCount = 16 )	{ WriteBits( &inData, inBitCount ); }
	void Write( int16_t inData, uint32_t inBitCount = 16 )	{ WriteBits( &inData, inBitCount ); }

	void Write( uint8_t inData, uint32_t inBitCount = 8 )	{ WriteBits( &inData, inBitCount ); }
	*/

	template< typename T >
	void Write( T inData, uint32_t inBitCount = sizeof( T ) * 8 )
	{
		static_assert( std::is_arithmetic< T >::value ||
					  std::is_enum< T >::value,
					  "Generic Write only supports primitive data types" );
		WriteBits( &inData, inBitCount );
	}

	void 		Write( bool inData )								{ WriteBits( &inData, 1 ); }

	void		Write( const Vector3& inVector );
	void		Write( const Quaternion& inQuat );

	void Write( const std::string& inString )
	{
		uint32_t elementCount = static_cast< uint32_t >( inString.size() );
		Write( elementCount );
		for( const auto& element : inString )
		{
			Write( element );
		}
	}
};

#endif
