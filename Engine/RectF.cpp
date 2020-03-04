#include "RectF.h"

RectF::RectF(float in_left, float in_right, float in_top, float in_bottom)
	:
	left(in_left),
	right(in_right),
	top(in_top),
	bottom(in_bottom)
{
}

RectF::RectF(const Vec2& topleft, const Vec2& bottomright)
	:
	RectF(topleft.x, bottomright.x, topleft.y, bottomright.y)
{
}

RectF::RectF(const Vec2& topleft, float width, float height)
	:
	RectF(topleft, topleft + Vec2(width, height))
{
}

bool RectF::isOverLappingWith(const RectF& other) const
{
	return right > other.left&& bottom > other.top
		&& left < other.right && top < other.bottom;
}
