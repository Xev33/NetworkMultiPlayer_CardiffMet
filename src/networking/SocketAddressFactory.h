#ifndef SOCKET_ADDRESS_FACTORY_H_
#define SOCKET_ADDRESS_FACTORY_H_

#include "SocketAddress.h"

class SocketAddressFactory
{
public:

	static SocketAddressPtr CreateIPv4FromString( const string& inString );
};

#endif
