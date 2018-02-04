#include "Agents.h"
#include "Blondie\Utils\ReSourceManager.h"


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
