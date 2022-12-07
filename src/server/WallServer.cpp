#include "WallServer.h"

WallServer::WallServer() : mTimeBeforeDeath(2), mLifeTime(0)
{
}

void WallServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

// If wall is a smoke, it will be destroy after mTimeBeforeDeath seconds
void WallServer::Update()
{
	if (mIsSmoke == false)
		return;

	mLifeTime += Timing::sInstance.GetDeltaTime();
	if (mLifeTime >= mTimeBeforeDeath)
		SetDoesWantToDie( true );
}