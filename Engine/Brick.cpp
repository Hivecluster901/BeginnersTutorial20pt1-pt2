#include "Brick.h"

Brick::Brick(const RectF& in_rect, Color in_c)
	:
	rect(in_rect),
	c(in_c)
{
}

void Brick::Draw(Graphics& gfx) const
{
	if (!isDestroyed)
	{
		gfx.DrawRect(rect.GetExpanded(-padding), c);
	}
}

bool Brick::DoBallCollision(Ball& ball)
{
	const Vec2 ballPos = ball.GetPosition();
	if (!isDestroyed && rect.isOverLappingWith(ball.GetRect()))
	{
		if (ballPos.x >= rect.left && ballPos.x <= rect.right)
		{
			ball.ReboundY();
		}
		else
		{
			ball.ReboundX();
		}
		isDestroyed = true;
		return true;
	}
	return false;
}
