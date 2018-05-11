#pragma once

#include "Vertex.h"
#include <GLM\glm.hpp>

namespace Eng
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void draw();
		void init();

	private:
		GLuint _vbo;
		GLuint _texture;
	};
}

