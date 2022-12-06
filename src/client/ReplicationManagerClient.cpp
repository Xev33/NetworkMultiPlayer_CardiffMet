
#include "ReplicationManagerClient.h"
#include "GameObject.h"
#include "GameObjectRegistry.h"
#include "InputMemoryBitStream.h"
#include "NetworkManagerClient.h"
#include "ReplicationCommand.h"

#include "StringUtils.h"

#include <cassert>

void ReplicationManagerClient::Read( InputMemoryBitStream& inInputStream )
{
	//LOG("DEBUG: ReplicationManagerClient is reading: %x bits left", inInputStream.GetRemainingBitCount());
	while( inInputStream.GetRemainingBitCount() >= 32 )
	{
		//read the network id...
		int networkId;
		inInputStream.Read( networkId );

		//only need 2 bits for action...
		uint8_t action;
		inInputStream.Read( action, 2 );

		switch( action )
		{
		case RA_Create:
			ReadAndDoCreateAction( inInputStream, networkId );
			//LOG("DEBUG - ReadAndDoCreateAction for networkId:%d", networkId);
			break;
		case RA_Update:
			ReadAndDoUpdateAction( inInputStream, networkId );
			//LOG("DEBUG - ReadAndDoUpdateAction for networkId:%d", networkId);
			break;
		case RA_Destroy:
			ReadAndDoDestroyAction( inInputStream, networkId );
			//LOG("DEBUG - ReadAndDoDestroyAction for networkId:%d", networkId);
			break;
		default:
			LOG("ERROR - Unknown replication action for networkId:%d", networkId);

		}

	}

}

void ReplicationManagerClient::ReadAndDoCreateAction( InputMemoryBitStream& inInputStream, int inNetworkId )
{
	//need 4 cc
	uint32_t fourCCName;
	inInputStream.Read( fourCCName );

	//we might already have this object- could happen if our ack of the create got dropped so server resends create request
	//( even though we might have created )
	GameObjectPtr gameObject = NetworkManagerClient::sInstance->GetGameObject( inNetworkId );
	if( !gameObject )
	{
		//create the object and map it...
		gameObject = GameObjectRegistry::sInstance->CreateGameObject( fourCCName );
		gameObject->SetNetworkId( inNetworkId );
		NetworkManagerClient::sInstance->AddToNetworkIdToGameObjectMap( gameObject );

		//it had really be the rigth type...
		assert( gameObject->GetClassId() == fourCCName );
	}

	//and read state
	gameObject->Read( inInputStream );
}

void ReplicationManagerClient::ReadAndDoUpdateAction( InputMemoryBitStream& inInputStream, int inNetworkId )
{
	//need object
	GameObjectPtr gameObject = NetworkManagerClient::sInstance->GetGameObject( inNetworkId );

	//gameObject MUST be found, because create was ack'd if we're getting an update...
	//and read state
	gameObject->Read( inInputStream );
}

void ReplicationManagerClient::ReadAndDoDestroyAction( InputMemoryBitStream& inInputStream, int inNetworkId )
{
	//if something was destroyed before the create went through, we'll never get it
	//but we might get the destroy request, so be tolerant of being asked to destroy something that wasn't created
	GameObjectPtr gameObject = NetworkManagerClient::sInstance->GetGameObject( inNetworkId );
	if( gameObject )
	{
		gameObject->SetDoesWantToDie( true );
		NetworkManagerClient::sInstance->RemoveFromNetworkIdToGameObjectMap( gameObject );
	}
}
