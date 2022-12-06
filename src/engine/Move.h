#ifndef MOVE_H
#define MOVE_H

#include "InputState.h"
#include "InputMemoryBitStream.h"
#include "OutputMemoryBitStream.h"

#include <memory>
using std::shared_ptr;

class Move
{
public:

	Move() :
		mTimestamp( 0.0f ),
		mDeltaTime( 0.0f )
		{}

	Move( const InputState& inInputState, float inTimestamp, float inDeltaTime ) :
		mInputState( inInputState ),
		mTimestamp( inTimestamp ),
		mDeltaTime( inDeltaTime )
	{}


	const InputState&	GetInputState()	const		{ return mInputState; }
	float				GetTimestamp()	const		{ return mTimestamp; }
	float				GetDeltaTime()	const		{ return mDeltaTime; }

	void setInputState(InputState& inInputState)	{ mInputState = inInputState; }
	void				SetTimestamp(float inTimeStamp)	{ mTimestamp = inTimeStamp; }
	void				SetDeltaTime(float inDetlaTime)	{ mDeltaTime = inDetlaTime; }

	bool Write( OutputMemoryBitStream& inOutputStream ) const;
	bool Read( InputMemoryBitStream& inInputStream );

private:
	InputState	mInputState;
	float		mTimestamp;
	float		mDeltaTime;

};

typedef shared_ptr< Move >	MovePtr;

#endif
