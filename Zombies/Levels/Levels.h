#pragma once
#include <string>
#include <vector>
#include "Blondie\SpriteBatch\SpriteBatch.h"


const float TILEWIDTH = 64;
const float TILEHEIGHT = 64;

class Levels
{
public:
	
	//Load the Lvl
	Levels(const std::string& filename);
	~Levels();

	void Draw();
	int getWidth() const { return m_lvlData[0].size(); }
	int getHeight() const { return m_lvlData.size(); }
	int getNumHumans() { return m_numHumans; }
	const std::vector<glm::vec2>& getZombieStartPos() const { return m_zombiePosStart; }
	const std::vector<std::string> getLevelData() const { return m_lvlData; }
	glm::vec2 getPlayerStartPos() const { return m_playerPosStart; }
private:
	int m_numHumans;
	std::vector<std::string> m_lvlData;
	BLONDIE::SpriteBatch m_spritebatch;

	glm::vec2 m_playerPosStart;
	std::vector<glm::vec2> m_zombiePosStart;
	std::vector<glm::vec2> m_humanPosStart;
};

