#include "TextureCache.h"
#include "../Textures/TextureLoader.h"
#include <iostream>

namespace BLONDIE
{
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturepath)
	{
		// lookup map to see if texture has been stored
		auto map_itter = m_textureMap.find(texturepath);

		//if it has not been stored all ready
		if (map_itter == m_textureMap.end())
		{
			//load a texture
			GLTexture newTexture = TextureLoader::loadPNG(texturepath);
			//insert into the map 
			m_textureMap.insert(make_pair(texturepath, newTexture));

			//std::cout << "Loaded Texture" << std::endl;
			return newTexture;
		}
		// if the texture hase been stored just return the texture
		//std::cout << "used Cached Texture" << std::endl;
		return map_itter->second;
	}
}
