#ifndef WALL_SERVER_H
#define WALL_SERVER_H

#include "Wall.h"
#include "NetworkManagerServer.h"

class WallServer : public Wall
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new WallServer() ); }
	virtual void HandleDying() override;

	virtual void Update() override;

protected:
	WallServer();

private:

};

#endif // WALL_SERVER_H
