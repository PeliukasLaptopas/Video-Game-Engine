#pragma once

#include <SDL\SDL.h>
#include "Input.h"
#include <iostream>
#include "Vertex.h"
#define FRAME_VALUES 10
#define MAX_PHYSICS_STEPS 3 //Max physics steps that we will simulate during lower than 60 fps
#define DESIRED_FRAME_TIME 1000/60

using namespace std;
namespace Eng {
class Window
{
public:

	enum GameState
	{
		PLAY,
		EXIT
	};

	Window(void) {}
	Window(char* title, int width, int height, Color background, int xPos = SDL_WINDOWPOS_CENTERED, int yPos = SDL_WINDOWPOS_CENTERED);
	~Window(void);

	Input input;


	/*!!!!!!!!!!!!!
	 //Game happens like this: 

	 while(window.opened())
	 {
		//draw game
		SDL_GL_SwapWindow(window.getWindow());
	 }

	 thats it
	  !!!!!!!!!!!!!*/
	bool opened();
	bool physics();

	char* title() {
		return _title;
	}

	int width() {
		return _width;
	}

	int height() {
		return _height;
	}

	int xPos() {
		return _xPos;
	}

	int yPos() {
		return _yPos;
	}

	GameState gameState()
	{
		return _gameState;
	}

	SDL_Window* getWindow()
	{
		return _window;
	}
	float getFPS()
	{
		return _fps;
	}
	float getDeltaTime()
	{
		return _deltaTime;
	}
	

private:
	void limitFPS();

	char* _title;
	int _width;
	int _height;
	int _xPos;
	int _yPos;
	SDL_Window *_window;
	GameState _gameState;
	bool _opened;

	double _startFrameTicks; //while window is opened calculate start ticks
	//And when all calculations in one frame are done measure the difference in ticks

	//Calculate delta time here
	double _previousTicks;
	double _totalDeltaTime;

	void initFPSCounter();
	void calculateFPS();
	// An array to store frame times:
	Uint32 _frameTimes[FRAME_VALUES];
	// Last calculated SDL_GetTicks
	Uint32 _prevFrameTime;
	// total frames rendered
	Uint32 _frameCount;
	// the value you want
	float _fps;

	int _currentPhysicsStep = 0;
	float _deltaTime = 1.0f;

	void inputProcessing();
};
}