#pragma once
#include "Agents.h"
class Zombie :
	public Agents
{
public:
	Zombie();
	~Zombie();
	virtual void update();
};

