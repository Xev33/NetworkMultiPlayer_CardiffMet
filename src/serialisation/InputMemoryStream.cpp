
#include "InputMemoryStream.h"

#include "Quaternion.h"
#include "Vector3.h"
#include "LinkingContext.h"

#include <cstring>

InputMemoryStream::~InputMemoryStream()
{
	std::free( mBuffer );
	mBuffer = nullptr;
}

void InputMemoryStream::Read( void* outData,
							  uint32_t inByteCount )
{
	uint32_t resultHead = mHead + inByteCount;
	if( resultHead > mCapacity )
	{
		//handle error, no data to read!
		//...
	}

	std::memcpy( outData, mBuffer + mHead, inByteCount );

	mHead = resultHead;
}

	void InputMemoryStream::Read( GameObject*& outGameObject )
	{
		uint32_t networkId;
		Read( networkId );
		outGameObject = mLinkingContext->GetGameObject( networkId );
	}
