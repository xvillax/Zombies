#pragma once
#include <string>
#include <vector>

class Levels
{
public:
	
	//Load the Lvl
	Levels(const std::string& filename);
	~Levels();

	void Draw();

private:
	std::vector<std::string> m_lvlData;
	int m_numHumans;
};

