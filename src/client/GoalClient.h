#ifndef GOAL_CLIENT_H
#define GOAL_CLIENT_H

#include "Goal.h"
#include "SpriteComponent.h"

class GoalClient : public Goal
{
public:
	static	GameObjectPtr	StaticCreate()		{ return GameObjectPtr( new GoalClient() ); }

	virtual void Update();
	virtual void	HandleDying() override;

	virtual void	Read( InputMemoryBitStream& inInputStream ) override;

protected:
	GoalClient();


private:
	float				mTimeLocationBecameOutOfSync;
	float				mTimeVelocityBecameOutOfSync;

	SpriteComponentPtr	mSpriteComponent;
};
typedef shared_ptr< GoalClient >	GoalClientPtr;
#endif //GOAL_CLIENT_H
