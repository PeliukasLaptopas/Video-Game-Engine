#pragma once

#include "Vertex.h"
#include "SpriteBatch.h"
#include "Window.h"
#include <Box2D\Box2D.h>


namespace Eng {
	class GameObject
	{
	public:

		~GameObject(void);
		GameObject(void) { }
		GameObject(const b2Vec2 &pos, const b2Vec2 &scale, const float &angle, const Color &color, const GLuint &texture, SpriteBatch& spriteBatch);

		Color getColor() {
			return _color;
		}
		GLuint getTexture() {
			return _texture;
		}
		b2Vec2 getPos()
		{
			return _pos;
		}
		b2Vec2 getScale()
		{
			return _scale;
		}

		Vertex leftBottom() {
			return _leftBottom;
		}
		Vertex rightBottom() {
			return _rightBottom;
		}
		Vertex topLeft() {
			return _topLeft;
		}
		Vertex topRight() {
			return _topRight;
		}

		friend class SpriteBatch;

		bool detectCollision;

	private:
		b2Vec2 rotatePoint(b2Vec2 point, float angle);

		Vertex _leftBottom;
		Vertex _rightBottom;
		Vertex _topLeft;
		Vertex _topRight;

		b2Vec2 _pos;
		b2Vec2 _scale;
		Color _color;
		GLuint _texture;
	};
}
