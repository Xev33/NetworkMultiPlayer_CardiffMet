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
	float oldRotation = GetRotation();

	if( !Maths::Is2DVectorEqual( oldLocation, GetLocation()))
	{
		NetworkManagerServer::sInstance->SetStateDirty( GetNetworkId(), ECRS_Pose );
	}
}

// The goal cannot interact with AI a doesn't hurt players
bool GoalServer::HandleCollisionWithPlayer(Player* inPlayer)
{
	PlayerServer* ps = static_cast<PlayerServer*>(inPlayer);
	if (ps)
	{
		if (ps->IsAi() == true)
			return false;
		//ps->TakeDamage(this->GetGoalId());
	
		SetDoesWantToDie(true);
		return true;
	}
	else
		return false;

}