#include "MainGame.h"
#include "Sprite.h"
#include "Shader.h"
#include <SOIL\SOIL.h>
#include "SpriteBatch.h"
#include "ResourceManager.h"
#include "Camera2D.h"
#include <GLM\glm.hpp>
#include "GameObject.h"
#include <algorithm>
#include "Collision2D.h"

#include <iostream>
using namespace std;
using namespace Eng;
using namespace glm;

MainGame::MainGame(char* title, int width, int height, int xPos, int yPos)
{
	/*window = Window(title, width, height, xPos, yPos);
	Shader shader = Shader();
	Camera2D camera2D = Camera2D((float)width, (float)height, shader, vec3(0,0,0));

	SpriteBatch batch = SpriteBatch();
	float x = 0.0f;
	float y = 0.0f;

	double previousTicks = SDL_GetTicks();
	double frameTime = 0.0;

	double speed = 100000;
	double camScale = 1;
	double MAX_DELTA_TIME = 1.0;

	Color c1 = Color(0.5f, 1, 1, 1);
	Color c2 = Color(0.5f, 0.5f, 0.0f, 1);

	float angle = 0.0f;

	GLuint text = ResourceManager::getTexture("Sprites/Character.png");
	Collision2D collision2D = Collision2D();

	while(window.opened())
	{
		if (window.input.getKey(SDLK_LSHIFT))
		{
			speed = 50000;
		}
		else {
			speed = 5000;
		}
		while (window.physics())
		{
			if (window.input.getKey(SDLK_w))
			{
				y += speed * window.getDeltaTime();
			}
			if (window.input.getKey(SDLK_s))
			{
				y -= speed * window.getDeltaTime();
			}
			if (window.input.getKey(SDLK_d))
			{
				x += speed * window.getDeltaTime();
			}
			if (window.input.getKey(SDLK_a))
			{
				x -= speed * window.getDeltaTime();
			}
		}

		if (window.input.getKey(SDLK_LCTRL))
		{
			c1 = Color(1, 0, 0, 1);
		}
		else {
			c1 = Color(0.5f, 1, 1, 1);
		}

		if (window.input.getKey(SDLK_LALT))
		{
			angle += 0.05f;
		}

		Collider2D Col = Collider2D(true, false);
		GameObject sprite3 = GameObject(vec2(150, 150), vec2(100, 100), 0, c1, ResourceManager::getTexture("Sprites/Clouds.png"), Col, batch, window);
		GameObject sprite = GameObject(vec2(x, y), vec2(100, 100), angle, c1, ResourceManager::getTexture("Sprites/Nedzius.png"), Col, batch, window);
		GameObject sprite1 = GameObject(vec2(300, 300), vec2(30, 30), 0.5f, c2, ResourceManager::getTexture("Sprites/Palete.png"), Col, batch, window);
		
		cout << sprite3.getBatchID() << endl;
		cout << sprite.getBatchID() << endl;
		cout << sprite1.getBatchID() << endl;

		collision2D.checkCollision(sprite, sprite3);
		cout << endl;

		if (window.input.getKey(SDLK_r))
		{
			camScale += 0.01f;
		}
		if (window.input.getKey(SDLK_f))
		{
			
			camScale -= 0.01f;
		}

		camera2D.setScale(camScale);
		camera2D.update();
		
		if (window.input.getKey(SDLK_SPACE))
		{
			for (int i = 0; i < 1000000; i++)
			{
				int a = sqrt(sqrt(sqrt(i)));
			}
		}
		
		shader.use();
		batch.bufferData();
		batch.render();
		shader.unuse();
		//Po visu operaciju swap window, kad updatintas vaizdas butu
		SDL_GL_SwapWindow(window.getWindow());
		
		//cout << window.getFPS() << endl;
	}*/
}

MainGame::~MainGame(void)
{
}
