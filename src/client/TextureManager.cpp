

#include "TextureManager.h"
#include "GraphicsDriver.h"
#include <SDL_image.h>

#include "StringUtils.h"

std::unique_ptr< TextureManager >		TextureManager::sInstance;

void TextureManager::StaticInit()
{
	sInstance.reset( new TextureManager() );
}

TextureManager::TextureManager()
{
	/* This should probably load from a config file or something */
	CacheTexture("player", "../assets/mouse2.png");
	CacheTexture("bullet", "../assets/yarn.png");
	CacheTexture("goal", "../assets/cheese.png");
	CacheTexture("ai", "../assets/player.png");
	CacheTexture("box", "../assets/box.png" );
}

TexturePtr	TextureManager::GetTexture( const string& inTextureName )
{
	return mNameToTextureMap[ inTextureName ];
}

bool TextureManager::CacheTexture( string inTextureName, const char* inFileName )
{
	SDL_Texture* texture = IMG_LoadTexture( GraphicsDriver::sInstance->GetRenderer(), inFileName );

	if( texture == nullptr )
	{
		SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Failed to load texture: %s", inFileName );
		LOG("Failed to load texture: %s", inFileName);
		return false;
	}

	int w, h;
	SDL_QueryTexture( texture, nullptr, nullptr, &w, &h );

	// Set the blend mode up so we can apply our colors
	SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );

	TexturePtr newTexture( new Texture( w, h, texture ) );

	mNameToTextureMap[ inTextureName ] = newTexture;

	return true;

}
