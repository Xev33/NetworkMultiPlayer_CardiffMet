#ifndef WALL_SERVER_H
#define WALL_SERVER_H

#include "Wall.h"
#include "NetworkManagerServer.h"


class WallServer : public Wall
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new WallServer()); }
	
	virtual void HandleDying() override;

	void Update();

protected:
	WallServer();

private:
	float mTimeBeforeDeath;
	float mLifeTime;
};


#endif // WALL_SERVER_H
