#include "Inputmanager.h"

namespace BLONDIE
{
	InputManager::InputManager()
	{

	}

	InputManager::~InputManager()
	{

	}

	void InputManager::PressKey(GLuint keyID)
	{
		_keyMap[keyID] = true;
	}

	void InputManager::ReleaseKey(GLuint keyID)
	{
		_keyMap[keyID] = false;
	}

	bool InputManager::isKeyPressed(GLuint keyID)
	{
		auto it = _keyMap.find(keyID);
		if (it != _keyMap.end())
			return it->second;
		else
			return false;
	}

	void InputManager::setMouseCoords(GLfloat x, GLfloat y)
	{
		m_mouseCoords.x = x;
		m_mouseCoords.y = y;
	}

}