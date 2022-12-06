
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

Server::Server()
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
	// Static game objects and NPCs here.
	//GoalPtr box = std::static_pointer_cast<Goal>(GameObjectRegistry::sInstance->CreateGameObject('GOAL'));
	WallPtr box = std::static_pointer_cast<Wall>(GameObjectRegistry::sInstance->CreateGameObject('WALL'));
	box->SetLocation(Vector3(1.f, 3.f, 0.f));

	SpawnAI();
}

void Server::DoFrame()
{
	NetworkManagerServer::sInstance->ProcessIncomingPackets();

	NetworkManagerServer::sInstance->CheckForDisconnects();

	NetworkManagerServer::sInstance->RespawnPlayers();

	Engine::DoFrame();
	SpawnAI();

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
	player->SetColor( Colors::Red );//ScoreBoardManager::sInstance->GetEntry( inPlayerId )->GetColor() );
	player->SetPlayerId( inPlayerId );
	//gotta pick a better spawn location than this...
	player->SetLocation( Vector3( 1.f - static_cast< float >( inPlayerId ), 0.f, 0.f ) );

}

void Server::SpawnAI()
{
	if (IsAiAlive() == true)
		return;
	PlayerPtr ai = std::static_pointer_cast<Player>(GameObjectRegistry::sInstance->CreateGameObject('PLYR'));
	ai->SetPlayerId(0);
	ai->EnableAi(true);

	PlayerServerPtr  ps = std::static_pointer_cast<PlayerServer>(ai);
	ps->SetPlayerControlType(ESCT_AI);
	ps->SetPlayerHealth(3);
	//gotta pick a better spawn location than this...
	ai->SetLocation(Vector3(2.f, 2.f, 0.f));

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

bool	Server::IsAiAlive() const
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

			if (player != nullptr && player->IsAi() == true)
				return true;
		}
	}
	return false;
}

