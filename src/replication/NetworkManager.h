#ifndef NETWORK_MANAGER_H_
#define NETWORK_MANAGER_H_

// From Replication.
#include "ReceivedPacket.h"
#include "Timing.h"
#include "WeightedTimedMovingAverage.h"

//From Networking
#include "UDPSocket.h"

//From Engine
#include "GameObject.h"

#include <unordered_map>
using std::unordered_map;

#include <list>
using std::list;

#include <queue>
using std::queue;

typedef unordered_map< int, GameObjectPtr > IntToGameObjectMap;

class InputMemoryBitStream;
class SocketAddress;
class OutputMemoryBitStream;


class NetworkManager
{
public:
	static const uint32_t	kHelloCC = 'HELO';
	static const uint32_t	kWelcomeCC = 'WLCM';
	static const uint32_t	kStateCC = 'STAT';
	static const uint32_t	kInputCC = 'INPT';
	static const int		kMaxPacketsPerFrameCount = 10;

	NetworkManager();
	virtual ~NetworkManager();

	bool	Init( uint16_t inPort );
	void	ProcessIncomingPackets();

	virtual void	ProcessPacket( InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress ) = 0;
	virtual void	HandleConnectionReset( const SocketAddress& inFromAddress ) { ( void ) inFromAddress; }

	void	SendPacket( const OutputMemoryBitStream& inOutputStream, const SocketAddress& inFromAddress );

	const WeightedTimedMovingAverage& GetBytesReceivedPerSecond()	const	{ return mBytesReceivedPerSecond; }
	const WeightedTimedMovingAverage& GetBytesSentPerSecond()		const	{ return mBytesSentPerSecond; }

	void	SetDropPacketChance( float inChance )	{ mDropPacketChance = inChance; }
	float	GetDropPacketChance() const				{ return mDropPacketChance; }
	void	SetSimulatedLatency( float inLatency )	{ mSimulatedLatency = inLatency; }
	float	GetSimulatedLatency() const				{ return mSimulatedLatency; }

	inline	GameObjectPtr	GetGameObject( int inNetworkId ) const;
	void	AddToNetworkIdToGameObjectMap( GameObjectPtr inGameObject );
	void	RemoveFromNetworkIdToGameObjectMap( GameObjectPtr inGameObject );

protected:

	IntToGameObjectMap		mNetworkIdToGameObjectMap;

private:

	void	UpdateBytesSentLastFrame();
	void	ReadIncomingPacketsIntoQueue();
	void	ProcessQueuedPackets();

	queue< ReceivedPacket, list< ReceivedPacket > >	mPacketQueue;

	UDPSocketPtr	mSocket;

	WeightedTimedMovingAverage	mBytesReceivedPerSecond;
	WeightedTimedMovingAverage	mBytesSentPerSecond;

	int							mBytesSentThisFrame;

	float						mDropPacketChance;
	float						mSimulatedLatency;

};



inline	GameObjectPtr NetworkManager::GetGameObject( int inNetworkId ) const
{
	auto gameObjectIt = mNetworkIdToGameObjectMap.find( inNetworkId );
	if( gameObjectIt != mNetworkIdToGameObjectMap.end() )
	{
		return gameObjectIt->second;
	}
	else
	{
		return GameObjectPtr();
	}
}

#endif //NETWORK_MANAGER_H_
