#ifndef TCP_SOCKET_H_
#define TCP_SOCKET_H_

#include "NetworkingCommon.h"

class SocketAddress;

#include <memory>
using std::shared_ptr;

class TCPSocket
{
public:
	~TCPSocket();
	int								Connect( const SocketAddress& inAddress );
	int								Bind( const SocketAddress& inToAddress );
	int								Listen( int inBackLog = 32 );
	shared_ptr< TCPSocket >			Accept( SocketAddress& inFromAddress );
	int32_t							Send( const void* inData, size_t inLen );
	int32_t							Receive( void* inBuffer, size_t inLen );
private:
	friend class SocketUtil;
	TCPSocket( SOCKET inSocket ) : mSocket( inSocket ) {}
	SOCKET		mSocket;
};
typedef shared_ptr< TCPSocket > TCPSocketPtr;

#endif
