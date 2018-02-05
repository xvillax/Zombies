#pragma once
#include "Agents.h"
#include "Blondie\InputManager\Inputmanager.h"
class Human :
	public Agents
{
public:
	Human();
	virtual ~Human();
	virtual void update();
};

