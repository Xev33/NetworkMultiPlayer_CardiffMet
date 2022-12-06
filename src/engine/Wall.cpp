#include "Wall.h"
#include "InputMemoryBitStream.h"
#include "OutputMemoryBitStream.h"
#include "Maths.h"
#include "Player.h"

//zoom hardcoded at 100...if we want to lock players on screen, this could be calculated from zoom
const float HALF_WORLD_HEIGHT = 3.6f;
const float HALF_WORLD_WIDTH = 6.4f;

Wall::Wall()
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