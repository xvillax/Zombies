#pragma once

#include <SDL2/SDL.h>
#include <gl\glew.h>
#include <string>

namespace BLONDIE {
	enum WindowFlags
	{
		INVISABLE = 0x1,
		FULLSCREEN = 0x2,
		BORBERLESS = 0x4
	};

	class GameWindow
	{
	public:
		GameWindow();
		~GameWindow();

		GLint Create(std::string name, GLint width, GLint height, GLuint currentflags);
		void SwapBuffer();
		GLint getScreenWidth() { return m_Width; }
		GLint getScreenHeight() { return m_Height; }
	private:
		SDL_Window * gameWindow;
		GLint m_Width;
		GLint m_Height;
	};
}
