#include "GameWindow.h"
#include "../Utils/Printerror.h"

namespace BLONDIE
{
	GameWindow::GameWindow()
	{
	}


	GameWindow::~GameWindow()
	{
	}

	GLint GameWindow::Create(std::string name, GLint width, GLint height, GLuint currentflags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;
		//create the window


		if (currentflags & INVISABLE)
			flags |= SDL_WINDOW_HIDDEN;

		if (currentflags & FULLSCREEN)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		if (currentflags & BORBERLESS)
			flags |= SDL_WINDOW_BORDERLESS;
		gameWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width, height, flags);

		if (gameWindow == nullptr)
			PrintError("SDL Window Failed to open!! ");
		// Setup Opengl Ready For Drawing to out new window
		SDL_GLContext glcontext = SDL_GL_CreateContext(gameWindow);
		if (glcontext == nullptr)
		{
			PrintError("Error Creating a GL_Contex ....");
		}

		if ((glewInit() != GLEW_OK))
		{
			PrintError("Error Initalizing glew ....");
		}

		// Check what version of OpenGL is on the system
		std::printf("***   OpenGL Version: %s  *** \n", glGetString(GL_VERSION));

		//set the background color
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		//enable/disable  V-Sync
		SDL_GL_SetSwapInterval(1);

		//enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void GameWindow::SwapBuffer()
	{
		SDL_GL_SwapWindow(gameWindow);
	}
}