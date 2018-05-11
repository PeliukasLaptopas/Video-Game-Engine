#include "SpriteBatch.h"
#include <algorithm>
#include <iostream>
#include "GameObject.h"
#include <SDL\SDL.h>
#include <algorithm>

using namespace std;
using namespace Eng;

SpriteBatch::SpriteBatch() : _vao(0), _vbo(0), _glyphPointers(0)
{
	if (_vao == 0)
	{
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		if (_vbo == 0)
		{
			glGenBuffers(1, &_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		}

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}


SpriteBatch::~SpriteBatch()
{

}

void SpriteBatch::add(GameObject *gameObject)
{
	_glyphs.emplace_back(*gameObject);
}

void SpriteBatch::sortGlyphs()
{
	std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareTexture);
}

void SpriteBatch::bufferData()
{
	if (_glyphs.empty())
	{
		return;
	}

	_glyphPointers.resize(_glyphs.size());
	for (int i = 0; i < _glyphs.size(); i++)
	{
		_glyphPointers[i] = &_glyphs[i];
	}

	sortGlyphs();
	_vertices.resize(_glyphs.size() * 6);

	unsigned int startOffset = 0;
	unsigned int currentVertex = 0;
	unsigned int currentGlyph = 0;

	_vertices[currentVertex++] = _glyphPointers[0]->leftBottom();
	_vertices[currentVertex++] = _glyphPointers[0]->rightBottom();
	_vertices[currentVertex++] = _glyphPointers[0]->topLeft();
	_vertices[currentVertex++] = _glyphPointers[0]->topLeft();
	_vertices[currentVertex++] = _glyphPointers[0]->topRight();
	_vertices[currentVertex++] = _glyphPointers[0]->rightBottom();

	startOffset += 6;
	currentGlyph++;
	_renderBatches.emplace_back(_glyphPointers[0]->getTexture(), 0, 6);
	for (int i = 1; i < _glyphPointers.size(); i++)
	{
		if (_glyphPointers[i]->getTexture() != _glyphPointers[i - 1]->getTexture())
		{
			_renderBatches.emplace_back(RenderBatch(_glyphPointers[i]->getTexture(), startOffset, 6));
		}
		else {
			_renderBatches.back().verticesCount += 6;
		}

		_vertices[currentVertex++] = _glyphPointers[i]->leftBottom();
		_vertices[currentVertex++] = _glyphPointers[i]->rightBottom();
		_vertices[currentVertex++] = _glyphPointers[i]->topLeft();
		_vertices[currentVertex++] = _glyphPointers[i]->topLeft();
		_vertices[currentVertex++] = _glyphPointers[i]->topRight();
		_vertices[currentVertex++] = _glyphPointers[i]->rightBottom();
		

		startOffset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, _vertices.size() * sizeof(Vertex), &_vertices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::render()
{
	glBindVertexArray(_vao);
	
	for (int i = 0; i < _renderBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].getTexture());
		glDrawArrays(GL_TRIANGLES, _renderBatches[i].getStart(), _renderBatches[i].verticesCount);
	}

	_glyphs.clear();
	_renderBatches.clear();
	_currentGlyph = 0;

	glBindVertexArray(0);
}

bool SpriteBatch::compareTexture(GameObject *a, GameObject *b)
{
	return (a->getTexture() < b->getTexture());
}