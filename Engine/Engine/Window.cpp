#include "Window.h"
#include "error.h"
#include <iostream>
#include <GL\glew.h>
#include <algorithm>
#include <GLM\glm.hpp>

using namespace glm;
using namespace std;
using namespace Eng;

Window::Window(char* title, int width, int height, Color background, int xPos, int yPos)
{
	_title = title;
	_width = width;
	_height = height;
	_xPos = xPos;
	_yPos = yPos;

	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow(title, xPos, yPos, width, height, SDL_WINDOW_OPENGL);

	if(_window == NULL)
	{
		_gameState = GameState::EXIT;
		_opened = false;
		errorMessage("Window could not be created!");
	}
	
	_opened = true;
	_gameState = GameState::PLAY;

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	glClearColor(background.r, background.g, background.b, background.a);

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		errorMessage("Could not initialize GLEW!");
	}

	initFPSCounter();

	_previousTicks = SDL_GetTicks();
	_startFrameTicks = _previousTicks;
}

void Window::initFPSCounter()
{
	_frameCount = 0;
	_fps = 0;
	_prevFrameTime = SDL_GetTicks();
}

void Window::calculateFPS()
{
	static Uint32 frametimesindex;
	static Uint32 getticks;
	static Uint32 count;
	static Uint32 i;
	
	// frametimesindex is the position in the array. It ranges from 0 to FRAME_VALUES.
	// This value rotates back to 0 after it hits FRAME_VALUES.
	frametimesindex = _frameCount % FRAME_VALUES;

	// store the current time
	getticks = SDL_GetTicks();
	// save the frame time value
	_frameTimes[frametimesindex] = getticks - _prevFrameTime;
	// save the last frame time for the next fpsthink
	_prevFrameTime = getticks;
	// increment the frame count
	_frameCount++;

	// Work out the current framerate
	// The code below could be moved into another function if you don't need the value every frame.
	// I've included a test to see if the whole array has been written to or not. This will stop
	// strange values on the first few (FRAME_VALUES) frames.
	if (_frameCount < FRAME_VALUES) {
		count = _frameCount;
	}
	else {
		count = FRAME_VALUES;
	}

	// add up all the values and divide to get the average frame time.
	_fps = 0;
	for (i = 0; i < count; i++) {
		_fps += _frameTimes[i];
	}

	if (count > 0)
	{
		_fps /= count;
		// now to make it an actual frames per second value...
		_fps = 1000.f / _fps;
	}
}

bool Window::physics()
{
	if (_totalDeltaTime <= 0.0 || _currentPhysicsStep > MAX_PHYSICS_STEPS)
	{
		_currentPhysicsStep = 0;
		return false;
	}

	_deltaTime = std::min(_totalDeltaTime, 1.0); //1.0 - max delta time
	_totalDeltaTime -= _deltaTime;
	_currentPhysicsStep++;
	

	return true;
}

void Window::inputProcessing()
{
	//Update previous frames key map
	unordered_map<unsigned int, bool>::iterator it;
	for (it = input._currentKeyMap.begin(); it != input._currentKeyMap.end(); it++)
	{
		input._previousKeyMap[it->first] = it->second;
	}

	//Update previous frames mouse button map
	for (it = input._currentMouseMap.begin(); it != input._currentMouseMap.end(); it++)
	{
		input._previousMouseMap[it->first] = it->second;
	}

	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
			case SDL_QUIT:
					_opened = false;
				break;
			case SDL_KEYDOWN:
					input.pressedKey(e.key.keysym.sym);
				break;
			case SDL_KEYUP:
					input.unpressedKey(e.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
					input.pressedMouseButton(e.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
					input.unpressedMouseButton(e.button.button);
				break;
			case SDL_MOUSEMOTION:
					input._mousePosition = b2Vec2(e.motion.x, e.motion.y);
				break;
		}
	}
}

void Window::limitFPS()
{
	float frameTicks = SDL_GetTicks() - _startFrameTicks;
	
	if (1000.0f / 60.0f > frameTicks)
	{
		SDL_Delay(1000.0f / 60.0f - frameTicks);
	}

	_startFrameTicks = SDL_GetTicks();
}

bool Window::opened()
{
	limitFPS();

	double newTicks = SDL_GetTicks();
	double frameTime = newTicks - _previousTicks;
	_previousTicks = newTicks;
	_totalDeltaTime = frameTime / DESIRED_FRAME_TIME;


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(GL_DEPTH_BUFFER_BIT);

	calculateFPS();
	inputProcessing();

	return _opened;
}

Window::~Window(void)
{
}
