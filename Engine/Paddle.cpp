#include "Paddle.h"

Paddle::Paddle(const Vec2& pos, float halfWidth, float halfHeight)
	:
	pos(pos),
	halfWidth(halfWidth),
	halfHeight(halfHeight)
{
}

void Paddle::Draw(Graphics& gfx) const
{
	RectF& rect = GetRect();
	gfx.DrawRect(rect, wingColor);
	rect.left += wingWidth;
	rect.right -= wingWidth;
	gfx.DrawRect(rect, bodyColor);
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(pos, halfWidth, halfHeight);
}
