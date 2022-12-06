#include "WallClient.h"
#include "TextureManager.h"
#include "GameObjectRegistry.h"

#include "InputMemoryBitStream.h"
#include "OutputMemoryBitStream.h"
#include "NetworkManagerClient.h"

#include "StringUtils.h"

WallClient::WallClient() :
	mTimeLocationBecameOutOfSync( 0.f ),
	mTimeVelocityBecameOutOfSync( 0.f )
{
	mSpriteComponent.reset( new SpriteComponent( this ) );
	mSpriteComponent->SetTexture( TextureManager::sInstance->GetTexture( "box" ) );
}

void WallClient::HandleDying()
{
	Wall::HandleDying();
}

void WallClient::Update()
{
}

void WallClient::Read( InputMemoryBitStream& inInputStream )
{
	bool stateBit;

	uint32_t readState = 0;

	inInputStream.Read( stateBit );
	if( stateBit )
	{
		uint32_t WallId;
		inInputStream.Read( WallId );
		SetWallId( WallId );
		readState |= ECRS_WallId;
	}

	Vector3 replicatedPosition;

	inInputStream.Read( stateBit );
	if( stateBit )
	{
		inInputStream.Read(replicatedPosition.mX );
		inInputStream.Read(replicatedPosition.mY );

		SetLocation(replicatedPosition);

		readState |= ECRS_Pose;
	}

	inInputStream.Read( stateBit );
}