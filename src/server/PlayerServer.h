#ifndef PLAYER_SERVER_H
#define PLAYER_SERVER_H

#include "Player.h"
#include "Server.h"
#include "NetworkManagerServer.h"

enum EPlayerControlType
{
	ESCT_Human,
	ESCT_AI
};

class PlayerServer : public Player
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new PlayerServer() ); }
	virtual void HandleDying() override;

	virtual void Update() override;
	virtual void UpdatePlayer();
	virtual void UpdateAI();

	float GetAiSpeed() { return mAiSpeed; }

	void SetPlayerControlType( EPlayerControlType inPlayerControlType ) { mPlayerControlType = inPlayerControlType; }
	virtual bool HandleCollisionWithPlayer(Player* inPlayer) override;

	void TakeDamage( int inDamagingPlayerId );

protected:
	PlayerServer();

private:

	void HandleShooting();
	void HandleMakeSmoke();

	EPlayerControlType	mPlayerControlType;


	float		mTimeOfNextShot;
	float		mTimeBetweenShots;
	float		mAiSpeed;

};

typedef shared_ptr< PlayerServer >	PlayerServerPtr;

#endif // PLAYER_SERVER_H
