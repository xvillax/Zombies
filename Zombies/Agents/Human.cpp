#include "Human.h"
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>

Human::Human()
	: m_frames(0)
{
}


Human::~Human()
{
}

void Human::update(const std::vector<std::string> & lvldata,
					std::vector<Human*>& humans,
					std::vector<Zombie*>& zombies)
{
	
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randRotate(-40.8f, 40.8f);

	m_position += m_direction * m_speed;
	
	if (m_frames == 100) 
	{
		m_direction = glm::rotate(m_direction, randRotate(randomEngine));
		m_frames = 0;
	}
	else
		m_frames++;

	if(tileColide(lvldata))
		m_direction = glm::rotate(m_direction, randRotate(randomEngine));
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
