#include "Camera2D.h"
#include <iostream>

namespace BLONDIE
{
	Camera2D::Camera2D()
		: m_position(0.0f, 0.0f),
		m_orthoMatrix(1.0f),
		m_cameraMatrix(1.0f),
		m_needsMatrixUpdate(true),
		m_screenWidth(800),
		m_screenHeight(600),
		m_Scale(1.0f)

	{
	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(GLint width, GLint height)
	{
		m_screenWidth = width;
		m_screenHeight = height;
		m_orthoMatrix = glm::ortho(0.0f, (GLfloat)m_screenWidth, 0.0f, (GLfloat)m_screenHeight);
	}
	void Camera2D::upDate()
	{
		//order is transalte // scale// rotate
		if (m_needsMatrixUpdate)
		{
			glm::vec3 m_translate(-m_position.x + m_screenWidth / 2, -m_position.y + m_screenHeight / 2, 0.0f);
			m_cameraMatrix = glm::translate(m_orthoMatrix, m_translate);

			glm::vec3 scale(m_Scale, m_Scale, 0.0f);
			m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;


			m_needsMatrixUpdate = false;
		}
	}

	glm::vec2 Camera2D::convertScreenXYtoWorldXY(glm::vec2 screencoords)
	{
		//invert y direction
		screencoords.y = m_screenHeight - screencoords.y;
		//make 0 the center of the screen
		screencoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
		// scale Coordinates
		screencoords /= m_Scale;
		// transalte with camera position
		screencoords += m_position;
		return screencoords;
	}

}