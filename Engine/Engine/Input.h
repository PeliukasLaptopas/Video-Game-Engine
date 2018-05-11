#pragma once
#include <unordered_map>
#include <Box2D\Box2D.h>

using std::unordered_map;

namespace Eng {
class Input
{
public:
	Input(void);
	~Input(void);

	bool getKey(unsigned int keyCode) {
		return _currentKeyMap[keyCode];
	}

	bool getKeyDown(unsigned int keyCode) {
		if (wasKeyPressed(keyCode) == false && getKey(keyCode))
		{
			return true;
		}

		return false;
	}
	bool wasKeyPressed(unsigned int keyCode);


	bool getMouseButton(unsigned int keyCode) {
		return _currentMouseMap[keyCode];
	}

	bool getMouseButtonDown(unsigned int keyCode) {
		if (wasMousePressed(keyCode) == false && getMouseButton(keyCode))
		{
			return true;
		}

		return false;
	}
	bool wasMousePressed(unsigned int keyCode);

	b2Vec2 getMousePosition()
	{
		return _mousePosition;
	}

	friend class Window;

private:
	void pressedKey(unsigned int keyCode);
	void unpressedKey(unsigned int keyCode);
	void pressedMouseButton(unsigned int keyCode);
	void unpressedMouseButton(unsigned int keyCode);
	unordered_map<unsigned int, bool> _currentKeyMap;
	unordered_map<unsigned int, bool> _previousKeyMap; //Previous frame key map
	unordered_map<unsigned int, bool> _currentMouseMap;
	unordered_map<unsigned int, bool> _previousMouseMap; //Previous frame mouse map
	b2Vec2 _mousePosition;
};
}