#ifndef BULLET_SERVER_H
#define BULLET_SERVER_H

#include "Bullet.h"
#include "NetworkManagerServer.h"


class BulletServer : public Bullet
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new BulletServer() ); }
	virtual void HandleDying() override;

	virtual void Update() override;

	virtual bool HandleCollisionWithPlayer(Player* inPlayer) override;

protected:
	BulletServer();

private:

	//float		mTimeOfNextShot;
	//float		mTimeBetweenShots;

};

#endif // BULLET_SERVER_H
