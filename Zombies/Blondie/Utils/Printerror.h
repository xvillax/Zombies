#pragma once
#include <string>
#include <iostream>
#include <cstdlib>
#include <SDL2\SDL.h>

namespace BLONDIE {
	inline void PrintError(std::string errmsg)
	{
		std::cout << errmsg << std::endl;
		system("pause");
		SDL_Quit();
		exit(-1);
	}
}