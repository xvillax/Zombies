#include "Sprite2D.h"
#include "..\Utils\Printerror.h"
#include "../Utils/ReSourceManager.h"
#include "../Utils/VertexStruct.h"
#include <cstddef>
namespace BLONDIE
{
	BLONDIE::Sprite2D::Sprite2D()
		: m_vboID(0),
		m_S2dX(0.0),
		m_S2dY(0.0),
		m_S2dWidth(0.0),
		m_S2dHeight(0.0)
	{
	}

	BLONDIE::Sprite2D::~Sprite2D()
	{
		//free up Vram
		if (m_vboID != 0)
			glDeleteBuffers(1, &m_vboID);
	}

	void BLONDIE::Sprite2D::Init2D(GLfloat x, GLfloat y, GLfloat width, GLfloat height, std::string texturepath)
	{
		m_S2dX = x;
		m_S2dY = y;
		m_S2dWidth = width;
		m_S2dHeight = height;

		m_Texture = ResourceManager::getTexture(texturepath);

		//create  a vertex buffer object
		if (m_vboID == 0)
		{
			glGenBuffers(1, &m_vboID);
		}
		else
			PrintError(" VBO Buffer Allready Created");

		Vertex vertexdata[6];

		//// triangle 1 /////////
		vertexdata[0].setPosition(x + width, y + height);
		vertexdata[0].setUV(1.0f, 1.0f);

		vertexdata[1].setPosition(x, y + height);
		vertexdata[1].setUV(0.0f, 1.0f);

		vertexdata[2].setPosition(x, y);
		vertexdata[2].setUV(0.0f, 0.0f);

		//// triangel 2 ///////
		vertexdata[3].setPosition(x, y);
		vertexdata[3].setUV(0.0f, 0.0f);

		vertexdata[4].setPosition(x + width, y);
		vertexdata[4].setUV(1.0f, 0.0f);

		vertexdata[5].setPosition(x + width, y + height);
		vertexdata[5].setUV(1.0f, 1.0f);

		for (int i = 0; i < 6; i++)
		{
			vertexdata[i].setColor(255, 0, 255, 255);

		}
		vertexdata[1].setColor(0, 0, 255, 255);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexdata), vertexdata, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BLONDIE::Sprite2D::DrawSptite2D()
	{
		glBindTexture(GL_TEXTURE_2D, m_Texture.Id);

		//Bind the vertex buffer object
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

		//tell opengl we want to use the first attribute array
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//point opengl to our vboID for position
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		//point opengl to our vboID for color
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//draw out vertex data to the screen
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}