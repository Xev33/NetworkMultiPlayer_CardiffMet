#ifndef WALL_H
#define WALL_H

#include "GameObject.h"
#include "World.h"

/* We'll later create client and server versions of this class */

class Wall : public GameObject
{
public:
	CLASS_IDENTIFICATION('WALL', GameObject)

		enum EPlayerReplicationState
	{
		ECRS_Pose = 1 << 0,
		ECRS_WallId = 1 << 1,

		ECRS_AllState = ECRS_Pose | ECRS_WallId
	};


	static	GameObject* StaticCreate() { return new Wall(); }

	//Note - the code in the book doesn't provide this until the client.
	//This however limits testing.
	static	GameObjectPtr	StaticCreatePtr() { return GameObjectPtr(new Wall()); }


	virtual uint32_t GetAllStateMask()	const override { return ECRS_AllState; }

	void		SetIsSmoke(bool in) { mIsSmoke = in; }
	bool		GetIsSmoke() const { return mIsSmoke; }

	void		SetWallId(uint32_t inPlayerId) { mWallId = inPlayerId; }
	uint32_t	GetWallId()						const { return mWallId; }

	uint32_t Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;
	// For testing

protected:
	Wall();

private:
	uint32_t			mWallId;

protected:
	bool				mIsSmoke;

};

typedef shared_ptr< Wall >	WallPtr;

#endif // WALL_H
