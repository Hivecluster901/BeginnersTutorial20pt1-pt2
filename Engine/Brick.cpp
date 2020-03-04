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
		gfx.DrawRect(rect, c);
	}
}

bool Brick::DoBallCollision(Ball& ball)
{
	if (!isDestroyed && rect.isOverLappingWith(ball.GetRect()))
	{
		ball.ReboundY();
		isDestroyed = true;
		return true;
	}
	return false;
}
