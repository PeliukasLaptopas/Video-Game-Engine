#pragma once
#include "GameObject.h"

namespace Eng
{
class Collision2D
{
public:
	Collision2D();
	~Collision2D();

	void checkCollision(GameObject sprite1, GameObject sprite2);//check for collision before adding an object to this spriteBatch

private:
	vec2 getVector(Vertex v1, Vertex v2);
	vec2 getNormal(vec2 vector);
	vector<vec2> getAxes(GameObject other);
	double dotProduct(Vertex vertex, vec2 vector);
	void project(GameObject other, vec2 axis, float &min, float &max);
};
}