#pragma once
#include "Agents.h"
#include "Blondie\InputManager\Inputmanager.h"
class Human :
	public Agents
{
public:
	Human();
	virtual ~Human();
	virtual void update(const std::vector<std::string> & lvldata,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);
};

