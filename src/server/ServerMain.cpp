
#ifndef _WIN32
#include <SDL2/SDL.h>
#else
#define SDL_MAIN_HANDLED
#include <SDL.h>
#endif

#include "Server.h"

#if _WIN32
#include <Windows.h>
#endif



#if _WIN32
int main(int argc, const char** argv)
{
	SDL_SetMainReady();
	if( Server::StaticInit() )
	{
		return Server::sInstance->Run();
	}
	else
	{
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

	if( Server::StaticInit() )
	{
		return Server::sInstance->Run();
	}
	else
	{
		//error
		return 1;
	}
}
#endif
