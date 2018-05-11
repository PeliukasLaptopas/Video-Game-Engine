#include "Ball.h"


Ball::Ball(b2World &world, b2Vec2 pos, float radius, Color color, GLuint texture, bool staticObj, bool freezeRotation)
{
	_collider2D = new Collider2D::CircleCollider2D(pos, radius, world, color, texture, staticObj, freezeRotation);
	_color = color;
}

Ball::~Ball()
{
}
