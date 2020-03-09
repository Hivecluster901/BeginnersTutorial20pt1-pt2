#pragma once
#include "Graphics.h"
#include "SpriteCodex.h"
#include "Vec2.h"
#include "Ball.h"

class LifeCounter {

public:
	bool Dead(const Ball& ball);
	bool IsGameOver();
	void ResetRoundOverConditon();
	void Draw(Graphics& gfx) const;
private:
	static constexpr int maxLives = 3;
	int currentLives = maxLives;
	float gapbtwpoos = 40.0f;
	bool isRoundOver = true;
	bool isDeadAlreadyEvaluated = false;
	bool isGameOver = false;
};