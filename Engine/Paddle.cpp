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

void Paddle::Update(const Keyboard& kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= speed * dt;
	}
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += speed * dt;
	}
}

bool Paddle::DoBallCollision(Ball& ball)
{
	const RectF rect = GetRect();
	if (ball.GetVelocity().y > 0 && rect.IsOverlappingWith(ball.GetRect()) && GetRect().left < ball.GetPosition().x && ball.GetPosition().x < GetRect().right)
	{
		ball.ReboundY();
		return true;
	}
	else if (ball.GetVelocity().y > 0 && rect.IsOverlappingWith(ball.GetRect()) && GetRect().top < ball.GetPosition().y && ball.GetPosition().y < GetRect().bottom)
	{
		ball.ReboundX();
		return true;
	}
		return false;
}

void Paddle::DoWallCollision(const RectF& walls)
{
	const RectF rect = GetRect();
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
	}
	else if (rect.right > walls.right)
	{
		pos.x -= rect.right - walls.right;
	}
}