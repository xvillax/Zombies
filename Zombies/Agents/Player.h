#pragma once
#include "Human.h"
class Player :
	public Human
{
public:
	Player();
	~Player();
	void init(float speed, glm::vec2 pos, BLONDIE::InputManager* inputManager);
	void update();
private:
	BLONDIE::InputManager* m_inputManager;
};

