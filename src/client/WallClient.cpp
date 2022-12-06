#include "WallClient.h"
#include "TextureManager.h"
#include "GameObjectRegistry.h"

#include "InputMemoryBitStream.h"
#include "OutputMemoryBitStream.h"
#include "NetworkManagerClient.h"

#include "StringUtils.h"

WallClient::WallClient() :
	mTimeLocationBecameOutOfSync(0.f),
	mTimeVelocityBecameOutOfSync(0.f)
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("box"));
}

void WallClient::HandleDying()
{
	Wall::HandleDying();
}


void WallClient::Update()
{
	//for now, we don't simulate any movement on the client side
	//we only move when the server tells us to move
}

void WallClient::Read(InputMemoryBitStream& inInputStream)
{
	bool stateBit;

	uint32_t readState = 0;

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		uint32_t WallId;
		inInputStream.Read(WallId);
		SetWallId(WallId);
		readState |= ECRS_WallId;
	}

	float replicatedRotation;
	float replicatedScale;
	Vector3 replicatedLocation;
	Vector3 replicatedVelocity;

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		inInputStream.Read(replicatedVelocity.mX);
		inInputStream.Read(replicatedVelocity.mY);

		SetVelocity(replicatedVelocity);

		inInputStream.Read(replicatedLocation.mX);
		inInputStream.Read(replicatedLocation.mY);

		SetLocation(replicatedLocation);

		inInputStream.Read(replicatedRotation);
		SetRotation(replicatedRotation);

		inInputStream.Read(replicatedScale);
		SetScale(replicatedScale);

		readState |= ECRS_Pose;
	}

	//inInputStream.Read( stateBit );
	//if( stateBit )
	//{
	//	inInputStream.Read( stateBit );
	//	mThrustDir = stateBit ? 1.f : -1.f;
	//}
	//else
	//{
	//	mThrustDir = 0.f;
	//}

	//inInputStream.Read( stateBit );
	//if( stateBit )
	//{
	//	Vector3 color;
	//	inInputStream.Read( color );
	//	SetColor( color );
	//	readState |= ECRS_Color;
	//}

	//if( GetWallId() == NetworkManagerClient::sInstance->GetWallId() )
	//{
	//	//did we get health? if so, tell the hud!
	//	if( ( readState & ECRS_Health ) != 0 )
	//	{
	//	//	HUD::sInstance->SetPlayerHealth( mHealth );
	//	}
	//}
}