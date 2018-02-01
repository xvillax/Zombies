#pragma once
#include <map>
#include "../Textures/GLTexture.h"

namespace BLONDIE {
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();
		GLTexture getTexture(std::string texturepath);

	private:
		std::map<std::string, GLTexture> m_textureMap;
	};
}
