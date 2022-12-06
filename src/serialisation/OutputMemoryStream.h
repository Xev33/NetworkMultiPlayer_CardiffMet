#ifndef OUTPUT_MEMORY_STREAM_H_
#define OUTPUT_MEMORY_STREAM_H_

#include <cstdlib>
#include <cstdint>
#include <type_traits>

#include "SerialisationCommon.h"
#include "Fixed.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "ByteSwap.h"

class GameObject;
class LinkingContext;

#include <vector>
#include <string>
#include <cstring>

class OutputMemoryStream
{
public:
	OutputMemoryStream() :
	mBuffer ( nullptr ),
	mHead ( 0 ),
	mCapacity ( 0 ),
	mLinkingContext( nullptr )
	{ ReallocBuffer( 32 ); }

	~OutputMemoryStream();

	//get a pointer to the data in the stream
	const 	char*		GetBufferPtr()	const	{ return mBuffer; }
			uint32_t	GetLength()		const	{ return mHead; }

			void		Write( const void* inData,
								size_t inByteCount );

	template< typename T > void Write( T inData )
	{
		static_assert( std::is_arithmetic< T >::value ||
					  std::is_enum< T >::value,
					  "Generic Write only supports primitive data types" );

		if( STREAM_ENDIANNESS == PLATFORM_ENDIANNESS )
		{
			Write( &inData, sizeof( inData ) );
		}
		else
		{
			T swappedData = ByteSwap( inData );
			Write( &swappedData, sizeof( swappedData ) );
		}

	}

	void Write( const std::vector< int >& inIntVector )
	{
		size_t elementCount = inIntVector.size();
		Write( elementCount );
		Write( inIntVector.data(), elementCount * sizeof( int ) );
	}

	template< typename T >
	void Write( const std::vector< T >& inVector )
	{
		uint32_t elementCount = inVector.size();
		Write( elementCount );
		for( const T& element : inVector )
		{
			Write( element );
		}
	}

	void Write( const std::string& inString )
	{
		size_t elementCount = inString.size() ;
		Write( elementCount );
		Write( inString.data(), elementCount * sizeof( char ) );
	}

	void Write( const GameObject* inGameObject );



private:
			void		ReallocBuffer( uint32_t inNewLength );

	char*		mBuffer;
	uint32_t	mHead;
	uint32_t	mCapacity;

	LinkingContext* mLinkingContext;
};

#endif
