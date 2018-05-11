#pragma once

#include <GLM\vec2.hpp>
#include "Vertex.h"
#include <GL\glew.h>

using namespace glm;

namespace Eng {
class GameObject_Draw
{
public:
	GameObject_Draw();
	~GameObject_Draw();

protected:
	vec2 rotatePoint(vec2 point, float angle);

	Vertex _leftBottom;
	Vertex _rightBottom;
	Vertex _topLeft;
	Vertex _topRight;

	vec2 _pos;
	vec2 _scale;
	Color _color;
	GLuint _texture;
};
}

