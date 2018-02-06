#pragma once
#include "Agents.h"
class Zombie :
	public Agents
{
public:
	Zombie();
	~Zombie();
	virtual void update(const std::vector<std::string> & lvldata,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);
};

