#ifndef GOAL_H
#define GOAL_H

#include "GameObject.h"
#include "World.h"

/* We'll later create client and server versions of this class */

class Goal : public GameObject
{
public:
	CLASS_IDENTIFICATION( 'GOAL', GameObject )

	enum EPlayerReplicationState
	{
		ECRS_Pose = 1 << 0,
		ECRS_GoalId = 1 << 1,

		ECRS_AllState = ECRS_Pose | ECRS_GoalId
	};


	static	GameObject*	StaticCreate()			{ return new Goal(); }

	//Note - the code in the book doesn't provide this until the client.
	//This however limits testing.
	static	GameObjectPtr	StaticCreatePtr()			{ return GameObjectPtr(new Goal()); }


	virtual uint32_t GetAllStateMask()	const override	{ return ECRS_AllState; }

	virtual void Update() override;

	void SimulateMovement( float inDeltaTime );

	void ProcessCollisions();
	void ProcessCollisionsWithScreenWalls();
	void AdjustVelocityByThrust(float inDeltaTime);

	void		SetGoalId( uint32_t inPlayerId )			{ mGoalId = inPlayerId; }
	uint32_t	GetGoalId()						const 	{ return mGoalId; }

	void			SetVelocity(const Vector3& inVelocity) { mVelocity = inVelocity; }
	const Vector3& GetVelocity()						const { return mVelocity; }

	void InitFromShooter(Player* player);

//	virtual void	Read( InputMemoryBitStream& inInputStream ) override;

	uint32_t Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const override;
	// For testing

	bool operator==(Goal &other);
protected:
	Goal();
	Goal(Vector3 dir);

private:

	uint32_t			mGoalId;
	Vector3				mVelocity;

protected:
	float				mHealth;
	float				mSpeed;

};

typedef shared_ptr< Goal >	GoalPtr;

#endif // GOAL_H
