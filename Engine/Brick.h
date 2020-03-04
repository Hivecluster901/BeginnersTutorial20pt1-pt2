#pragma once
#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"

class Brick 
{
public:
	Brick() = default;
	Brick(const RectF& in_rect, Color in_c);
	void Draw(Graphics& gfx) const;
	bool DoBallCollision(Ball& ball);
private:
	RectF rect;
	Color c;
	bool isDestroyed = false;

};