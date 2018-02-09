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
	
	m_position += m_direction * m_speed;
	tileColide(lvldata);
}

void Human::init(float speed, glm::vec2 pos)
{
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randomDir(-1.0f, 1.0f); 

	m_color = { 200, 0, 200, 255 };
	m_speed = speed;
	m_position = pos;
	m_direction = glm::vec2(randomDir(randomEngine), randomDir(randomEngine));
	if (m_direction.length() == 0)
	{
		m_direction = glm::vec2(1.0f, 0.0f);
	}
	m_direction = glm::normalize(m_direction);
}
