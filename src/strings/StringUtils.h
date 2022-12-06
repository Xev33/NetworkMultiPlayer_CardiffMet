#ifndef STRING_UTILS
#define STRING_UTILS

#include <string>
using std::string;

namespace StringUtils
{
	string GetCommandLineArg( int inIndex );

	string Sprintf( const char* inFormat, ... );

	void	Log( const char* inFormat );
	void	Log( const char* inFormat, ... );
}

#define LOG( ... ) StringUtils::Log( __VA_ARGS__ );

#endif
