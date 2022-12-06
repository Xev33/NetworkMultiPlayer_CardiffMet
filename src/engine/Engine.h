#ifndef ENGINE_H_
#define ENGINE_H_

#ifndef _WIN32
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <memory>

class Engine
{
public:

	virtual ~Engine();
	static std::unique_ptr< Engine >	sInstance;

	virtual int		Run();
	void			SetShouldKeepRunning( bool inShouldKeepRunning ) { mShouldKeepRunning = inShouldKeepRunning; }
	virtual void	HandleEvent( SDL_Event* inEvent );

protected:

	Engine();

	virtual void DoFrame();

private:

			int		DoRunLoop();

			bool	mShouldKeepRunning;
};

#endif // ENGINE_H_
