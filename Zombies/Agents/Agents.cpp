#include "Agents.h"
#include "Blondie\Utils\ReSourceManager.h"
#include "Levels\Levels.h"


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
	//first corner
	glm::vec2 cornerpos = glm::vec2(m_position.x / (float)TILEWIDTH);
}