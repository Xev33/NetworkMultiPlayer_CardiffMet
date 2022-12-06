#ifndef GOAL_SERVER_H
#define GOAL_SERVER_H

#include "Goal.h"
#include "NetworkManagerServer.h"


class GoalServer : public Goal
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new GoalServer() ); }
	virtual void HandleDying() override;

	virtual void Update() override;

	virtual bool HandleCollisionWithPlayer(Player* inPlayer) override;

protected:
	GoalServer();

private:

};

#endif // GOAL_SERVER_H
