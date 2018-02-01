#include "Timing.h"
#include <SDL2\SDL.h>

namespace BLONDIE
{
	FpsLimiter::FpsLimiter()
	{
	}

	void FpsLimiter::init( GLfloat maxfps )
	{
		setMaxFps(maxfps);
	}

	void FpsLimiter::setMaxFps( GLfloat maxfps)
	{
		_maxFps = maxfps;
	}

	void FpsLimiter::begin()
	{
		_startTicks = (GLfloat)SDL_GetTicks();
	}

	GLfloat FpsLimiter::end()
	{
		calculateFps();

		GLfloat frameTicks = (GLfloat)SDL_GetTicks() - _startTicks;

		if (1000.0f / _maxFps > frameTicks)
			SDL_Delay(1000 / (GLuint)_maxFps - (GLuint)frameTicks);
		return _fps;
	}

	void FpsLimiter::calculateFps()
	{
		static const int NUMSAMPLES = 10;
		static  float frameTimes[NUMSAMPLES];
		static int currentFrame = 0;
		static float prevTicks = (float)SDL_GetTicks();
		float currentTicks;
		float frameTimeAverage = 0;
		int count;

		currentTicks = (float)SDL_GetTicks();

		_frametime = currentTicks - prevTicks;
		frameTimes[currentFrame % NUMSAMPLES] = _frametime;
		prevTicks = currentTicks;
		currentFrame++;

		if (currentFrame < NUMSAMPLES)
		{
			count = currentFrame;
		}
		else
		{
			count = NUMSAMPLES;
		}

		for (int i = 0; i < count; i++)
		{
			frameTimeAverage += frameTimes[i];
		}
		frameTimeAverage /= count;

		if (frameTimeAverage > 0)
		{
			_fps = 1000.0f / frameTimeAverage;
		}
		else
		{
			_fps = 60.0f;
		}
	}
}