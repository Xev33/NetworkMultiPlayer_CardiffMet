#ifndef SERVER_H
#define SERVER_H

#include "Engine.h"
#include "ClientProxy.h"
#include "Player.h"
#include "NetworkManagerServer.h"
#include <vector>

class Server : public Engine
{
public:

	static bool StaticInit();

	virtual void DoFrame() override;

	virtual int Run();

	void HandleNewClient( ClientProxyPtr inClientProxy );
	void HandleLostClient( ClientProxyPtr inClientProxy );

	PlayerPtr	GetPlayer(int inPlayerId);
	Vector3	GetClosestPlayerPos(Vector3 inLoc);
	void	SpawnPlayer( int inPlayerId );
	void RespawnAI();
	void RespawnGoal();
	int	GetCurrentNumberOfPlayer() const;
	int	GetCurrentNumberOfAi() const;
	bool IsAGoalOnMap() const;


private:
	Server();

	float	mTimeToRespawnAi;
	float	mCoolDownRespawnAI;
	bool	InitNetworkManager();
	void	SetupWorld();
	int		mGoalSpawnerIndex;

	vector<Vector3> mLevelPositions;
	vector<Vector3> mGoalSpawnerPos;

};

#endif // SERVER_H
