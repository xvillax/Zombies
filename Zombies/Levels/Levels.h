#pragma once
#include <string>
#include <vector>
#include "Blondie\SpriteBatch\SpriteBatch.h"


const int TILEWIDTH = 64;
const int TILEHEIGHT = 64;

class Levels
{
public:
	
	//Load the Lvl
	Levels(const std::string& filename);
	~Levels();

	void Draw();
	glm::vec2 getPlayerStartPos() const { return m_playerPosStart; }
	const std::vector<glm::vec2>& getZombieStartPos() const { return m_zombiePosStart; }
	const std::vector<std::string> getLevelData() const { return m_lvlData; }
private:
	int m_numHumans;
	std::vector<std::string> m_lvlData;
	BLONDIE::SpriteBatch m_spritebatch;

	glm::vec2 m_playerPosStart;
	std::vector<glm::vec2> m_zombiePosStart;
	std::vector<glm::vec2> m_humanPosStart;
};

