#include "Brick.h"

Brick::Brick(const RectF& in_rect, Color in_c)
	:
	rect(in_rect),
	c(in_c),
	isDestroyed(false)
{
}

void Brick::Draw(Graphics& gfx) const
{
	if (!isDestroyed)
	{
		gfx.DrawRect(rect.GetExpanded(-padding), c);
	}
}

bool Brick::CheckBallCollision(Ball& ball) const
{
	return !isDestroyed && rect.isOverLappingWith(ball.GetRect());
}

void Brick::ExecuteBallCollision(Ball& ball)
{
	const Vec2 ballPos = ball.GetPosition();
	if (ball.GetVelocity().x * (ballPos - GetCenter()).x > 0  )
	{
		ball.ReboundY();
	}
	else if (ballPos.x >= rect.left && ballPos.x <= rect.right)
	{
		ball.ReboundY();
	}
	else
	{
		ball.ReboundX();
	}
	isDestroyed = true;
}

Vec2 Brick::GetCenter() const
{
	return Vec2((rect.right + rect.left)/2.0f, (rect.bottom + rect.top) / 2.0f);
}
