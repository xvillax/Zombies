#pragma once
#include <glm\glm.hpp>
#include "Blondie\SpriteBatch\SpriteBatch.h"

const float AGENT_WIDTH = 32.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;
class Zombie;
class Human;



class Agents
{
public:
	Agents();
	virtual ~Agents();
	virtual void update(const std::vector<std::string> & lvldata,
						std::vector<Human*>& humans,
						std::vector<Zombie*>& zombies) = 0;
	void draw(BLONDIE::SpriteBatch& spriteBatch);
	glm::vec2 getPosition() const { return m_position; }
	bool tileColide(const std::vector<std::string>& lvldata);
	bool colideWithAgent(Agents* agent);
protected:
	void checkTilePos(const std::vector<std::string>& lvldata,
		              std::vector<glm::vec2>& collidetileposition,
					  float x, float y);
	void collideWithTile(glm::vec2 tilePos);
	
	glm::vec2 m_position;
	BLONDIE::Color m_color;
	float m_speed;
};

