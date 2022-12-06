#include "SocketAddress.h"
#include "StringUtils.h"

#if _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif

string	SocketAddress::ToString() const
{
#if _WIN32
	const sockaddr_in* s = GetAsSockAddrIn();
	char destinationBuffer[ 128 ];
	InetNtop( s->sin_family, const_cast< in_addr* >( &s->sin_addr ), destinationBuffer, sizeof( destinationBuffer ) );
	return StringUtils::Sprintf( "%s:%d",
								destinationBuffer,
								ntohs( s->sin_port ) );
#else
	//not implement on mac for now...
	const sockaddr_in* s = GetAsSockAddrIn();
	char destinationBuffer[ 128 ];
	inet_ntop( s->sin_family, &s->sin_addr, destinationBuffer, sizeof( destinationBuffer ) );

	return StringUtils::Sprintf( "%s:%d",
								destinationBuffer,
								ntohs( s->sin_port ) );
	//return string( "not implemented on mac for now" );
#endif
}
