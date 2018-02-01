#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <gl\glew.h>

namespace BLONDIE
{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();
		void init(GLint width, GLint height);
		void upDate();
		glm::vec2 convertScreenXYtoWorldXY(glm::vec2 screencoords);

		// Setters
		void setPosition(const glm::vec2& newPosition) {
			m_position = newPosition; m_needsMatrixUpdate = true; }

		void setScale(GLfloat newScale) { m_Scale = newScale; m_needsMatrixUpdate = true; }

		//Getters
		glm::vec2 getPosition() { return m_position; }
		GLfloat getScale() { return m_Scale; }
		glm::mat4 getcameraMatrix() { return m_cameraMatrix; }


	private:
		GLint m_screenWidth;
		GLint m_screenHeight;
		bool m_needsMatrixUpdate;
		GLfloat m_Scale;
		glm::vec2 m_position;
		glm::mat4 m_cameraMatrix;
		glm::mat4 m_orthoMatrix;
	};
}
