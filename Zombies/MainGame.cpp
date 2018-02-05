#include "MainGame.h"
#include "Blondie\Window\Blondie.h"
#include <SDL2/SDL.h>
#include "Blondie/Timers/Timing.h"


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
	m_window.Create("Zombies", WIDTH, HEIGHT, 0);
	initShaders();
	m_agentsSpritebatch.init();
	_camera.init(WIDTH, HEIGHT);
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
	m_Player->init(1.0f, m_levels[m_currentlvl]->getPlayerStartPos(), &_inputManager);
	m_humans.push_back(m_Player);
}

void MainGame::gameLoop() {
	BLONDIE::FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFps(60);
	
	while (m_gameState == GameState::PLAY)
	{
		fpsLimiter.begin();

		processInput();



		_camera.upDate();

		drawGame();

		fpsLimiter.end();
	}
}

void MainGame::updateAgents()
{
	for (unsigned int i = 0; i < m_humans.size(); i++)
		m_humans[i]->update();
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
	m_agentsSpritebatch.End();
	m_agentsSpritebatch.renderBatch();

	_textureProgram.Unuse();
	//Swap our buffer and draw everything to the screen!
	m_window.SwapBuffer();
}