#include "Cache.h"
#include <SOIL\SOIL.h>
#include "error.h"

#include <iostream>
using namespace std;
using namespace Eng;

GLuint Cache::getImage(string filePath, bool tile)
{
	unordered_map<string, GLuint>::iterator it;
	for (it = _textureCache.begin(); it != _textureCache.end(); it++)
	{
		//If iterator is NOT at the end
		if (it != _textureCache.end())
		{
			//If a texture was found - return it from the cache
			if (it->first == filePath)
			{
				//cout << "LOADED FROM CACHE: " << filePath.c_str() << endl;
				return it->second;
			}
		}
	}

	GLuint textureToReturn = loadImage(filePath, tile);
	_textureCache.insert(std::make_pair(filePath, textureToReturn));
	//If image was not found in cache load a new one from the computer
	//cout << "LOADED FROM COMPUTER: " << filePath.c_str() << endl;
	return textureToReturn;
}

//Loads image with SOIL and generates a new texture for us
GLuint Cache::loadImage(string filePath, bool tile)
{
	int width;
	int height;

	unsigned char* image = SOIL_load_image(filePath.c_str(), &width, &height, 0, 0);
	if (0 == image)
	{
		errorMessage((char*)SOIL_last_result());
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if (tile)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}