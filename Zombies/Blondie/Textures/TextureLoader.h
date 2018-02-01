#pragma once
#include "GLtexture.h"
#include <string>

namespace BLONDIE {
	class TextureLoader
	{
	public:
		static GLTexture loadPNG(const std::string filepath);

	private:

	};
}
