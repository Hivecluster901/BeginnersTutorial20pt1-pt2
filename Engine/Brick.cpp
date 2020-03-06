#include "Brick.h"

Brick::Brick(const RectF& rect_in, Color color_in)
	:
	rect(rect_in),
	color(color_in)
{
}

void Brick::Draw(Graphics& gfx) const
{
	if (!isDestroyed)
	{
		gfx.DrawRect(rect, color);
	}
}

bool Brick::DoBallCollision(Ball& ball)
{
	if (!isDestroyed && rect.IsOverlappingWith(ball.GetRect()))
	{
		ball.ReboundY();
		isDestroyed = true;
		return true;
	}
	return false;
}

