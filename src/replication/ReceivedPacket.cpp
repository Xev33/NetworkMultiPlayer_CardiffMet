#include "ReceivedPacket.h"

ReceivedPacket::ReceivedPacket( float inReceivedTime, InputMemoryBitStream& ioInputMemoryBitStream, const SocketAddress& inFromAddress ) :
	mReceivedTime( inReceivedTime ),
	mFromAddress( inFromAddress ),
	mPacketBuffer( ioInputMemoryBitStream )
{
}
