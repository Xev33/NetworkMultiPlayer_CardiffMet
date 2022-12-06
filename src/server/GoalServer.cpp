#include "GoalServer.h"
#include "PlayerServer.h"
#include "ClientProxy.h"
#include "Timing.h"
#include "MoveList.h"
#include "Maths.h"

GoalServer::GoalServer()
{
}

void GoalServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject( this );
}

void GoalServer::Update()
{
	Goal::Update();

	Vector3 oldLocation = GetLocation();
	Vector3 oldVelocity = GetVelocity();
	float oldRotation = GetRotation();

	// Trouver comment faire l'update
	ClientProxyPtr client = NetworkManagerServer::sInstance->GetClientProxy( GetGoalId() );
	if( client )
	{
		MoveList& moveList = client->GetUnprocessedMoveList();
		for( const Move& unprocessedMove : moveList )
		{
			const InputState& currentState = unprocessedMove.GetInputState();
			float deltaTime = unprocessedMove.GetDeltaTime();
			SimulateMovement( deltaTime );
		}

		moveList.Clear();
	}
	else
		ProcessCollisions();


	if( !Maths::Is2DVectorEqual( oldLocation, GetLocation() ) ||
		!Maths::Is2DVectorEqual( oldVelocity, GetVelocity() ) ||
		oldRotation != GetRotation() )
	{
		NetworkManagerServer::sInstance->SetStateDirty( GetNetworkId(), ECRS_Pose );
	}
	else
		NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ECRS_Pose);
	ProcessCollisionsWithScreenWalls();
}

bool GoalServer::HandleCollisionWithPlayer(Player* inPlayer)
{
	PlayerServer* ps = static_cast<PlayerServer*>(inPlayer);
	if (ps)
	{
		ps->TakeDamage(this->GetGoalId());
	
		SetDoesWantToDie(true);
		return true;
	}
	else
		return false;

}