#ifndef PLAYER_CLIENT_H
#define PLAYER_CLIENT_H

#include "Player.h"
#include "SpriteComponent.h"

class PlayerClient : public Player
{
public:
	static	GameObjectPtr	StaticCreate()		{ return GameObjectPtr( new PlayerClient() ); }

	virtual void Update();
	virtual void	HandleDying() override;
	const SpriteComponentPtr GetSpriteComponent() { return mSpriteComponent; }

	virtual void	Read( InputMemoryBitStream& inInputStream ) override;

protected:
	PlayerClient();


private:
	float				mTimeLocationBecameOutOfSync;
	float				mTimeVelocityBecameOutOfSync;
	bool				isSpriteChanged;

	SpriteComponentPtr	mSpriteComponent;
};
typedef shared_ptr< PlayerClient >	PlayerClientPtr;
#endif //PLAYER_CLIENT_H
