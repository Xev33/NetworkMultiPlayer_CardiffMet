#include "WallServer.h"
#include "ClientProxy.h"
#include "Timing.h"
#include "Maths.h"
#include <iostream>

WallServer::WallServer()
{}

void WallServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject( this );
}

void WallServer::Update()
{
	Wall::Update();


	Vector3 oldLocation = GetLocation();
	float oldRotation = GetRotation();

	if( !Maths::Is2DVectorEqual( oldLocation, GetLocation() ) ||
		oldRotation != GetRotation() )
	{
		NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ECRS_Pose);
	}
	else
	{
		std::cout << GetWallId() << "Pos : " << GetLocation().mX << ',' << GetLocation().mY << ',' << GetLocation().mZ << std::endl;
	}
}
