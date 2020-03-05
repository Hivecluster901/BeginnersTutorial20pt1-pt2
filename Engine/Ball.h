#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "RectF.h"

class Ball {

public:
	Ball(const Vec2& pos_in, const Vec2& vel_in);
	void Draw(Graphics& gfx) const;
	void update(float dt);
	bool DoWallCollision(const RectF& walls);
	RectF GetRect() const;
	void ReboundX();
	void ReboundY();
private:
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;
};