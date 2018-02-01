#pragma once
#include <gl\glew.h>
#include "../Textures/GLtexture.h"
#include <string>

namespace BLONDIE {
	class Sprite2D
	{
	public:
		Sprite2D();
		~Sprite2D();
		void Init2D(GLfloat x, GLfloat y, GLfloat width, GLfloat height, std::string texturepath);
		void DrawSptite2D();
	private:
		GLuint m_vboID;
		GLfloat m_S2dX;
		GLfloat m_S2dY;
		GLfloat m_S2dWidth;
		GLfloat m_S2dHeight;
		GLTexture m_Texture;
	};
}
