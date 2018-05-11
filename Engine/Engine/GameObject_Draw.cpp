#include "GameObject_Draw.h"

/*GameObject::GameObject(const vec2 &pos, const vec2 &scale, const float &angle, const Color &color, const GLuint &texture, SpriteBatch& spriteBatch) {
	
vec2 lb(-halfScale.x, -halfScale.y); //left bottom
vec2 rb(halfScale.x, -halfScale.y); //right bottom
vec2 tr(halfScale.x, halfScale.y); //top right
vec2 tl(-halfScale.x, halfScale.y); //top left
									//Rotate the sprite. After we rotated this sprite lets get its origin (pivot point) back to its original bottom left by simply adding half scale of the sprite
lb = rotatePoint(lb, angle); //Galim prideti prie sito dar "+ halfScale" ir tada bus pivot point bottom left
rb = rotatePoint(rb, angle); //Galim prideti prie sito dar "+ halfScale" ir tada bus pivot point bottom left
tr = rotatePoint(tr, angle); //Galim prideti prie sito dar "+ halfScale" ir tada bus pivot point bottom left
tl = rotatePoint(tl, angle); //Galim prideti prie sito dar "+ halfScale" ir tada bus pivot point bottom left

_leftBottom.pos.x = pos.x + lb.x;
_leftBottom.pos.y = pos.y + lb.y;
_leftBottom.uv = vec2(0, 0);
_leftBottom.color = color;

_rightBottom.pos.x = pos.x + rb.x;
_rightBottom.pos.y = pos.y + rb.y;
_rightBottom.uv = vec2(1, 0);
_rightBottom.color = color;

_topLeft.pos.x = pos.x + tl.x;
_topLeft.pos.y = pos.y + tl.y;
_topLeft.uv = vec2(0, 1);
_topLeft.color = color;

_topRight.pos.x = pos.x + tr.x;
_topRight.pos.y = pos.y + tr.y;
_topRight.uv = vec2(1, 1);
_topRight.color = color;

_color = color;

_texture = texture;

_color = color;
_pos = pos;
_scale = scale;
_texture = texture;

spriteBatch.add(this);
}*/

using namespace Eng;

GameObject_Draw::GameObject_Draw()
{
}


GameObject_Draw::~GameObject_Draw()
{
}
