#include "Levels.h"
#include <fstream>
#include "Blondie/Utils/Printerror.h"
#include "Blondie\Utils\ReSourceManager.h"



Levels::Levels(const std::string& filename)
{
	
	std::ifstream file;
	file.open(filename);
	if (file.fail())
	{
		BLONDIE::PrintError("Failed to open Level File  " + filename);
	}

	std::string tmp;
	file >> tmp >> m_numHumans;
	
	//read in the rest of the lvl data
	while (std::getline(file, tmp))
	{
		  m_lvlData.push_back(tmp);
	}
	m_spritebatch.init();
	m_spritebatch.Begin();
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	BLONDIE::Color color = { 255,255,255,255 };
	BLONDIE::Color pcolor = { 100,55,255,255 };
	//render tiles
	for (unsigned int y = 0; y < m_lvlData.size(); y++) {
		for (unsigned int x = 0; x < m_lvlData[y].size(); x++) {
		
			//get a destination rect
			glm::vec4 destRect(x * TILEWIDTH, y * TILEWIDTH, TILEWIDTH, TILEHEIGHT);
			//get a tile
			char tile = m_lvlData[y][x];
			//process the tile
			switch (tile)
			{
			case 'B':
			case '@':
				
				m_playerPosStart.x = x * TILEWIDTH;
				m_playerPosStart.y = y * TILEHEIGHT;
				m_spritebatch.Draw(destRect, uvRect,
					BLONDIE::ResourceManager::getTexture("Textures/circle.png").Id,
					0.0f, pcolor);
				break;
			case 'R':
				m_spritebatch.Draw(destRect, uvRect,
					BLONDIE::ResourceManager::getTexture("Textures/red_bricks.png").Id,
					0.0f, color);
				break;
			case 'L':
				m_spritebatch.Draw(destRect, uvRect,
					BLONDIE::ResourceManager::getTexture("Textures/light_bricks.png").Id,
					0.0f, color);
				break;
			case '.':
				break;
			case 'G':
				m_spritebatch.Draw(destRect, uvRect,
					BLONDIE::ResourceManager::getTexture("Textures/glass.png").Id,
					0.0f, color);
				break;
			case 'Z':
				m_zombiePosStart.emplace_back(x * TILEWIDTH, y * TILEHEIGHT);
				break;
			default:
				std::printf("unexpected symbol %c at (%d,%d)", tile, x, y);
				break;
			}
		}

	}
	m_spritebatch.End();
}


Levels::~Levels()
{
}

void Levels::Draw()
{
	m_spritebatch.renderBatch();
}
