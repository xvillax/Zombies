#pragma once
#include "Human.h"
#include "Blondie\InputManager\Inputmanager.h"

class Player :
	public Human
{
public:
	Player();
	~Player();
	void init(float speed, glm::vec2 pos, BLONDIE::InputManager* inputManager);
	void update(const std::vector<std::string> & lvldata,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);
	
private:
	BLONDIE::InputManager* m_inputManager;
};

