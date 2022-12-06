#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <memory>

#ifndef _WIN32
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

class WindowManager
{

public:

	static bool StaticInit();
	static std::unique_ptr< WindowManager >	sInstance;

	SDL_Window*		GetMainWindow()	const	{ return mMainWindow; }

	~WindowManager();
private:
	WindowManager( SDL_Window* inMainWindow );

	SDL_Window*				mMainWindow;
};

#endif
