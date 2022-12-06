#ifndef SERVER_H
#define SERVER_H

#include "Engine.h"
#include "ClientProxy.h"
#include "Player.h"
#include "NetworkManagerServer.h"

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
	void SpawnAI();
	int	GetCurrentNumberOfPlayer() const;
	bool	IsAiAlive() const;


private:
	Server();

	bool	InitNetworkManager();
	void	SetupWorld();

};

#endif // SERVER_H
