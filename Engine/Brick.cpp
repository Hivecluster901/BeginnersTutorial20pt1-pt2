#include "Brick.h"
#include <assert.h>
#include <cmath>

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

bool Brick::CheckBallCollision(const Ball& ball) const
{
	return !isDestroyed && rect.isOverLappingWith(ball.GetRect());
}

void Brick::ExecuteBallCollision(Ball& ball)
{
	assert(CheckBallCollision(ball));
	const Vec2 ballPos = ball.GetPosition();
	if (std::signbit(ball.GetVelocity().x) == std::signbit((ballPos - GetCenter()).x))
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
	return rect.GetCenter();
}
