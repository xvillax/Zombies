#include "ResourceManager.h"

namespace BLONDIE
{
	TextureCache ResourceManager::m_textureCache;

	GLTexture ResourceManager::getTexture(std::string texturepath)
	{
		return m_textureCache.getTexture(texturepath);
	}
}