#ifndef INPUT_MEMORY_STREAM_H_
#define INPUT_MEMORY_STREAM_H_

#include <cstdlib>
#include <cstdint>
#include <type_traits>

#include "SerialisationCommon.h"
#include "BitMan.h"
#include "Fixed.h"

class Vector3;
class Quaternion;

#include <cmath>
#include <vector>

class GameObject;
class LinkingContext;

class InputMemoryStream
{
private:
	char*		mBuffer;
	uint32_t	mHead;
	uint32_t	mCapacity;

	LinkingContext* mLinkingContext;

public:
	InputMemoryStream( char* inBuffer, uint32_t inByteCount ) :
	mBuffer( inBuffer ),
	mHead( 0 ),
	mCapacity( inByteCount ),
	mLinkingContext( nullptr ) {}

	~InputMemoryStream();

	uint32_t		GetRemainingDataSize() const
					{ return mCapacity - mHead; }

	void		Read( void* outData, uint32_t inByteCount );
  void    Read( GameObject*& outGameObject );

	template< typename T > void Read( T& outData )
	{
		static_assert( std::is_arithmetic< T >::value ||
					   std::is_enum< T >::value,
					   "Generic Read only supports primitive data types" );
		Read( &outData, sizeof( outData ) );
	}

	template< typename T >
	void Read( std::vector< T >& outVector )
	{
		size_t elementCount;
		Read( elementCount );
		outVector.resize( elementCount );
		for( const T& element : outVector )
		{
			Read( element );
		}
	}
};

#endif
