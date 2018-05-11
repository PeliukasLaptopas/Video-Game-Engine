#pragma once

#include <GL/glew.h>
#include <string>
#include <GLM\glm.hpp>

namespace Eng
{
class Shader
{
public:
	Shader();
	~Shader();
	
	//From top to bottom its sorted how it should go:
	void use();
	void unuse();

	void addAttrib(const std::string &name);
	void sendFloat(float value, const GLuint &location);
	void sendMatrix(const glm::mat4 &value, const GLuint &location);
	GLuint getLocation(std::string name);

private:
	void createProgram();
	void attatchShaders();
	void link();
	void createShaders(GLuint &shader, GLenum type, char *filePath);
	GLuint _vertexShader;
	GLuint _fragmentShader;
	GLuint _shaderProgram;
	unsigned int _attribCount;
};
}