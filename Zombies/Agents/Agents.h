#pragma once
#include <glm\glm.hpp>
#include "Blondie\SpriteBatch\SpriteBatch.h"

const float AGENT_WIDTH = 60;
class Agents
{
public:
	Agents();
	virtual ~Agents();
	void draw(BLONDIE::SpriteBatch& spriteBatch);
protected:
	glm::vec2 m_position;
	BLONDIE::Color m_color;
	float m_speed;
};

