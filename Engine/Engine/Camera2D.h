#pragma once
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include "Shader.h"
#include <vector>
#include <Box2D\Box2D.h>

using namespace glm;
namespace Eng
{
	class Camera2D
	{
	public:
		Camera2D(float screenWidth, float screenHeight, Shader shader, b2Vec2 position);
		~Camera2D();

		//Returns ortho matrix
		mat4 getMatrix() { return _cameraMatrix; }
		b2Vec2 getPosition() { return _position; }
		void update();
		void setScale(const float& scale);
		b2Vec2 convertScreenToWorld(b2Vec2 screenCoords);

	private:
		GLuint location;
		float _screenWidth;
		float _screenHeight;
		float _scale = 1.0f;
		bool _updateCamera;
		mat4 _cameraMatrix;
		mat4 _orthoMatrix;
		b2Vec2 _position;
		Shader _shader;
		bool _needsUpdate;
	};
}
