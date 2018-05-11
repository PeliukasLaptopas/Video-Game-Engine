#include "GameObject.h"

using namespace Eng;

b2Vec2 GameObject::rotatePoint(b2Vec2 point, float angle)
{
	b2Vec2 rotatedPoint;
	rotatedPoint.x = point.x * cos(angle) - point.y * sin(angle);
	rotatedPoint.y = point.x * sin(angle) + point.y * cos(angle);
	return rotatedPoint;
}

GameObject::GameObject(const b2Vec2 &pos, const b2Vec2 &scale, const float &angle, const Color &color, const GLuint &texture, SpriteBatch& spriteBatch) {
	
	//!!!!Here by default sprite origin (pivot point)  is at its cerner!!!!

	b2Vec2 halfScale(scale.x / 2, scale.y / 2);

	//Get sprite centered at the origin of x and y axis
	//So if the sprite is 2x2, centered it will look like:
	/*
	(-1, 1) (1,1)
	(-1,-1) (1,-1)
	*/
	b2Vec2 lb(-halfScale.x, -halfScale.y); //left bottom
	b2Vec2 rb(halfScale.x, -halfScale.y); //right bottom
	b2Vec2 tr(halfScale.x, halfScale.y); //top right
	b2Vec2 tl(-halfScale.x, halfScale.y); //top left
										//Rotate the sprite. After we rotated this sprite lets get its origin (pivot point) back to its original bottom left by simply adding half scale of the sprite
	lb = rotatePoint(lb, angle); //Galim prideti prie sito dar "+ halfScale" ir tada bus pivot point bottom left
	rb = rotatePoint(rb, angle); //Galim prideti prie sito dar "+ halfScale" ir tada bus pivot point bottom left
	tr = rotatePoint(tr, angle); //Galim prideti prie sito dar "+ halfScale" ir tada bus pivot point bottom left
	tl = rotatePoint(tl, angle); //Galim prideti prie sito dar "+ halfScale" ir tada bus pivot point bottom left

	_leftBottom.pos.x = pos.x + lb.x;
	_leftBottom.pos.y = pos.y + lb.y;
	_leftBottom.uv = b2Vec2(0, 0);
	_leftBottom.color = color;

	_rightBottom.pos.x = pos.x + rb.x;
	_rightBottom.pos.y = pos.y + rb.y;
	_rightBottom.uv = b2Vec2(1, 0);
	_rightBottom.color = color;

	_topLeft.pos.x = pos.x + tl.x;
	_topLeft.pos.y = pos.y + tl.y;
	_topLeft.uv = b2Vec2(0, 1);
	_topLeft.color = color;

	_topRight.pos.x = pos.x + tr.x;
	_topRight.pos.y = pos.y + tr.y;
	_topRight.uv = b2Vec2(1, 1);
	_topRight.color = color;

	_color = color;

	_texture = texture;
	
	_color = color;
	_pos = pos;
	_scale = scale;
	_texture = texture;

	spriteBatch.add(this);
}


GameObject::~GameObject(void)
{
}
