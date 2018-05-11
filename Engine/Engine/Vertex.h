#pragma once
#include <GLM\glm.hpp>
#include <GL\glew.h>
#include <Box2D\Box2D.h>

struct Color
{
	Color() {}

	Color(float _r, float _g, float _b, float _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	float r;
	float g;
	float b;
	float a;
};

class Vertex
{
public:
	b2Vec2 pos;
	Color color;
	b2Vec2 uv;

	Vertex() {}
	Vertex(b2Vec2 _pos, Color _color, b2Vec2 _uv)
	{
		pos = _pos;
		color = _color;
		uv = _uv;
	}
};