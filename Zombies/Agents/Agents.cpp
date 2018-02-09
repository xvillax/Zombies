#include "Agents.h"
#include "Blondie\Utils\ReSourceManager.h"
#include "Levels\Levels.h"
#include <algorithm>


Agents::Agents()
{
}


Agents::~Agents()
{
}

void Agents::draw(BLONDIE::SpriteBatch & spriteBatch)
{
	static int textureID = BLONDIE::ResourceManager::getTexture("Textures/circle.png").Id;
	glm::vec4 destRect;
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	
	destRect.x = m_position.x;
	destRect.y = m_position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	spriteBatch.Draw(destRect, uvRect, textureID, 0.0f, m_color);
}

void Agents::tileColide(const std::vector<std::string>& lvldata)
{
	std::vector<glm::vec2> collideTilePosition;
	
	// check the 4 corners
	//corner1
	checkTilePos(lvldata, collideTilePosition, 
				m_position.x, 
				m_position.y);
	//corner2
	checkTilePos(lvldata, collideTilePosition, 
				m_position.x + AGENT_WIDTH, 
		        m_position.y);
	//corner3
	checkTilePos(lvldata, collideTilePosition, 
			    m_position.x, 
				m_position.y + AGENT_WIDTH);
	//corner4
	checkTilePos(lvldata, collideTilePosition, 
		         m_position.x + AGENT_WIDTH, 
		         m_position.y + AGENT_WIDTH);

	//do the collision
	for (unsigned int i = 0; i < collideTilePosition.size(); i++)
	{
		collideWithTile(collideTilePosition[i]);
	}
}

void Agents::checkTilePos(const std::vector<std::string>& lvldata, 
						  std::vector<glm::vec2>& collidetileposition, float x, float y)
{
	glm::vec2 cornerpos = glm::vec2(floor(x / (float)TILEWIDTH),
									floor(y / (float)TILEWIDTH));

	if (cornerpos.x < 0 || cornerpos.x > lvldata[0].length() ||
		cornerpos.y < 0 || cornerpos.y > lvldata.size())
	{
		return;
	}
	if (lvldata[cornerpos.y][cornerpos.x] != '.')
	{
		collidetileposition.push_back(cornerpos * (float)TILEWIDTH + 
			                          glm::vec2((float)TILEWIDTH / 2.0f));
	}
}
//AABB Colision
void Agents::collideWithTile(glm::vec2 tilePos)
{
	const float AGENT_RADIUS = (float)AGENT_WIDTH / 2.0f;
	const float TILE_RADIUS = (float)TILEWIDTH / 2.0f;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	glm::vec2 centerPlayerPos = m_position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distvec = centerPlayerPos - tilePos;

	float xdepth = MIN_DISTANCE - abs(distvec.x);
	float ydepth = MIN_DISTANCE - abs(distvec.y);
	

	if (xdepth > 0 || ydepth > 0) // True if colliding
	{

		if (std::max(xdepth, 0.0f) < std::max(ydepth, 0.0f))
		{
			if (distvec.x < 0)
			{
				m_position.x -= xdepth;
			}else {

				m_position.x += xdepth;
			}		
		}
		else {

			if (distvec.y < 0)
			{
				m_position.y -= ydepth;
			}
			else
				m_position.y += ydepth;
		}
	}
}
