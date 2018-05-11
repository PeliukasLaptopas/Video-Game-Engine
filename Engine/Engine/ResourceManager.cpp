#include "ResourceManager.h"

using namespace Eng;

//All static variables have to be declared like this:
Cache ResourceManager::cache;

GLuint ResourceManager::getTexture(string filePath, bool tile)
{
	return cache.getImage(filePath, tile);
}
