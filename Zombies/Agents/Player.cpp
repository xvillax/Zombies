#include <SDL2\SDL.h>
#include "Player.h"
#include "Blondie\InputManager\Inputmanager.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::init(float speed, glm::vec2 pos, BLONDIE::InputManager* inputManager)
{
	m_inputManager = inputManager;
	m_speed = speed;
	m_position = pos;
	m_color = { 100,55,255,255 };
}

void Player::update()
{
	if (m_inputManager->isKeyPressed(SDLK_w))
	{
		m_position.y += m_speed;
	}
	else
	if (m_inputManager->isKeyPressed(SDLK_s))
	{
		m_position.y -= m_speed;
	}
	else
	if (m_inputManager->isKeyPressed(SDLK_a))
	{
		m_position.x += m_speed;
	}
	else
	if (m_inputManager->isKeyPressed(SDLK_d))
	{
		m_position.x -= m_speed;
	}
}
