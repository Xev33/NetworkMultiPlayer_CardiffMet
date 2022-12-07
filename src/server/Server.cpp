
#include "Server.h"
#include "GameObjectRegistry.h"
#include "StringUtils.h"
#include "Colors.h"
#include "PlayerServer.h"
#include "BulletServer.h"
#include "WallServer.h"
#include "GoalServer.h"
#include <iostream>

//uncomment this when you begin working on the server

bool Server::StaticInit()
{
	sInstance.reset( new Server() );

	return true;
}

Server::Server() : mTimeToRespawnAi(0), mCoolDownRespawnAI(3), mGoalSpawnerIndex(0)
{

	GameObjectRegistry::sInstance->RegisterCreationFunction( 'PLYR', PlayerServer::StaticCreate );
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'BULT', BulletServer::StaticCreate );
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'WALL', WallServer::StaticCreate );
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'GOAL', GoalServer::StaticCreate );

	InitNetworkManager();

	// Setup latency
	float latency = 0.0f;
	string latencyString = StringUtils::GetCommandLineArg( 2 );
	if( !latencyString.empty() )
	{
		latency = stof( latencyString );
	}
	NetworkManagerServer::sInstance->SetSimulatedLatency( latency );
	//We setup position of every level's wall
	mLevelPositions = { 
	// Bottom left
	 {-3.95, 2, 0}, {-2.90, 2, 0}, {-1.85, 2, 0},
	// Top left
	{-3, -2, 0}, {-1.95, -2, 0}, {-3, -0.95, 0}, {-1.95, -0.95, 0},
	// Right
	{3, -2, 0}, {3, 1, 0}, {3, 2.05, 0}
	};

	//We setup all the possible spawn position for the goal
	mGoalSpawnerPos = {
		 {0, -3, 0}, {-4, 3, 0}, {0, 0, 0},
		 // --------------------------
		 {4, 3, 0}, {-4, -3, 0}, {-2, 0, 0}, {0, -3, 0},
		 // --------------------------
		 {4, -3, 0}, {0, 3, 0}, {4, 0, 0}
	};
}


int Server::Run()
{
	SetupWorld();

	return Engine::Run();
}

bool Server::InitNetworkManager()
{
	string portString = StringUtils::GetCommandLineArg( 1 );
	uint16_t port = stoi( portString );

	return NetworkManagerServer::StaticInit( port );
}


void Server::SetupWorld()
{
	for (Vector3 pos : mLevelPositions)
	{
		WallPtr box = std::static_pointer_cast<Wall>(GameObjectRegistry::sInstance->CreateGameObject('WALL'));
		box->SetLocation(pos);
	}
}

void Server::DoFrame()
{
	NetworkManagerServer::sInstance->ProcessIncomingPackets();

	NetworkManagerServer::sInstance->CheckForDisconnects();

	NetworkManagerServer::sInstance->RespawnPlayers();

	RespawnAI();

	RespawnGoal();

	Engine::DoFrame();

	NetworkManagerServer::sInstance->SendOutgoingPackets();
}

void Server::HandleNewClient( ClientProxyPtr inClientProxy )
{

	int playerId = inClientProxy->GetPlayerId();

	//ScoreBoardManager::sInstance->AddEntry( playerId, inClientProxy->GetName() );
	SpawnPlayer( playerId );
}

void Server::SpawnPlayer( int inPlayerId )
{

	PlayerPtr player = std::static_pointer_cast< Player >( GameObjectRegistry::sInstance->CreateGameObject( 'PLYR' ) );
	player->SetPlayerId( inPlayerId );
	player->SetLocation( Vector3( 1.f - static_cast< float >( inPlayerId ), 0.f, 0.f ) );

}

void Server::RespawnAI()
{
	if (GetCurrentNumberOfAi() == 2)
	{
		mTimeToRespawnAi = 0;
		return;
	}
	if (mTimeToRespawnAi < mCoolDownRespawnAI)
	{
		mTimeToRespawnAi += Timing::sInstance.GetDeltaTime();
		return;
	}
	PlayerPtr ai = std::static_pointer_cast<Player>(GameObjectRegistry::sInstance->CreateGameObject('PLYR'));
	ai->EnableAi(true);
	if (GetCurrentNumberOfAi() == 2)
		ai->SetLocation(Vector3(3.f, 3.f, 0.f));
	else
		ai->SetLocation(Vector3(4.f, 3.f, 0.f));

	PlayerServerPtr  ps = std::static_pointer_cast<PlayerServer>(ai);
	ps->SetPlayerControlType(ESCT_AI);
	ps->SetColor(Colors::Red);//ScoreBoardManager::sInstance->GetEntry( inPlayerId )->GetColor() );
}

