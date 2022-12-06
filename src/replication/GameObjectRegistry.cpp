#include "GameObjectRegistry.h"
#include <iostream>

#include "GameObject.h"

// Dodgy!
#include "World.h"


std::unique_ptr< GameObjectRegistry >	GameObjectRegistry::sInstance;

void GameObjectRegistry::StaticInit()
{
	sInstance.reset( new GameObjectRegistry() );
}

GameObjectRegistry::GameObjectRegistry()
{
}

void GameObjectRegistry::RegisterCreationFunction( uint32_t inFourCCName, GameObjectCreationFunc inCreationFunction )
{
	mNameToGameObjectCreationFunctionMap[ inFourCCName ] = inCreationFunction;
}

bool GameObjectRegistry::CanCreate( uint32_t inFourCCName )
{
	std::unordered_map< uint32_t, GameObjectCreationFunc >::iterator it;
	it = mNameToGameObjectCreationFunctionMap.find(inFourCCName);
	//end is the element after the last
	//if find has returned this - its not there.
	return (it != mNameToGameObjectCreationFunctionMap.end());
}

GameObjectPtr GameObjectRegistry::CreateGameObject( uint32_t inFourCCName )
{
	//std::cout << inFourCCName << std::endl;
	// This is more graceful than a crash but time consuming (consider removing with #define for production)
	if(CanCreate(inFourCCName) == true)
	{
		GameObjectCreationFunc creationFunc = mNameToGameObjectCreationFunctionMap[ inFourCCName ];

		GameObjectPtr gameObject = creationFunc();

		//should the registry depend on the world? this might be a little weird
		//perhaps you should ask the world to spawn things? for now it will be like this
		World::sInstance->AddGameObject( gameObject );

		return gameObject;
	}
	else
	{
		throw UnknownGameObjectType();
	}
}
