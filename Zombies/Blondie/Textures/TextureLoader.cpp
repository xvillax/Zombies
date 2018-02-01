#include "TextureLoader.h"
#include "PecoPng.h"
#include "../Utils/IOmanager.h"
#include "../Utils/Printerror.h"

namespace BLONDIE
{
	GLTexture TextureLoader::loadPNG(const std::string filepath)
	{
		GLTexture texture = {};

		std::vector<unsigned char> in;
		std::vector<unsigned char> out;

		unsigned long width, height;

		if (IOManager::FileToBuffer(filepath, in) == false)
			PrintError("Failed to load PNG to Buffer ! ");

		int errorcode = decodePNG(out, width, height, &in[0], in.size());
		if (errorcode != 0)
			PrintError("DecodePNG Failed" + errorcode);

		glGenTextures(1, &(texture.Id));

		glBindTexture(GL_TEXTURE_2D, texture.Id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
		texture.width = width;
		texture.height = height;
		glBindTexture(GL_TEXTURE_2D, 0);
		return texture;

	}
}
