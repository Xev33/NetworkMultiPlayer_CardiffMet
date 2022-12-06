#ifndef WALL_CLIENT_H
#define WALL_CLIENT_H

#include "Wall.h"
#include "SpriteComponent.h"

class WallClient : public Wall
{
public:
	static	GameObjectPtr	StaticCreate()		{ return GameObjectPtr( new WallClient() ); }

	virtual void	HandleDying() override;
	virtual void Update();
	virtual void	Read( InputMemoryBitStream& inInputStream ) override;

protected:
	WallClient();


private:
	float				mTimeLocationBecameOutOfSync;
	float				mTimeVelocityBecameOutOfSync;

	SpriteComponentPtr	mSpriteComponent;
};
typedef shared_ptr< WallClient >	WallClientPtr;
#endif //WALL_CLIENT_H
