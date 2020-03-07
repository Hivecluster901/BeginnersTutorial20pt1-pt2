#pragma once

#include "Vec2.h"
#include "Graphics.h"

class Ball
{
public:
	Ball() = default;
	void Draw( Graphics& gfx ) const;
	void Update( float dt );
	bool DoWallCollision( const RectF& walls );
	bool IsCollidedWithBottom() const;
	void ReboundX();
	void ReboundY();
	void Reset();
	RectF GetRect() const;
	Vec2 GetVelocity() const;
	Vec2 GetPosition() const;
private:
	static constexpr float radius = 7.0f;
	Vec2 ballStartingPos = { 200.0f , 300.0f };
	Vec2 ballStartingVel = Vec2(300.0f, 300.0f);
	Vec2 pos = ballStartingPos;
	Vec2 vel = ballStartingVel;
	bool isCollidedWithBottom = false;
};