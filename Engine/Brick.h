#pragma once
#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"

class Brick 
{
public:
	Brick(const RectF& in_rect, Color in_c);
	void Draw(Graphics& gfx) const;
private:
	RectF rect;
	Color c;
	bool isDestroyed = false;

};