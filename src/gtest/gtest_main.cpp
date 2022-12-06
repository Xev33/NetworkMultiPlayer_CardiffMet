
#include <cstdlib>


#include <limits.h>

#include "gtest/gtest.h"

#ifndef _WIN32
char** __argv;
int __argc;
#endif

#define SDL_MAIN_HANDLED

#ifndef _WIN32
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#if _WIN32
#include <Windows.h>
#endif

#if _WIN32
int main(int argc, char** argv)
{
	
	::testing::InitGoogleTest(&__argc, __argv);
	return RUN_ALL_TESTS();

}
#else
int main(int argc, char** argv)
{
	__argc = argc;
	__argv = argv;
	
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
#endif