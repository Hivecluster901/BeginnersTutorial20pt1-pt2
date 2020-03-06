#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"
#include "Ball.h"
#include "Keyboard.h"
class Paddle {

public:
	Paddle(const Vec2& pos, float halfWidth, float halfHeight);
	void Draw(Graphics& gfx) const;
	RectF GetRect() const;
	void Update( const Keyboard& kbd, float dt);
	bool DoBallCollision(Ball& ball);
	void DoWallCollision(const RectF& walls);
private:
	Vec2 pos;
	Color bodyColor = Colors::White;
	Color wingColor = Colors::Red;
	static constexpr float wingWidth = 20.0f;
	static constexpr float speed = 300.0f;
	float halfWidth;
	float halfHeight;
};