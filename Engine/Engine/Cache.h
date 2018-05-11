#pragma once
#include <unordered_map>
#include <GL\glew.h>

using std::unordered_map;
using std::string;

/*Cache class is not static because its constantly changing. Cache is being updated
with more textures. Resource manager is going to be our static class which will hold
functions like loading textures. It will access this cache and return a texture
*/
namespace Eng {
	class Cache
	{
	public:
		GLuint getImage(string filePath, bool tile);
	private:
		GLuint loadImage(string filePath, bool tile);
		unordered_map<string, GLuint> _textureCache;
	};
}