void Server::RespawnGoal()
{
	if (IsAGoalOnMap() == true)
		return;
	GoalPtr goal = std::static_pointer_cast<Goal>(GameObjectRegistry::sInstance->CreateGameObject('GOAL'));
	goal->SetLocation(mGoalSpawnerPos.at(mGoalSpawnerIndex));
	mGoalSpawnerIndex++;
	if (mGoalSpawnerIndex >= mGoalSpawnerPos.size())
		mGoalSpawnerIndex = 0;
}

void Server::HandleLostClient( ClientProxyPtr inClientProxy )
{
	//kill client's player
	//remove client from scoreboard
	int playerId = inClientProxy->GetPlayerId();

	//ScoreBoardManager::sInstance->RemoveEntry( playerId );
	PlayerPtr player = GetPlayer( playerId );
	if( player )
	{
		player->SetDoesWantToDie( true );
	}
}

PlayerPtr Server::GetPlayer( int inPlayerId )
{
	//run through the objects till we find the Player...
	//it would be nice if we kept a pointer to the Player on the clientproxy
	//but then we'd have to clean it up when the Player died, etc.
	//this will work for now until it's a perf issue
	const auto& gameObjects = World::sInstance->GetGameObjects();
	for( int i = 0, c = gameObjects.size(); i < c; ++i )
	{
		GameObjectPtr go = gameObjects[ i ];

		/* Original code did this in a weird way, used a method in the base (GameObject) which
		returned a player object if a game object is the player and null otherwise */

		uint32_t type = go->GetClassId();

		//Player* player = dynamic_cast<Player*>(*go);
		PlayerPtr player = nullptr;
		if(type == 'PLYR')
		{
			player = std::static_pointer_cast< Player >(go);
		}

		if(player && player->GetPlayerId() == inPlayerId )
		{
			return player;
		}
	}

	return nullptr;

}

Vector3	Server::GetClosestPlayerPos(Vector3 inLoc)
{
	const auto& gameObjects = World::sInstance->GetGameObjects();
	Vector3 closestPlayerPoc = inLoc;
	float closestDistance = 0;

	for (int i = 0, c = gameObjects.size(); i < c; ++i)
	{
		GameObjectPtr go = gameObjects[i];
		/* Original code did this in a weird way, used a method in the base (GameObject) which
		returned a player object if a game object is the player and null otherwise */

		uint32_t type = go->GetClassId();

		if (type == 'PLYR')
		{
			PlayerPtr player = std::static_pointer_cast<Player>(go);

			if (player != nullptr && player->IsAi() == false)
			{
				Vector3 dist = player->GetLocation() - inLoc;

				if (closestPlayerPoc == inLoc)
				{
					closestPlayerPoc = player->GetLocation();
					closestDistance = dist.Length2D();
				}
				if (dist.Length2D() < closestDistance)
				{
					closestDistance = dist.Length2D();
					closestPlayerPoc = player->GetLocation();
				}
			}
		}
	}
	//std::cout << "ClosestPlayer pos = " << closestPlayerPoc.mX << ',' << closestPlayerPoc.mY << ',' << closestPlayerPoc.mZ << std::endl;
	return closestPlayerPoc;
}

int	Server::GetCurrentNumberOfPlayer() const
{
	const auto& gameObjects = World::sInstance->GetGameObjects();
	int nbrOfPlayer = 0;

	for (int i = 0, c = gameObjects.size(); i < c; ++i)
	{
		GameObjectPtr go = gameObjects[i];

		uint32_t type = go->GetClassId();

		if (type == 'PLYR')
		{
			PlayerPtr player = std::static_pointer_cast<Player>(go);

			if (player != nullptr && player->IsAi() == false)
			{
				nbrOfPlayer++;
			}
		}
	}
	return nbrOfPlayer;
}

int	Server::GetCurrentNumberOfAi() const
{
	const auto& gameObjects = World::sInstance->GetGameObjects();
	int nbrOfAi = 0;

	for (int i = 0, c = gameObjects.size(); i < c; ++i)
	{
		GameObjectPtr go = gameObjects[i];

		uint32_t type = go->GetClassId();

		if (type == 'PLYR')
		{
			PlayerPtr player = std::static_pointer_cast<Player>(go);

			if (player != nullptr && player->IsAi() == true)
				nbrOfAi++;
		}
	}
	return nbrOfAi;
}

bool Server::IsAGoalOnMap() const
{
	const auto& gameObjects = World::sInstance->GetGameObjects();

	for (int i = 0, c = gameObjects.size(); i < c; ++i)
	{
		GameObjectPtr go = gameObjects[i];

		uint32_t type = go->GetClassId();

		if (type == 'GOAL')
		{
			GoalPtr goal = std::static_pointer_cast<Goal>(go);

			if (goal != nullptr)
				return true;
		}
	}
	return false;
}

