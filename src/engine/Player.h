#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "World.h"

class InputState;

/* We'll later create client and server versions of this class */

class Player : public GameObject
{
public:
	CLASS_IDENTIFICATION( 'PLYR', GameObject )

	enum EPlayerReplicationState
	{
		ECRS_Pose = 1 << 0,
		ECRS_Color = 1 << 1,
		ECRS_PlayerId = 1 << 2,
		ECRS_Health = 1 << 3,

		ECRS_AllState = ECRS_Pose | ECRS_Color | ECRS_PlayerId | ECRS_Health
	};


	static	GameObject*	StaticCreate()			{ return new Player(); }

	//Note - the code in the book doesn't provide this until the client.
	//This however limits testing.
	static	GameObjectPtr	StaticCreatePtr()			{ return GameObjectPtr(new Player()); }


	virtual uint32_t GetAllStateMask()	const override	{ return ECRS_AllState; }

	virtual void Update() override;

	void ProcessInput( float inDeltaTime, const InputState& inInputState );
	void SimulateMovement( float inDeltaTime );

	void ProcessCollisions();
	void ProcessCollisionsWithScreenWalls();

	void		SetPlayerId( uint32_t inPlayerId )			{ mPlayerId = inPlayerId; }
	uint32_t	GetPlayerId()						const 	{ return mPlayerId; }

	void		SetPlayerHealth(int inPlayerId) { mHealth = inPlayerId; }
	int	GetPlayerHealth()						const { return mHealth; }

	void			SetThrust( const float& inThrust )	{ mThrustDir = inThrust; }
	void			SetVelocity( const Vector3& inVelocity )	{ mVelocity = inVelocity; }
	const Vector3&	GetVelocity()						const	{ return mVelocity; }

	void			EnableAi(const bool isAi) { mIsAi = isAi; }

	void			SetClosestPlayerPos(const Vector3& inPos) { mVelocity = inPos; }
	const Vector3& GetClosestPlayerPos()						const { return mClosestPlayerPos; }

//	virtual void	Read( InputMemoryBitStream& inInputStream ) override;

	uint32_t Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const override;
	// For testing

	float GetMaxLinearSpeed() { return mMaxLinearSpeed; }
	float GetMaxRotationSpeed() { return mMaxRotationSpeed; }
	float GetWallRestitution() { return mWallRestitution; }
	float GetNPCRestitution() { return mNPCRestitution; }
	float GetLastMoveTimestamp() { return mLastMoveTimestamp; }
	float GetThrustDir() { return mThrustDir; }
	int GetHealth() { return mHealth; }
	bool IsShooting() { return mIsShooting; }
	bool IsAi() { return mIsAi; }

	bool operator==(Player &other);
protected:
	Player();

private:


	void	AdjustVelocityByThrust( float inDeltaTime );

	Vector3				mVelocity;
	Vector3				mClosestPlayerPos;


	float				mMaxLinearSpeed;
	float				mMaxRotationSpeed;

	//bounce fraction when hitting various things
	float				mWallRestitution;
	float				mNPCRestitution;


	uint32_t			mPlayerId;

protected:

	///move down here for padding reasons...

	float				mLastMoveTimestamp;

	float				mThrustDir;
	int					mHealth;

	bool				mIsShooting;
	bool				mIsAi;


};

typedef shared_ptr< Player >	PlayerPtr;

#endif // PLAYER_H_
