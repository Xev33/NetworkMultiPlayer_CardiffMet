#ifndef GAME_OBJECT_REGISTRY_H_
#define GAME_OBJECT_REGISTRY_H_

#include "GameObject.h"

#include <memory>
#include <unordered_map>

#include <exception>

typedef GameObjectPtr ( *GameObjectCreationFunc )();

// http://www.cplusplus.com/doc/tutorial/exceptions/
class UnknownGameObjectType: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Game Object Type Unknown";
  }
};

class GameObjectRegistry
{
public:

	static void StaticInit();

	static std::unique_ptr< GameObjectRegistry >		sInstance;

	void RegisterCreationFunction( uint32_t inFourCCName, GameObjectCreationFunc inCreationFunction );

	GameObjectPtr CreateGameObject( uint32_t inFourCCName );

private:

	GameObjectRegistry();

	bool CanCreate( uint32_t inFourCCName );

	std::unordered_map< uint32_t, GameObjectCreationFunc >	mNameToGameObjectCreationFunctionMap;

};

#endif
