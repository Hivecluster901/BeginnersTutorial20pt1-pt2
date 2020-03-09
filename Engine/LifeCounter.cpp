#include "LifeCounter.h"

void LifeCounter::Dead(const Ball& ball)
{
	if (ball.BottomCollision())
	{
		currentLives--;
		isRoundOver = true;
	}
}

void LifeCounter::Draw(Graphics& gfx) const
{
	for (int i = 0; i < currentLives; i++)
	{
		SpriteCodex::DrawPoo(Vec2(25.0f, 25.0f + gapbtwpoos * i), gfx);
	}
}
