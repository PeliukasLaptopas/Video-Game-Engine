#pragma once
#include <Box2D\Box2D.h>
#include "Vertex.h"
#include "GameObject.h" //Jeigu sito neincludinam spritebatch nezinos koks GameObject sizeof bus ir error mes vectorius jo
#include "SpriteBatch.h"
#include <iostream>

using namespace std;

namespace Eng
{
class Collider2D
{
public:
	Collider2D();
	~Collider2D();

	class Rigidbody2D
	{
	public:
		Rigidbody2D(b2Vec2 pos, b2Vec2 scale, b2World &world, Color color, GLuint texture, bool staticObj, bool dontAllowRotation)
		{
			if (staticObj == false)
				_bodyDef.type = b2_dynamicBody;

			_bodyDef.position.Set(pos.x, pos.y);
			
			_bodyDef.fixedRotation = dontAllowRotation;
			_body = world.CreateBody(&_bodyDef);
			_scale = scale;
			_color = color;
			_texture = texture;
		}

		void Draw(SpriteBatch &batch)
		{
			GameObject thisObj = GameObject(_body->GetPosition(), _scale, _body->GetAngle(), _color, _texture, batch);
		}

		Rigidbody2D() { }

		void SetScale(b2Vec2 newScale)
		{
			_scale.x = newScale.x;
			_scale.y = newScale.y;
		}

		b2Vec2 GetScale() { return _scale; }

		b2Body *GetBody() { return _body; }
	private:
		b2Body *_body = nullptr;
		b2BodyDef _bodyDef;
		b2Vec2 _scale;
		Color _color;
		GLuint _texture;
	};

	class CircleCollider2D
	{
	public:

		CircleCollider2D(b2Vec2 pos, float radius, b2World &world, Color color, GLuint texture, bool staticObj, bool dontAllowRotation)
		{
			_staticObj = staticObj;
			///Now we create a dynamic body
			_rigidBody2D = Rigidbody2D(pos, b2Vec2(radius, radius), world, color, texture, staticObj, dontAllowRotation);

			_radius = radius;

			b2CircleShape circleShape;
			circleShape.m_p.Set(0, 0); //position, relative to body position
			circleShape.m_radius = radius / 2; //radius

			_fixtureDef.shape = &circleShape;
			_fixtureDef.density = 1.0f;
			_fixtureDef.friction = .5f;
			_fixtureDef.restitution = .7f;

			currentFixture = _rigidBody2D.GetBody()->CreateFixture(&_fixtureDef); //add a fixture to the body
		}

		void SetScale(float newRadius)
		{
			if (currentFixture == nullptr) //Nera fixture nera colliderio
				return;

			_radius = newRadius;

			b2CircleShape circleShape;
			circleShape.m_p.Set(0, 0); //position, relative to body position
			circleShape.m_radius = newRadius / 2; //radius
			_fixtureDef.shape = &circleShape;

			_rigidBody2D.GetBody()->DestroyFixture(currentFixture); //Remove currentFixture and add new one with new scale

			if (_staticObj)
			{
				currentFixture = _rigidBody2D.GetBody()->CreateFixture(&circleShape, 0);
			}
			else {
				currentFixture = _rigidBody2D.GetBody()->CreateFixture(&_fixtureDef);
			}


			_rigidBody2D.SetScale(b2Vec2(newRadius, newRadius));
		}

		CircleCollider2D() { } //DEFAULT CONSTRUCTOR

		float GetRadius() { return _radius; }

		Rigidbody2D GetRigidbodyBody() { return _rigidBody2D; }
		
	private:
		Rigidbody2D _rigidBody2D;
		b2Body *_body = nullptr;
		float _radius;

		b2PolygonShape _dynamicBox;
		b2FixtureDef _fixtureDef;
		b2Fixture* currentFixture;
		bool _staticObj;
	};

	class BoxCollider2D
	{
	public:

		/*
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = world.CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);*/

		BoxCollider2D(b2Vec2 pos, b2Vec2 scale, b2World &world, Color color, GLuint texture, bool staticObj, bool dontAllowRotation)
		{
			_staticObj = staticObj;
			_rigidBody2D = Rigidbody2D(pos, scale, world, color, texture, staticObj, dontAllowRotation);
			b2PolygonShape dynamicBox;
			if (staticObj)
			{
				dynamicBox.SetAsBox(scale.x / 2, scale.y / 2); //Praso per pus maziau, todel duodam * 2
				currentFixture = _rigidBody2D.GetBody()->CreateFixture(&dynamicBox, 0);
				currentFixture->SetFriction(1);
			}
			else {
				dynamicBox.SetAsBox(scale.x / 2, scale.y / 2); //Praso per pus maziau, todel duodam * 2
				_scale = scale;
				
				_fixtureDef.shape = &dynamicBox;
				_fixtureDef.density = 1.0f;
				_fixtureDef.friction = 0.3f;
				currentFixture = _rigidBody2D.GetBody()->CreateFixture(&_fixtureDef);
			}
		}

		void SetScale(b2Vec2 newScale)
		{
			if (currentFixture == nullptr)
				return;

			_scale = newScale;
			b2PolygonShape dynamicBox;
			_rigidBody2D.GetBody()->DestroyFixture(currentFixture); //Remove currentFixture and add new one with new scale

			dynamicBox.SetAsBox(newScale.x / 2, newScale.y / 2); //Praso per pus maziau, todel duodam * 2
			_fixtureDef.shape = &dynamicBox;
			if (_staticObj)
			{
				currentFixture = _rigidBody2D.GetBody()->CreateFixture(&dynamicBox, 0);
			}
			else {
				currentFixture = _rigidBody2D.GetBody()->CreateFixture(&_fixtureDef);
			}

			_rigidBody2D.SetScale(newScale);
		}

		BoxCollider2D() { } //DEFAULT CONSTRUCTOR

		Rigidbody2D GetRigidbodyBody() { return _rigidBody2D; }

	private:
		b2Vec2 _scale;
		Rigidbody2D _rigidBody2D;
		b2FixtureDef _fixtureDef;
		b2Fixture* currentFixture;
		bool _staticObj;
	};
};
}
