#include "Box.h"

Box::Box(b2World &world, b2Vec2 pos, b2Vec2 scale, Color color, GLuint texture, bool staticObj, bool freezeRotation)
{
	_collider2D = Collider2D::BoxCollider2D(pos, scale, world, color, texture, staticObj, freezeRotation);
	_color = color;
}

Box::~Box()
{
}
