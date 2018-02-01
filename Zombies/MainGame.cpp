#include "MainGame.h"
#include <SDL2/SDL.h>


MainGame::MainGame(){
    // Empty
}

MainGame::~MainGame() 
{
	// Empty
}

void MainGame::run() {
	// Empty
}

void MainGame::initSystems() {
	// Empty
}

void MainGame::initShaders() {
    // Compile our color shader
	_textureProgram.CreateShaders("Resources/Shaders/vertexShader.vs", "Resources/Shaders/fragmentShader.fs");
	_textureProgram.AddAttrib("vertexPosition");
	_textureProgram.AddAttrib("vertexColor");
	_textureProgram.AddAttrib("vertexUV");
	_textureProgram.LinkShaders();
}

void MainGame::gameLoop() {
	// Empty
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

	//Draw code goes here

	//Swap our buffer and draw everything to the screen!
	_window.SwapBuffer();
}