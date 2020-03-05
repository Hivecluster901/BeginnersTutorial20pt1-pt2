#include "Brick.h"

Brick::Brick(const RectF& rect, Color color)
	:
	rect(rect),
	color(color)
{
}

void Brick::Draw(Graphics& gfx) const
{
	if (!isDestroyed)
	{
		gfx.DrawRect(rect.GetExpanded(-padding), color);
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
