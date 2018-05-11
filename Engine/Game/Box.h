#pragma once

#include <GLM\glm.hpp>
#include <Box2D\Box2D.h>
#include <Vertex.h>
#include <iostream>
#include <GameObject.h>
#include <Collider2D.h>

using namespace glm;
using namespace std;
using namespace Eng;

class Box
{
public:
	Box(b2World &world, b2Vec2 pos, b2Vec2 scale, Color color, GLuint texture, bool staticObj, bool freezeRotation);
	~Box();

	Collider2D::Rigidbody2D GetRigidbodyBody() { return _collider2D.GetRigidbodyBody(); }
	Color GetColor() { return _color; }

private:
	Collider2D::BoxCollider2D _collider2D;
	Color _color;
};

