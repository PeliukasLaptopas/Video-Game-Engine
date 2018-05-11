#include "Input.h"
#include <iostream>

using namespace std;
using namespace Eng;

Input::Input(void)
{
}


Input::~Input(void)
{
}

void Input::pressedKey(unsigned int keyCode)
{
	_currentKeyMap[keyCode] = true;
}

void Input::unpressedKey(unsigned int keyCode)
{
	_currentKeyMap[keyCode] = false;
}

bool Input::wasKeyPressed(unsigned int keyCode)
{
	return _previousKeyMap[keyCode];
}

bool Input::wasMousePressed(unsigned int keyCode)
{
	return _previousMouseMap[keyCode];
}

void Input::pressedMouseButton(unsigned int keyCode)
{
	_currentMouseMap[keyCode] = true;
}

void Input::unpressedMouseButton(unsigned int keyCode)
{
	_currentMouseMap[keyCode] = false;
}