#include "Zombie.h"
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>


Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}

void Zombie::update(const std::vector<std::string> & lvldata,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies)
{
}

void Zombie::init(float speed, glm::vec2 pos)
{
	/*static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randomDir(-1.0f, 1.0f);*/

	m_color = { 0, 168, 0, 255 };
	m_speed = speed;
	m_position = pos;
	/*m_direction = glm::vec2(randomDir(randomEngine), randomDir(randomEngine));
	if (m_direction.length() == 0)
	{
		m_direction = glm::vec2(1.0f, 0.0f);
	}
	m_direction = glm::normalize(m_direction);*/
}
