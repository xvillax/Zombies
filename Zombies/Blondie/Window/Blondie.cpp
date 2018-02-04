#include "Blondie.h"
#include <SDL2\SDL.h>
#include <gl\glew.h>


int BLONDIE::Init()
{
	// Set up SDL and  Create a Window
	SDL_Init(SDL_INIT_EVERYTHING);	

	//Set a double buffer Window
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	return 0;
}

