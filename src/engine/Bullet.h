#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "World.h"

/* We'll later create client and server versions of this class */

class Bullet : public GameObject
{
public:
	CLASS_IDENTIFICATION( 'BULT', GameObject )

	enum EPlayerReplicationState
	{
		ECRS_Pose = 1 << 0,
		ECRS_BulletId = 1 << 1,
		//ECRS_Health = 1 << 2,
		//ECRS_Color = 1 << 3,

		ECRS_AllState = ECRS_Pose | ECRS_BulletId /*| ECRS_Health | ECRS_Color */
	};


	static	GameObject*	StaticCreate()			{ return new Bullet(); }

	//Note - the code in the book doesn't provide this until the client.
	//This however limits testing.
	static	GameObjectPtr	StaticCreatePtr()			{ return GameObjectPtr(new Bullet()); }


	virtual uint32_t GetAllStateMask()	const override	{ return ECRS_AllState; }

	virtual void Update() override;

	void SimulateMovement( float inDeltaTime );

	void ProcessCollisions();
	void ProcessCollisionsWithScreenWalls();
	void AdjustVelocityByThrust(float inDeltaTime);

	void		SetBulletId( uint32_t inPlayerId )			{ mBulletId = inPlayerId; }
	uint32_t	GetBulletId()						const 	{ return mBulletId; }

	void			SetVelocity(const Vector3& inVelocity) { mVelocity = inVelocity; }
	const Vector3& GetVelocity()						const { return mVelocity; }

	void InitFromShooter(Player* player);

//	virtual void	Read( InputMemoryBitStream& inInputStream ) override;

	uint32_t Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const override;
	// For testing

	bool operator==(Bullet &other);
protected:
	Bullet();
	Bullet(Vector3 dir);

private:

	uint32_t			mBulletId;
	Vector3				mVelocity;

protected:
	float				mHealth;
	float				mSpeed;

};

typedef shared_ptr< Bullet >	BulletPtr;

#endif // BULLET_H
