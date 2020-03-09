#include "LifeCounter.h"


bool LifeCounter::Dead(const Ball& ball)
{
	if (ball.BottomCollision() && !isDeadAlreadyEvaluated)
	{
		currentLives--;
		isRoundOver = true;
		isDeadAlreadyEvaluated = true;
	}
	return isRoundOver;
}

bool LifeCounter::IsGameOver()
{
	if (currentLives <= 0)
	{
		isGameOver = true;
	}
	return isGameOver;
}

void LifeCounter::ResetRoundOverConditon(float dt)
{
	readyTimeCounter -= std::fmin(dt, readyTimeCounter);
	if (readyTimeCounter == 0.0f)
	{
		isRoundOver = false;
		isDeadAlreadyEvaluated = false;
		readyTimeCounter = readyTime;
	}
}

void LifeCounter::Draw(Graphics& gfx) const
{
	for (int i = 0; i < currentLives - 1; i++)
	{
		SpriteCodex::DrawPoo(Vec2(25.0f + gapbtwpoos * i, 25.0f), gfx);
	}
}
