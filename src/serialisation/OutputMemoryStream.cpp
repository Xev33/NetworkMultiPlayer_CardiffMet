#include "OutputMemoryStream.h"

#include "LinkingContext.h"

#include <algorithm>

OutputMemoryStream::~OutputMemoryStream()
{
	std::free( mBuffer );
	mBuffer = nullptr;
}

void OutputMemoryStream::ReallocBuffer( uint32_t inNewLength )
{
	mBuffer = static_cast< char* >( std::realloc( mBuffer, inNewLength ) );
	//handle realloc failure
	//...
	mCapacity = inNewLength;
}

void OutputMemoryStream::Write( const void* inData,
								size_t inByteCount )
{
	//make sure we have space...
	uint32_t resultHead = mHead + static_cast< uint32_t >( inByteCount );
	if( resultHead > mCapacity )
	{
		ReallocBuffer( std::max( mCapacity * 2, resultHead ) );
	}

	//copy into buffer at head
	std::memcpy( mBuffer + mHead, inData, inByteCount );

	//increment head for next write
	mHead = resultHead;
}

void OutputMemoryStream::Write( const GameObject* inGameObject )
{
	uint32_t networkId = mLinkingContext->GetNetworkId( const_cast< GameObject* >( inGameObject ), false );
	Write( networkId );
}
