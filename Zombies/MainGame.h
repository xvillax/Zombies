#pragma once


#include "Blondie\Window\GameWindow.h"
#include "Blondie\Shader\shader.h"
#include "Blondie\Camera\Camera2D.h"
#include "Blondie\InputManager\Inputmanager.h"
#include "Levels\Levels.h"
#include "Agents\Player.h"
#include "Blondie\SpriteBatch\SpriteBatch.h"

class Zombie;

enum class GameState
{
	PLAY,
	EXIT
};
class MainGame
{
public:
    MainGame();
    ~MainGame();

    /// Runs the game
    void run();

private:
    /// Initializes the core systems
    void initSystems();
    /// Initializes the shaders
    void initShaders();

	void initLevel();

    /// Main game loop for the program
    void gameLoop();

	//updates agents
	void updateAgents();

    /// Handles input processing
    void processInput();
    /// Renders the game
    void drawGame();

private:
    /// Member Variables
	float m_fps;
	int m_currentlvl;
	static constexpr int SCREEN_WIDTH = 1024;
	static constexpr int SCREEN_HEIGHT = 768;

    BLONDIE::GameWindow m_window; ///< The game window
	BLONDIE::Shader _textureProgram; ///< The shader program
	BLONDIE::InputManager _inputManager; ///< Handles input
    BLONDIE::Camera2D _camera; ///< Main Camera
	BLONDIE::SpriteBatch m_agentsSpritebatch;  // draw all agents
	GameState m_gameState;
	Player* m_Player;
	std::vector<Levels*> m_levels;  // vector of all levels
	std::vector<Human*> m_humans;  // vector of all Humans
	std::vector<Zombie*> m_zombies;  // vector of all Zombies
};

