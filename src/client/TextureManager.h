#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "Texture.h"

#include <string>
using std::string;

#include <memory>

#include <unordered_map>
using std::unordered_map;

class TextureManager
{
public:
	static void StaticInit();

	static std::unique_ptr< TextureManager >		sInstance;

	TexturePtr	GetTexture( const string& inTextureName );

private:
	TextureManager();

	bool CacheTexture( string inName, const char* inFileName );

	unordered_map< string, TexturePtr >	mNameToTextureMap;
};

#endif
