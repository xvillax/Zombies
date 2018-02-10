#pragma once
#include "Agents.h"

class Human :
	public Agents
{
public:
	Human();
	virtual ~Human();

	virtual void update(const std::vector<std::string> & lvldata,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);

	void init(float speed, glm::vec2 pos);

private:
	glm::vec2 m_direction;
	int m_frames;
};

