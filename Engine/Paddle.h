#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"
class Paddle {

public:
	Paddle(const Vec2& pos, float halfWidth, float halfHeight);
	void Draw(Graphics& gfx) const;
	RectF GetRect() const;
private:
	Vec2 pos;
	Color bodyColor = Colors::White;
	Color wingColor = Colors::Red;
	static constexpr float wingWidth = 20.0f;
	float halfWidth;
	float halfHeight;
};