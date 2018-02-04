#include "Player.h"



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

void Player::update()
{
}
