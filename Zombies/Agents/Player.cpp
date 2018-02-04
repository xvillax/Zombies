#include <SDL2\SDL.h>
#include "Player.h"
#include "Blondie\InputManager\Inputmanager.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::init(float speed, glm::vec2 pos)
{
	m_speed = speed;
	m_position = pos;
	m_color = { 100,55,255,255 };
}

void Player::update(BLONDIE::InputManager& inputManager)
{
	if (inputManager.isKeyPressed(SDLK_w))
	{

	}
}
