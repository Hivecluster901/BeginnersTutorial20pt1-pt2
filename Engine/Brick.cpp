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
		gfx.DrawRect(rect.GetExpanded(-padding), color);
	}
}

bool Brick::DoBallCollision(Ball& ball)
{
	if (!isDestroyed && rect.IsOverlappingWith(ball.GetRect()) && rect.top < ball.GetPosition().y && ball.GetPosition().y < rect.bottom)
	{
		ball.ReboundX();
		isDestroyed = true;
		return true;
	}
	else if (!isDestroyed && rect.IsOverlappingWith(ball.GetRect()) && rect.left < ball.GetPosition().x && ball.GetPosition().x < rect.right)
	{
		ball.ReboundY();
		isDestroyed = true;
		return true;
	}
	return false;
}

