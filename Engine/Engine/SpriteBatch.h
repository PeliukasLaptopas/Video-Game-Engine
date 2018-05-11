#pragma once

#include <vector>
#include "Vertex.h"
#include <GLM\glm.hpp>

using std::vector;
using namespace glm;

namespace Eng
{
	class RenderBatch
	{
	public:
		RenderBatch(GLuint texture, int start, int vertCount)
		{
			_texture = texture;
			_startOffset = start;
			verticesCount = vertCount;
		}

		GLuint getTexture()
		{
			return _texture;
		}
		unsigned int getStart()
		{
			return _startOffset;
		}

		unsigned int verticesCount; /*We need to know how many vertices we have in this render batch
									 so whenever we draw we know start offset in buffer and count of
									 vertices to draw*/

	private:
		GLuint _texture;
		unsigned int _startOffset; /*We only need start because sprites will be rectangular shape. 
									 This means that they will have 6 vertices. So we draw:
									 from _startOffset 6 vertices*/
	};

	class GameObject; //forward declaration of GameObject because GameObject uses sprite batch in its constructor


	class SpriteBatch
	{
	public:
		friend class GameObject;

		SpriteBatch();
		~SpriteBatch();

		//We add all sprites, upload information to the buffer and render
		void bufferData();
		void render();
		void begin();

		vector<GameObject> getGameObjects()
		{
			return _glyphs;
		}


	private:
		void add(GameObject *gameObject);
		unsigned int _currentGlyph = 0;

		vector<GameObject*> _glyphPointers;
		vector<GameObject> _glyphs;
		vector<RenderBatch> _renderBatches;
		vector<Vertex> _vertices;

		GLuint _vao;
		GLuint _vbo;

		void sortGlyphs();
		static bool compareTexture(GameObject *a, GameObject *b);
	};
}
