#pragma once
#include "Cache.h"

using std::string;

namespace Eng
{
	//Static class that returns texture
	class ResourceManager
	{
	public:
		static GLuint getTexture(string filePath, bool tile);
	private:
		static Cache cache;
	};
}