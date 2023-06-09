#include "GoalClient.h"
#include "TextureManager.h"
#include "GameObjectRegistry.h"

#include "InputMemoryBitStream.h"
#include "OutputMemoryBitStream.h"
#include "NetworkManagerClient.h"

#include "StringUtils.h"

GoalClient::GoalClient() :
	mTimeLocationBecameOutOfSync( 0.f ),
	mTimeVelocityBecameOutOfSync( 0.f )
{
	mSpriteComponent.reset( new SpriteComponent( this ) );
	mSpriteComponent->SetTexture( TextureManager::sInstance->GetTexture( "goal" ) );
}

void GoalClient::HandleDying()
{
	Goal::HandleDying();
}

void GoalClient::Read( InputMemoryBitStream& inInputStream )
{
	bool stateBit;

	uint32_t readState = 0;

	inInputStream.Read( stateBit );
	if( stateBit )
	{
		uint32_t GoalId;
		inInputStream.Read(GoalId);
		SetGoalId(GoalId);
		readState |= ECRS_GoalId;
	}

	float replicatedScale;
	Vector3 replicatedLocation;

	inInputStream.Read( stateBit );
	if( stateBit )
	{

		inInputStream.Read( replicatedLocation.mX );
		inInputStream.Read( replicatedLocation.mY );

		SetLocation( replicatedLocation );

		inInputStream.Read(replicatedScale);
		SetScale(replicatedScale);

		readState |= ECRS_Pose;
	}
}