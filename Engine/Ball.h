#pragma once

#include "Vec2.h"
#include "Graphics.h"

class Ball
{
public:
	Ball() = default;
	Ball(const Vec2& pos_in, const Vec2& vel_in);
	void Draw( Graphics& gfx ) const;
	void Update( float dt );
	bool DoWallCollision( const RectF& walls );
	bool IsCollidedWithBottom() const;
	void ReboundX();
	void ReboundY();
	void Reset(const Vec2& startingPos, const Vec2& startingVel);
	RectF GetRect() const;
	Vec2 GetVelocity() const;
	Vec2 GetPosition() const;
private:
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;
	bool isCollidedWithBottom = false;
};