#pragma once


#include "Blondie\Window\GameWindow.h"
#include "Blondie\Shader\shader.h"
#include "Blondie\Camera\Camera2D.h"
#include "Blondie\InputManager\Inputmanager.h"
#include "Levels\Levels.h"


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

    /// Main game loop for the program
    void gameLoop();
    /// Handles input processing
    void processInput();
    /// Renders the game
    void drawGame();

private:
    /// Member Variables
    BLONDIE::GameWindow _window; ///< The game window
	BLONDIE::Shader _textureProgram; ///< The shader program
	BLONDIE::InputManager _inputManager; ///< Handles input
    BLONDIE::Camera2D _camera; ///< Main Camera

	std::vector<Levels*> m_levels;  // vector of all levels
};

