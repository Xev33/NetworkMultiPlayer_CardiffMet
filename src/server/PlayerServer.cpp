#include "PlayerServer.h"
#include "Bullet.h"
#include "ClientProxy.h"
#include "Timing.h"
#include "MoveList.h"
#include "Maths.h"
#include "GameObjectRegistry.h"
#include <iostream>
#include <memory>

PlayerServer::PlayerServer() :
	mPlayerControlType( ESCT_Human ),
	mTimeOfNextShot( 0.f ),
	mTimeBetweenShots( 0.2f )
{}

void PlayerServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject( this );
}

void PlayerServer::Update()
{
	if (mPlayerControlType == ESCT_Human)
		UpdatePlayer();
	else
		UpdateAI();
}

void PlayerServer::UpdatePlayer()
{
	Player::Update();


	Vector3 oldLocation = GetLocation();
	Vector3 oldVelocity = GetVelocity();
	float oldRotation = GetRotation();

	ClientProxyPtr client = NetworkManagerServer::sInstance->GetClientProxy(GetPlayerId());
	if (client)
	{
		MoveList& moveList = client->GetUnprocessedMoveList();
		for (const Move& unprocessedMove : moveList)
		{
			const InputState& currentState = unprocessedMove.GetInputState();
			float deltaTime = unprocessedMove.GetDeltaTime();
			ProcessInput(deltaTime, currentState);
			SimulateMovement(deltaTime);
		}

		moveList.Clear();
	}

	HandleShooting();

	if (!Maths::Is2DVectorEqual(oldLocation, GetLocation()) ||
		!Maths::Is2DVectorEqual(oldVelocity, GetVelocity()) ||
		oldRotation != GetRotation() )
	{
		NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ECRS_Pose);
	}
}

void PlayerServer::UpdateAI()
{
	Player::Update();

	// If no player -> AI doesn't move
	if ((static_cast<Server*> (Engine::sInstance.get()))->GetCurrentNumberOfPlayer() == 0)
	{
		mThrustDir = 0;
		ProcessCollisions();
		return;
	}

	mThrustDir = 0.01;
	float time = Timing::sInstance.GetFrameStartTime();
	Vector3 closestPlayerLoc = (static_cast<Server*> (Engine::sInstance.get()))->GetClosestPlayerPos(this->GetLocation()) - GetLocation();
	Vector3 forwardVec = GetRightVector();

	// We normalize every vectors
	closestPlayerLoc.Normalize2D();
	forwardVec.Normalize2D();

	float dot = Dot2D(forwardVec, closestPlayerLoc); // dot product
	float det = Det2D(forwardVec, closestPlayerLoc); // determinant
	float angleToRotate = std::atan2(dot, det);

	//We check if the player is on the AI's right or not
	if (angleToRotate <= -0.5)
		this->SetRotation(this->GetRotation() - (GetMaxRotationSpeed() * time) / 5000);
	else
		this->SetRotation(this->GetRotation() + (GetMaxRotationSpeed() * time) / 5000);
	NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ECRS_Pose);
	ProcessCollisions();
}

void PlayerServer::HandleShooting()
{
	float time = Timing::sInstance.GetFrameStartTime();
	if( mIsShooting && Timing::sInstance.GetFrameStartTime() > mTimeOfNextShot )
	{
		//not exact, but okay
		mTimeOfNextShot = time + mTimeBetweenShots;

		//fire!
		BulletPtr bullet = std::static_pointer_cast< Bullet >( GameObjectRegistry::sInstance->CreateGameObject( 'BULT' ) );
		bullet->InitFromShooter( this );
	}
}

void PlayerServer::TakeDamage( int inDamagingPlayerId )
{
	mHealth--;
	if( mHealth <= 0.f )
	{
		//score one for damaging player...
		//ScoreBoardManager::sInstance->IncScore( inDamagingPlayerId, 1 );

		//and you want to die
		SetDoesWantToDie( true );

		//tell the client proxy to make you a new cat
		ClientProxyPtr clientProxy = NetworkManagerServer::sInstance->GetClientProxy( GetPlayerId() );
		if( clientProxy )
		{
			clientProxy->HandlePlayerDied();
			//std::cout << "hehe";
		}
		else
		{
			// if ai dies
			//static_cast<Server*> (Engine::sInstance.get())->SpawnAI();
		}
	}

	//tell the world our health dropped
	NetworkManagerServer::sInstance->SetStateDirty( GetNetworkId(), ECRS_Health );
}
