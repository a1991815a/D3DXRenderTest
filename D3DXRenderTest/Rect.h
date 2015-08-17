#ifndef __RECT__
#define __RECT__

class Rect{
public:
	Rect()
		:x(0), y(0), width(0), height(0)
	{};
	Rect(float x, float y, float width, float height)
		:x(x), y(y), width(width), height(height)
	{};
	Rect(const Rect& rect) 
		:x(rect.x), y(rect.y), width(rect.width), height(rect.height)
	{};
	float x, y;
	float width, height;
};
#endif