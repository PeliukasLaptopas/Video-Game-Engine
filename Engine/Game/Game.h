#include <SDL\SDL.h>
#include <Window.h>
#include <Box2D\Box2D.h>

#pragma once

using namespace Eng;

class Game
{
public:
	Game(char* title, int width, int height, int xPos = SDL_WINDOWPOS_CENTERED, int yPos = SDL_WINDOWPOS_CENTERED);
	~Game();
	Window window;

private:
	void Implosion(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower);

	b2Vec2 m_mouseWorld;
	b2MouseJointDef m_mouseJoint;
};

