#ifndef RECEIVED_PACKET_H_
#define RECEIVED_PACKET_H_

#include "InputMemoryBitStream.h"
#include "SocketAddress.h"

class ReceivedPacket
{
public:
	ReceivedPacket( float inReceivedTime, InputMemoryBitStream& inInputMemoryBitStream, const SocketAddress& inAddress );

	const	SocketAddress&			GetFromAddress()	const	{ return mFromAddress; }
			float					GetReceivedTime()	const	{ return mReceivedTime; }
			InputMemoryBitStream&	GetPacketBuffer()			{ return mPacketBuffer; }

private:

	float					mReceivedTime;
	InputMemoryBitStream	mPacketBuffer;
	SocketAddress			mFromAddress;

};

  #endif
