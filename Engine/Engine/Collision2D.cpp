#include "Collision2D.h"
#include <iostream>
#include <algorithm>

using namespace Eng;
using namespace std;

Collision2D::Collision2D()
{
}


Collision2D::~Collision2D()
{
}

void Collision2D::checkCollision(GameObject sprite1, GameObject sprite2)
{
	float min1, min2;
	float max1, max2;

	vec2 axis;
	double overlap = 99999999;
	vector<vec2> axes1 = getAxes(sprite1);
	vector<vec2> axes2 = getAxes(sprite2);

	bool noCollision = false;
	for (int e = 0; e < axes1.size(); e++)
	{
		project(sprite1, axes1[e], min1, max1);
		project(sprite2, axes1[e], min2, max2);

		if (min1 - max2  > 0 || min2 - max1 > 0)
		{
			noCollision = true;
			break;
		}
		else { //Collision was found
			double currentOverlap = std::min(max1, max2) - std::max(min1, min2);
			if (currentOverlap < overlap)
			{
				overlap = currentOverlap;
				axis = axes1[e];
			}
		}
	}

	if (noCollision)
	{
		return;
	}
	else {
		if (noCollision == false)
		{
			axis = glm::normalize(axis);
			cout << axis.x << ";" << axis.y << "   ";
			//cout << overlap << ":";
			//cout << "yes";
		}
	}

	for (int e = 0; e < axes2.size(); e++)
	{
		project(sprite1, axes2[e], min1, max1);
		project(sprite2, axes2[e], min2, max2);

		if (min1 - max2  > 0 || min2 - max1 > 0)
		{
			noCollision = true;
			break;
		}
		else { //Collision was found
			double currentOverlap = std::min(max1, max2) - std::max(min1, min2);
			if (currentOverlap < overlap)
			{
				overlap = currentOverlap;
				axis = axes2[e];
			}
		}
	}

	if (noCollision == false)
	{
		axis = glm::normalize(axis);
		cout << axis.x << ";" << axis.y << "   ";
		//cout << overlap << ":";
		//cout << "yes";
	}
}

vec2 Collision2D::getVector(Vertex v1, Vertex v2)
{
	return vec2(v2.pos.x - v1.pos.x, v2.pos.y - v1.pos.y);
}

vec2 Collision2D::getNormal(vec2 vector)
{
	return vec2(vector.y, -vector.x);
}

vector<vec2> Collision2D::getAxes(GameObject other)
{
	/*
	Lets graph how this we get normals:

	1) /^\
	|
	----------
	|        |
	2) <--   | --> 3)
	|        |
	----------
	|
	\/ 4)

	here we have all 4 normals of a sprite. These will represent each axis.
	1) top normal
	2) left normal
	3) right normal
	4) bottom normal

	first two vertices specify bottom left and bottom right
	first and 3rd specify bottom left and top left

	rectangular sprite only needs to get 2 normals, either left or right and bottom or top
	because they are parallel
	*/

	vector<vec2> axis;

	vec2 bottom_vector = getVector(other.leftBottom(), other.rightBottom());
	vec2 left_vector = getVector(other.leftBottom(), other.topLeft());

	vec2 bottom_axis = getNormal(bottom_vector);
	vec2 left_axis = getNormal(left_vector);

	axis.emplace_back(bottom_axis.x, bottom_axis.y);
	axis.emplace_back(left_axis.x, left_axis.y);

	return axis;
}

double Collision2D::dotProduct(Vertex vertex, vec2 vector)
{
	return (vertex.pos.x * vector.x) + (vertex.pos.y * vector.y);
}

void Collision2D::project(GameObject other, vec2 axis, float &min, float &max)
{
	float min1 = dotProduct(other.leftBottom(), axis);
	float min2 = dotProduct(other.rightBottom(), axis);
	float min3 = dotProduct(other.topRight(), axis);
	float min4 = dotProduct(other.topLeft(), axis);

	if (min1 <= min2 && min1 <= min3 && min1 <= min4)
		min = min1;
	if (min2 <= min1 && min2 <= min3 && min2 <= min4)
		min = min2;
	if (min3 <= min1 && min3 <= min2 && min3 <= min4)
		min = min3;
	if (min4 <= min1 && min4 <= min2 && min4 <= min3)
		min = min4;

	if (min1 >= min2 && min1 >= min3 && min1 >= min4)
		max = min1;
	if (min2 >= min1 && min2 >= min3 && min2 >= min4)
		max = min2;
	if (min3 >= min1 && min3 >= min2 && min3 >= min4)
		max = min3;
	if (min4 >= min1 && min4 >= min2 && min4 >= min3)
		max = min4;

}