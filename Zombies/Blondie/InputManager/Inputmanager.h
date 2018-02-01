#pragma once
#include <gl\glew.h>
#include <glm\glm.hpp>
#include <unordered_map>

namespace BLONDIE
{
	class InputManager {
	public:
		InputManager();
		~InputManager();

		void PressKey(GLuint keyID);
		void ReleaseKey(GLuint keyID);
		bool isKeyPressed(GLuint keyID);
		void setMouseCoords(GLfloat x, GLfloat y);
		glm::vec2 getMouseCoords() const { return m_mouseCoords; }

	private:
		std::unordered_map<GLuint, bool> _keyMap;
		glm::vec2 m_mouseCoords;
	};
}