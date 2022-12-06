#ifndef TEXTURE_H_
#define TEXTURE_H_

#ifndef _WIN32
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <memory>
using std::shared_ptr;

class Texture
{
public:
	Texture( uint32_t inWidth, uint32_t inHeight, SDL_Texture* inTexture );
	~Texture();

	uint32_t	GetWidth()	const	{ return mWidth; }
	uint32_t	GetHeight()	const	{ return mHeight; }
	SDL_Texture* GetData() const	{ return mTexture; }

private:
	uint32_t		mWidth;
	uint32_t		mHeight;
	SDL_Texture*	mTexture;
};


typedef shared_ptr< Texture >	TexturePtr;

#endif //TEXTURE_H_
