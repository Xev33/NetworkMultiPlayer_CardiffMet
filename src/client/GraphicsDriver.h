#ifndef GRAPHICS_DRIVER_H
#define GRAPHICS_DRIVER_H

#ifndef _WIN32
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <memory>

class GraphicsDriver
{
public:

	static bool StaticInit( SDL_Window* inWnd );

	static std::unique_ptr< GraphicsDriver >		sInstance;

	void					Clear();
	void					Present();
	SDL_Rect&				GetLogicalViewport();
	SDL_Renderer*			GetRenderer();

	~GraphicsDriver();

private:

	GraphicsDriver();
	bool Init( SDL_Window* inWnd );

	SDL_Renderer*			mRenderer;
	SDL_Rect				mViewport;
};

#endif // GRAPHICS_DRIVER_H
