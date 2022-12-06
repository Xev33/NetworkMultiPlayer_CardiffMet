#include "Engine.h"

#include "World.h"
#include "Timing.h"
#include "SocketUtil.h"
#include "GameObjectRegistry.h"

#include <time.h>

#define SDL_MAIN_HANDLED

#ifndef _WIN32
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

std::unique_ptr< Engine >	Engine::sInstance;


Engine::Engine() :
mShouldKeepRunning( true )
{
	SocketUtil::StaticInit();

	srand( static_cast< uint32_t >( time( nullptr ) ) );

	GameObjectRegistry::StaticInit();


	World::StaticInit();

	/* Prepare SDL - from Year 1 Game Sys Fundamentals */

	const int SDL_OKAY = 0;

	SDL_SetMainReady(); //don't use sdl_main
	int sdlStatus = SDL_Init(SDL_INIT_EVERYTHING);
	

	if (sdlStatus != SDL_OKAY)
		throw "SDL init error";
}

Engine::~Engine()
{
	SocketUtil::CleanUp();

	SDL_Quit();
}

int Engine::Run()
{
	return DoRunLoop();
}

void Engine::HandleEvent( SDL_Event* inEvent )
{
	// Default implementation does nothing, up to derived classes to handle them, if they so choose
	 ( void )inEvent;
}

int Engine::DoRunLoop()
{
	// Main message loop
	bool quit = false;
	SDL_Event event;
	memset( &event, 0, sizeof( SDL_Event ) );

	while( !quit && mShouldKeepRunning )
	{
		if( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT )
			{
				quit = true;
			}
			else
			{
				HandleEvent( &event );
			}
		}
		else
		{
			Timing::sInstance.Update();

			DoFrame();
		}
	}

 	return event.type;
}

void Engine::DoFrame()
{
	World::sInstance->Update();
}
