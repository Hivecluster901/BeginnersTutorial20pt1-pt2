#pragma once
#include "Graphics.h"
#include "SpriteCodex.h"
#include "Vec2.h"
#include "Ball.h"
#include <cmath>

class LifeCounter {

public:
	bool Dead(const Ball& ball);
	bool IsGameOver();
	void ResetRoundOverConditon(float dt);
	void Draw(Graphics& gfx) const;
private:
	static constexpr int maxLives = 3;
	static constexpr float readyTime = 4.5f;
	int currentLives = maxLives;
	float readyTimeCounter = readyTime;
	float gapbtwpoos = 40.0f;
	bool isRoundOver = true;
	bool isDeadAlreadyEvaluated = false;
	bool isGameOver = false;
};