#pragma once
#include <gl\glew.h>

namespace BLONDIE
{

	class FpsLimiter
	{
	public:
		FpsLimiter();

		void init(GLfloat maxfps);
		void setMaxFps(GLfloat maxfps);

		void begin();
		GLfloat end(); // will return the current FPS

	private:
		GLfloat	_maxFps;
		GLfloat _startTicks;
		GLfloat _fps;
		GLfloat _frametime;
		void calculateFps();
	};

}