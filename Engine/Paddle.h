#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "RectF.h"
#include "Colors.h"
#include "Keyboard.h"
#include "Ball.h"

class Paddle {
public:
	Paddle(const Vec2& pos_in, float halfWidth_in, float halfHeight_in);
	void Draw(Graphics& gfx) const;
	void Update(const Keyboard& kbd, float dt);
	bool DoBallCollision(Ball& ball) const;
	void DoWallCollision(const RectF& walls);
	RectF GetRect() const;
private:
	Vec2 pos;
	Color color = Colors::White;
	float halfWidth;
	float halfHeight;
	static constexpr float speed = 300.0f;
};
