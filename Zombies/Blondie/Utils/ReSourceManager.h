#pragma once

#include "TextureCache.h"

namespace BLONDIE {
	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string texturepath);


	private:
		static TextureCache m_textureCache;
	};
}