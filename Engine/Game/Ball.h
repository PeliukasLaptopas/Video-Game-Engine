#pragma once

#include <Box2D\Box2D.h>
#include <Vertex.h>
#include <GLM\glm.hpp>
#include <Collider2D.h>

using namespace glm;
using namespace Eng;

class Ball
{
public:
	Ball(b2World &world, b2Vec2 pos, float radius, Color color, GLuint texture, bool staticObj, bool freezeRotation);
	~Ball();

	Collider2D::CircleCollider2D* GetCollider() { return _collider2D; }
	float GetRadius() { return _radius; }
	Color GetColor() { return _color; }

private:
	Collider2D::CircleCollider2D *_collider2D;
	float _radius;
	Color _color;

	/*
	b2Body *_body = nullptr;
	b2BodyDef _bodyDef;
	vec2 _scale;
	Color _color;
	b2PolygonShape _dynamicBox;*/
};

