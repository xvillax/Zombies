#include "Human.h"
#include <random>
#include <ctime>

Human::Human()
{
}


Human::~Human()
{
}

void Human::update(const std::vector<std::string> & lvldata,
					std::vector<Human*>& humans,
					std::vector<Zombie*>& zombies)
{
	
	tileColide(lvldata);
}

void Human::init(float speed, glm::vec2 pos)
{
	static std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));
	static std::uniform_real_distribution<float>(0.01f, 1.0f);
	m_speed = speed;
	m_position = pos;
	m_direction = 
}
