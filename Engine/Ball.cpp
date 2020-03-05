#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(const Vec2& pos_in, const Vec2& vel_in)
	:
	pos(pos_in),
	vel(vel_in)
{
}

void Ball::Draw(Graphics& gfx) const
{
	SpriteCodex::DrawBall(pos, gfx);
}

RectF Ball::GetRect() const
{
	return RectF::FromCenter(pos, radius, radius);
}

void Ball::Update(float dt)
{
	pos += vel * dt;
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}

bool Ball::DoWallCollision(const RectF& walls)
{
	const RectF rect = GetRect();
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
		ReboundX();
		return true;
	}
	else if (rect.right > walls.right)
	{
		pos.x -= rect.right - walls.right;
		ReboundX();
		return true;
	}
	if (rect.top < walls.top)
	{
		pos.y += walls.top - rect.top;
		ReboundY();
		return true;
	}
	else if (rect.bottom > walls.bottom)
	{
		pos.y -= rect.bottom - walls.bottom;
		ReboundY();
		return true;
	}
	return false;
}
