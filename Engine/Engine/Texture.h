#pragma once

#include <GL\glew.h>
#include "ResourceManager.h"

namespace Eng {
	class Texture
	{
	public:
		Texture();
		~Texture();

		bool tile;

	private:
		GLuint _textureID;
	};
}
