
#include "Client.h"

#if _WIN32
#include <Windows.h>
#endif

#if _WIN32 
int main(int argc, const char** argv)	
{
	if( Client::StaticInit() )
	{
		return Client::sInstance->Run();
	}
	else
	{
		SDL_Quit();
		//error
		return 1;
	}

}
#else 
const char** __argv;
int __argc;
int main(int argc, const char** argv)
{
	__argc = argc;
	__argv = argv;

	if( Client::StaticInit() )
	{
		return Client::sInstance->Run();
	}
	else
	{
		SDL_Quit();
		//error
		return 1;
	}
}
#endif
