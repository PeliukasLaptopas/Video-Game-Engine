#include "Game.h"
#include "Box.h"
#include "Ball.h"
#include <GLM\glm.hpp>
#include <GameObject.h>
#include <Vertex.h>
#include <Shader.h>
#include <Camera2D.h>
#include <ResourceManager.h>
#include <Vertex.h>
#include <random>
#include <time.h>

using namespace Eng;

Game::Game(char* title, int width, int height, int xPos, int yPos)
{
	vec2 groundSize = vec2(45, 1);  //Bottom
	vec2 groundSize2 = vec2(1, 30); //Right
	vec2 groundSize3 = vec2(1, 30); //Left
	vec2 groundSize4 = vec2(45, 1);  //Top

	vec2 groundPos = vec2(0.0f, -10.83 - .5f);   //Bottom
	vec2 groundPos2 = vec2(20.5f, 0);    //Right
	vec2 groundPos3 = vec2(-20.5f, 0);    //Left
	vec2 groundPos4 = vec2(0.0f, 10.83 + .5f);  //Top

	window = Window(title, width, height, Color(0, 0, 0, 1), xPos, yPos);

	b2Vec2 gravity(0, 0);
	b2World world(gravity);

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	SpriteBatch batch;
	Shader shader;

	Camera2D camera((float)width, (float)height, shader, b2Vec2(0, 0));

	float camScale = 30;

	float camX;

	std::mt19937 gen;
	vector<Ball> balls;

	srand(time(NULL));
	for (int i = 0; i < 1000; i++)
	{
		std::uniform_real_distribution<> r(.3f, 1.0f);
		std::uniform_real_distribution<> g(.3f, 1.0f);
		std::uniform_real_distribution<> b(.3f, 1.0f);
		std::uniform_real_distribution<> a(.7f, 1.0f);

		std::uniform_real_distribution<> randomX(-20, 20);
		std::uniform_real_distribution<> randomY(-10.3, 10.3);

		std::uniform_real_distribution<> randomRadius(.3f, .7f);

		//World &world, vec2 pos, float radius, Color color
		//
		//world, vec2(randomX(gen), randomY(gen)), randomRadius(gen), Color(r(gen), g(gen), b(gen), a(gen))
		balls.emplace_back(world, b2Vec2(randomX(gen), randomY(gen)), randomRadius(gen), Color(r(gen), g(gen), b(gen), a(gen)), ResourceManager::getTexture("Sprites/circle.png", false), false, true);
		b2MassData *ballmase = new b2MassData();
		ballmase->mass = 1;
		balls[i].GetCollider()->GetRigidbodyBody().GetBody()->SetMassData(ballmase);
		
		//boxes.emplace_back(world, vec2(randomX, randomY), vec2(randomXScale, randomYScale), Color(r(gen),0,b(gen),a(gen)));
	}

	vec2 randomCircle(0, 0);
	
	Box ground =  Box(world, b2Vec2(groundPos.x, groundPos.y), b2Vec2(groundSize.x, groundSize.y),     Color(1, 1, 1, 0), ResourceManager::getTexture("Sprites/Bricks.png", false), true, true);
	Box ground2 = Box(world, b2Vec2(groundPos2.x, groundPos2.y), b2Vec2(groundSize2.x, groundSize2.y), Color(1, 1, 1, 0), ResourceManager::getTexture("Sprites/Bricks.png", false), true, true);
	Box ground3 = Box(world, b2Vec2(groundPos3.x, groundPos3.y), b2Vec2(groundSize3.x, groundSize3.y), Color(1, 1, 1, 0), ResourceManager::getTexture("Sprites/Bricks.png", false), true, true);
	Box ground4 = Box(world, b2Vec2(groundPos4.x, groundPos4.y), b2Vec2(groundSize4.x, groundSize4.y), Color(1, 1, 1, 0), ResourceManager::getTexture("Sprites/Bricks.png", false), true, true);
	Ball circle = Ball(world, b2Vec2(randomCircle.x, randomCircle.y), .3f, Color(1, .7f, 1, 1), ResourceManager::getTexture("Sprites/circle.png", false), false, true);

	Box center = Box(world, b2Vec2(0, 0), b2Vec2(3, 3), Color(1, 1, 1, 1), ResourceManager::getTexture("Sprites/WaterF4.png", false), false, false);
	Box center2 = Box(world, b2Vec2(5, 0), b2Vec2(3, 3), Color(1, 1, 1, 1), ResourceManager::getTexture("Sprites/WaterF4.png", false), false, false);

	b2MouseJointDef md;

	b2MassData *mase = new b2MassData();
	mase->mass = 100;
	circle.GetCollider()->GetRigidbodyBody().GetBody()->SetMassData(mase);
	//if joint exists then create
	md.bodyA = ground.GetRigidbodyBody().GetBody();
	md.bodyB = circle.GetCollider()->GetRigidbodyBody().GetBody();
	md.target = b2Vec2(0,0);
	
	md.collideConnected = true;
	md.maxForce = 1000 * circle.GetCollider()->GetRigidbodyBody().GetBody()->GetMass();
	md.dampingRatio = 0;
	md.frequencyHz = 30;
	md.collideConnected = true;

	circle.GetCollider()->GetRigidbodyBody().GetBody()->SetActive(true);

	b2MouseJoint* dotDrag = static_cast<b2MouseJoint*>(world.CreateJoint(&md));

	float newScale = .3f;

	while (window.opened())
	{
		shader.use();

		world.SetGravity(gravity);
		world.Step(timeStep, velocityIterations, positionIterations);
		b2Vec2 mousePos = camera.convertScreenToWorld(window.input.getMousePosition());

		for (int i = 0; i < balls.size(); i++)
		{
			balls[i].GetCollider()->GetRigidbodyBody().Draw(batch);
		}

		if (window.input.getKey(SDLK_SPACE))
		{
			float power = 100;
			for (int i = 0; i < balls.size(); i++)
			{
				Implosion(balls[i].GetCollider()->GetRigidbodyBody().GetBody(), mousePos, balls[i].GetCollider()->GetRigidbodyBody().GetBody()->GetPosition(), power);
			}
		}

		center.GetRigidbodyBody().Draw(batch);
		center2.GetRigidbodyBody().Draw(batch);


		if (window.input.getKey(SDLK_a))
		{
			gravity = b2Vec2(0, -9);
		}

		if (window.input.getKey(SDLK_q))
		{
			gravity = b2Vec2(0, 0);
		}

		if (window.input.getKey(SDLK_w))
		{
			newScale += 0.05f;
			circle.GetCollider()->SetScale(newScale);
		}
		if (window.input.getKey(SDLK_s))
		{
			newScale -= 0.05f;
			circle.GetCollider()->SetScale(newScale);
		}


		ground.GetRigidbodyBody().Draw(batch);
		ground2.GetRigidbodyBody().Draw(batch);
		ground3.GetRigidbodyBody().Draw(batch);
		ground4.GetRigidbodyBody().Draw(batch);
		circle.GetCollider()->GetRigidbodyBody().Draw(batch);

		
		dotDrag->SetTarget(mousePos);

		if (window.input.getKey(SDLK_x))
			camScale += 1;
		if (window.input.getKey(SDLK_z))
			camScale -= 1;

		camera.setScale(camScale);
		camera.update();
		batch.bufferData();
		batch.render();
		shader.unuse();
		
		SDL_GL_SwapWindow(window.getWindow());
	}
}

void Game::Implosion(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower)
{
	//void applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower) {
	b2Vec2 blastDir = applyPoint - blastCenter;
	float distance = blastDir.Length();
	//ignore bodies exactly at the blast point - blast direction is undefined
	if (distance == 0)
		return;
	float impulseMag = -blastPower / distance*.1f;
	body->SetLinearVelocity(impulseMag * blastDir);
}

Game::~Game()
{
}