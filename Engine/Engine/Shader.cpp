#include "Shader.h"
#include <fstream>
#include <iostream>
#include "error.h"
#include <vector>

using namespace std;
using namespace Eng;

Shader::Shader() : _attribCount(0)
{
	createShaders(_fragmentShader, GL_FRAGMENT_SHADER, "Shaders/fragmentShader.txt");
	createShaders(_vertexShader, GL_VERTEX_SHADER, "Shaders/vertexShader.txt");
	createProgram();
	glUseProgram(_shaderProgram);
	addAttrib("position");
	addAttrib("vertexColor");
	addAttrib("iTexCord");
	attatchShaders();
	link();
}


Shader::~Shader()
{
}

void Shader::createShaders(GLuint &shader, GLenum type, char *filePath)
{
	shader = glCreateShader(type);
	ifstream info(filePath);
	if (info.fail()){
		errorMessage("Failed to open shader");
	}

	string line = "";
	string contents = "";
	while (getline(info, line)) {
		contents += line + "\n";
	}

	const char* contentsChar = contents.c_str();
	glShaderSource(shader, 1, &contentsChar, nullptr);
	glCompileShader(shader);

	GLint succes = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
	if (succes == GL_FALSE)
	{
		GLint logSize = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
		
		vector<GLchar> error(logSize);
		glGetShaderInfoLog(shader, logSize, &logSize, &error[0]);

		errorMessage(&error[0]);
	}
	else {
		cout << "Shaders created succesfully!" << endl;
	}
}

void Shader::createProgram()
{
	_shaderProgram = glCreateProgram();
}

void Shader::attatchShaders()
{
	glAttachShader(_shaderProgram, _vertexShader);
	glAttachShader(_shaderProgram, _fragmentShader);
}

void Shader::link()
{
	glLinkProgram(_shaderProgram);
	
	GLint isLinked = 0;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 512;
		glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(_shaderProgram, maxLength, &maxLength, &infoLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_shaderProgram);
		//Don't leak shaders either.
		glDeleteShader(_fragmentShader);
		glDeleteShader(_vertexShader);

		errorMessage("Shader link failed!");
	}
	else {
		cout << "Shaders linked succesfully!" << endl;
	}

	//Always detach shaders after a successful link.
	glDetachShader(_shaderProgram, _vertexShader);
	glDetachShader(_shaderProgram, _fragmentShader);
	glDeleteShader(_fragmentShader);
	glDeleteShader(_vertexShader);
}

void Shader::use()
{
	glUseProgram(_shaderProgram);
	for (int i = 0; i < _attribCount; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void Shader::unuse()
{
	glUseProgram(_shaderProgram);
	for (int i = 0; i < _attribCount; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void Shader::addAttrib(const std::string &name)
{
	glBindAttribLocation(_shaderProgram, _attribCount++, name.c_str());
}

void Shader::sendFloat(float value, const GLuint &location)
{
	glUniform1f(location, value);
}

void Shader::sendMatrix(const glm::mat4 &value, const GLuint &location)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &(value[0][0]));
}

GLuint Shader::getLocation(std::string name)
{
	GLuint location = glGetUniformLocation(_shaderProgram, name.c_str());
	if (location == GL_INVALID_INDEX) {
		errorMessage("Uniform was not found in shader!");
	}

	return location;
}