#include "Camera2D.h"
#include <iostream>

using namespace std;
using namespace Eng;

Camera2D::Camera2D(float screenWidth, float screenHeight, Shader shader, b2Vec2 position)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_orthoMatrix = ortho(0.0f, screenWidth, 0.0f, screenHeight);
	_shader = shader;
	_position = position;
	_needsUpdate = true;
	location = _shader.getLocation("camera");
}

Camera2D::~Camera2D()
{

}

void Camera2D::update()
{
	if (_needsUpdate)
	{
		//When we move camera to the left everything moves to the right and same for right side.
		//Center camera to the center of the screen to set correct scaling matrix with "+ _screenWidh/2 and+ _screenHeight/2"
		vec3 translationVec(-_position.x + _screenWidth / 2, -_position.y + _screenHeight/2, 0.0f);
		_cameraMatrix = translate(_orthoMatrix, translationVec);
		

		vec3 scaleVec(_scale, _scale, 0.0f);
		_cameraMatrix = glm::scale(glm::mat4(1.0f), scaleVec) * _cameraMatrix;

		_shader.sendMatrix(_cameraMatrix, location);
		_needsUpdate = false;
	}
	else {
		_shader.sendMatrix(_cameraMatrix, location);
	}
}

void Camera2D::setScale (const float& scale)
{
	if (_scale != scale)
	{
		_scale = scale;
		_needsUpdate = true;
	}
}

b2Vec2 Camera2D::convertScreenToWorld(b2Vec2 screenCoords) {
	// Invert Y direction
	screenCoords.y = _screenHeight - screenCoords.y;
	// Make it so that 0 is the center
	screenCoords -= b2Vec2(_screenWidth / 2, _screenHeight / 2);
	// Scale the coordinates
	screenCoords.x /= _scale;
	screenCoords.y /= _scale;
	// Translate with the camera position
	screenCoords.x += _position.x;
	screenCoords.y += _position.y;

	return screenCoords;
}