#include "Paddle.h"

Paddle::Paddle(const Vec2 pos_in, float halfWidth_in, float halfHeight_in)
	:
	pos(pos_in),
	halfWidth(halfWidth_in),
	halfHeight(halfHeight_in)
{
}

void Paddle::Draw(Graphics& gfx) const
{
	RectF rect = GetRect();
	gfx.DrawRect(GetRect(), wingColor);
	rect.left += wingWidth;
	rect.right -= wingWidth; 
	gfx.DrawRect(rect, color);
}

bool Paddle::DoBallCollision(Ball& ball) const
{
	bool collided = false;
	if (ball.GetVelocity().y > 0.0f && GetRect().IsOverlappingWith(ball.GetRect()))
	{
		ball.ReboundY();
		collided = true;
	}
	return collided;
}

void Paddle::DoWallCollision(const RectF& walls)
{
	if (GetRect().left < walls.left)
	{
		pos.x += walls.left - GetRect().left;
	}
	else if (GetRect().right > walls.right)
	{
		pos.x -= GetRect().right - walls.right;
	}
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

RectF Paddle::GetRect() const
{
	return RectF::FromCeter(pos, halfWidth, halfHeight);
}
