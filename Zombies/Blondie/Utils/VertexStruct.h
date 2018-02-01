#pragma once
#include <gl\glew.h>

namespace BLONDIE {
	struct Position
	{
		float x;
		float y;
	};
	struct Color
	{
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};
	struct UV
	{
		GLfloat u;
		GLfloat v;
	};

	// vertext definition
	struct Vertex
	{

		Position position;
		Color color;
		UV uv;
		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}
		void setUV(GLfloat u, GLfloat v)
		{
			uv.u = u;
			uv.v = v;
		}
		void setPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}
	};
}
