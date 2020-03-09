#pragma once
#include "Graphics.h"
#include "SpriteCodex.h"
#include "Vec2.h"
#include "Ball.h"
#include "Keyboard.h"

class LifeCounter {

public:
	bool Dead(const Ball& ball);
	bool IsGameOver();
	void ResetRoundOverConditon(const Keyboard& kbd);
	void Draw(Graphics& gfx) const;
private:
	static constexpr int maxLives = 5;
	int currentLives = maxLives;
	float gapbtwpoos = 40.0f;
	bool isRoundOver = true;
	bool isDeadAlreadyEvaluated = false;
	bool isGameOver = false;
};