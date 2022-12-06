#include "Wall.h"
#include "InputMemoryBitStream.h"
#include "OutputMemoryBitStream.h"
#include "Maths.h"
#include "Player.h"

//zoom hardcoded at 100...if we want to lock players on screen, this could be calculated from zoom
const float HALF_WORLD_HEIGHT = 3.6f;
const float HALF_WORLD_WIDTH = 6.4f;

Wall::Wall() : mHealth(1)
{
	mVelocity.mX = 0;
	mVelocity.mY = 0;
	mVelocity.mZ = 0;
}

Wall::Wall(Vector3 dir) : mVelocity(dir), mHealth(1)
{
	this->SetCollisionRadius(0.5f);
}

uint32_t Wall::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & ECRS_WallId)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(GetWallId());

		writtenState |= ECRS_WallId;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & ECRS_Pose)
	{
		inOutputStream.Write((bool)true);

		Vector3 location = GetLocation();
		inOutputStream.Write(location.mX);
		inOutputStream.Write(location.mY);

		inOutputStream.Write(GetScale());

		writtenState |= ECRS_Pose;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}
	return writtenState;
}

bool Wall::operator==(Wall& other)
{
	if (!GameObject::operator==(other)) return false;

	if (!Maths::Is3DVectorEqual(this->mVelocity, other.mVelocity)) return false;

	return true;
}
