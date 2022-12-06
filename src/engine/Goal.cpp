#include "Goal.h"
#include "InputMemoryBitStream.h"
#include "OutputMemoryBitStream.h"
#include "Maths.h"
#include "Player.h"

//zoom hardcoded at 100...if we want to lock players on screen, this could be calculated from zoom
const float HALF_WORLD_HEIGHT = 3.6f;
const float HALF_WORLD_WIDTH = 6.4f;

Goal::Goal() : mHealth(1)
{
	mVelocity.mX = 0;
	mVelocity.mY = 0;
	mVelocity.mZ = 0;
}

Goal::Goal(Vector3 dir) : mVelocity(dir), mHealth(1)
{
	this->SetCollisionRadius(0.5f);
}

void Goal::Update()
{
}

void Goal::SimulateMovement(float inDeltaTime)
{
	

	SetLocation(GetLocation() + mVelocity * inDeltaTime);

	ProcessCollisions();
}

void Goal::InitFromShooter(Player* player)
{
	Vector3 pos = player->GetLocation() + player->GetForwardVector() * 1.5;
	SetLocation(pos);
	SetScale(this->GetScale()/2);
	SetVelocity(player->GetVelocity() * 2);
	SetRotation(player->GetRotation());
}

void Goal::ProcessCollisions()
{
	ProcessCollisionsWithScreenWalls();
}

void Goal::ProcessCollisionsWithScreenWalls()
{
	Vector3 location = GetLocation();
	float x = location.mX;
	float y = location.mY;

	float vx = mVelocity.mX;
	float vy = mVelocity.mY;

	float radius = GetCollisionRadius();

	//if the Goal collides against a wall, destroy it
	if ((y + radius) >= HALF_WORLD_HEIGHT)
	{
		SetDoesWantToDie(true);
	}
	else if (y <= (-HALF_WORLD_HEIGHT - radius))
	{
		SetDoesWantToDie(true);
	}

	if ((x + radius) >= HALF_WORLD_WIDTH)
	{	
		SetDoesWantToDie(true);
	}
	else if (x <= (-HALF_WORLD_WIDTH - radius))
	{
		SetDoesWantToDie(true);
	}
}

uint32_t Goal::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & ECRS_GoalId)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(GetGoalId());

		writtenState |= ECRS_GoalId;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & ECRS_Pose)
	{
		inOutputStream.Write((bool)true);

		Vector3 velocity = mVelocity;
		inOutputStream.Write(velocity.mX);
		inOutputStream.Write(velocity.mY);

		Vector3 location = GetLocation();
		inOutputStream.Write(location.mX);
		inOutputStream.Write(location.mY);

		inOutputStream.Write(GetRotation());
		inOutputStream.Write(GetScale());

		writtenState |= ECRS_Pose;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}
	return writtenState;
}

bool Goal::operator==(Goal& other)
{
	if (!GameObject::operator==(other)) return false;

	if (!Maths::Is3DVectorEqual(this->mVelocity, other.mVelocity)) return false;

	return true;
}

void Goal::AdjustVelocityByThrust(float inDeltaTime)
{
	//just set the velocity based on the thrust direction -- no thrust will lead to 0 velocity
	//simulating acceleration makes the client prediction a bit more complex
	Vector3 forwardVector = GetForwardVector();
	mVelocity = forwardVector * (inDeltaTime * mSpeed);
}
