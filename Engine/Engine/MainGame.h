#pragma once

#include <SDL\SDL.h>
#include "Window.h"

namespace Eng {
class MainGame
{
public:

	MainGame(void) {}
	MainGame(char* title, int width, int height, int xPos = SDL_WINDOWPOS_CENTERED, int yPos = SDL_WINDOWPOS_CENTERED);
	~MainGame(void);

	Window getWindow()
	{
		return window;
	}

private:
	Window window;
};
}