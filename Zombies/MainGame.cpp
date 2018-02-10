#include "MainGame.h"
#include "Blondie\Window\Blondie.h"
#include <SDL2/SDL.h>
#include "Blondie/Timers/Timing.h"
#include "Agents\Zombie.h"
#include <random>
#include <ctime>

const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 2.0f;

MainGame::MainGame()
    :m_gameState(GameState::PLAY),
	m_fps(0),
	m_currentlvl(0),
	m_Player(nullptr)
{
}

MainGame::~MainGame() 
{
	for (unsigned int i = 0; i < m_levels.size(); i++)
		delete m_levels[i];
}

void MainGame::run() {
	
	initSystems();
	initLevel();
	gameLoop();
}

void MainGame::initSystems() {

	BLONDIE::Init();
	m_window.Create("Zombies", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	initShaders();
	m_agentsSpritebatch.init();
	_camera.init(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void MainGame::initShaders()
{

    // Compile our color shader
	_textureProgram.CreateShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	_textureProgram.AddAttrib("vertexPosition");
	_textureProgram.AddAttrib("vertexColor");
	_textureProgram.AddAttrib("vertexUV");
	_textureProgram.LinkShaders();
}

void MainGame::initLevel()
{
	//Load lvl one
	m_levels.push_back(new Levels("Levels/level1.txt"));
	m_currentlvl = 0;

	m_Player = new Player;
	m_Player->init(4.0f, m_levels[m_currentlvl]->getPlayerStartPos(), &_inputManager);
	m_humans.push_back(m_Player);

	static std::mt19937 randomEngine;
	randomEngine.seed((int)time(nullptr));
	static std::uniform_int_distribution<int> randX(2, m_levels[m_currentlvl]->getWidth() - 2);
	static std::uniform_int_distribution<int> randY(2, m_levels[m_currentlvl]->getHeight() - 2);

	
	//add all the Humans
	for(int i = 0; i < m_levels[m_currentlvl]->getNumHumans(); i++)
	{
		m_humans.push_back(new Human);
		glm::vec2 pos(randX(randomEngine) * TILEWIDTH, randY(randomEngine) * TILEWIDTH);
		m_humans.back()->init(HUMAN_SPEED, pos);
	}

	//add the zombies
	const std::vector<glm::vec2>& zombiePositions = 
					m_levels[m_currentlvl]->getZombieStartPos();
	for (unsigned int i = 0; i < zombiePositions.size(); i++) 
	{
		m_zombies.push_back(new Zombie);
		m_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
	}
}

void MainGame::gameLoop() {
	BLONDIE::FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFps(60);
	
	while (m_gameState == GameState::PLAY)
	{
		fpsLimiter.begin();

		processInput();
		updateAgents();
		_camera.setPosition(m_Player->getPosition());

		_camera.upDate();

		drawGame();

		fpsLimiter.end();
	}
}

void MainGame::updateAgents()
{
	//update all Humans
	for (unsigned int i = 0; i < m_humans.size(); i++)
		m_humans[i]->update(m_levels[m_currentlvl]-> getLevelData(),
			m_humans, m_zombies);

	//update Zombies
	for (unsigned int i = 0; i < m_zombies.size(); i++)
		m_zombies[i]->update(m_levels[m_currentlvl]->getLevelData(),
			m_humans, m_zombies);

	//update human collisons
	for (unsigned int i = 0; i < m_humans.size(); i++)
	{
		//collide with other humans
		for (unsigned int j = i + 1; j < m_humans.size(); j++)
		{
			m_humans[i]->colideWithAgent(m_humans[j]);
		}
	}

	//update zombie collisons
	for (unsigned int i = 0; i < m_zombies.size(); i++)
	{
		//collide with zombies
		for (unsigned int j = i + 1; j < m_zombies.size(); j++)
		{
			m_zombies[i]->colideWithAgent(m_zombies[j]);
		}
		//collide with humans
		for (unsigned int j = i + 1; j < m_humans.size(); j++)
		{
			if (m_zombies[i]->colideWithAgent(m_humans[j])) //if a human and zombie collide
			{
				//add a new zombie
				m_zombies.push_back(new Zombie);
				m_zombies.back()->init(ZOMBIE_SPEED, m_humans[j]->getPosition());
				//delete the human
				delete m_humans[j];
				m_humans[j] = m_humans.back();
				m_humans.pop_back();
			}
		}
	}
}

void MainGame::processInput() {
    SDL_Event evnt;

    //Will keep looping until there are no more events to process
    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                //Exit the game here!
                break;
            case SDL_MOUSEMOTION:
                _inputManager.setMouseCoords((GLfloat)evnt.motion.x, (GLfloat)evnt.motion.y);
                break;
            case SDL_KEYDOWN:
				_inputManager.PressKey(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
				_inputManager.ReleaseKey(evnt.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
				_inputManager.PressKey(evnt.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
				_inputManager.ReleaseKey(evnt.button.button);
                break;
        }
    
	}

}

void MainGame::drawGame() {
    // Set the base depth to 1.0
    glClearDepth(1.0);
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_textureProgram.Use();
	//Draw code goes here
	glActiveTexture(GL_TEXTURE0);

	//make sure shader uses Texture 0
	GLint textureUniform = _textureProgram.GetUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	glm::mat4 projectionMatrix = _camera.getcameraMatrix();
	GLint pUniform = _textureProgram.GetUniformLocation("transformationMatrix");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	//draw the level
	m_levels[m_currentlvl]->Draw();

	//draw agents
	m_agentsSpritebatch.Begin();
	//draw the Humans
	for(unsigned int i= 0; i < m_humans.size(); i++)
	 m_humans[i]->draw(m_agentsSpritebatch);
	//draw the zombies
	for (unsigned int i = 0; i < m_zombies.size(); i++)
		m_zombies[i]->draw(m_agentsSpritebatch);

	m_agentsSpritebatch.End();
	m_agentsSpritebatch.renderBatch();

	_textureProgram.Unuse();
	//Swap our buffer and draw everything to the screen!
	m_window.SwapBuffer();
}