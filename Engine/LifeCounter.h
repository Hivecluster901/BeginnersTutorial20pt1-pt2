#pragma once
#include "Graphics.h"
#include "SpriteCodex.h"
#include "Vec2.h"

class LifeCounter {

public:
	void Dead();
	void Draw(Graphics& gfx) const; 
private:
	static constexpr int maxLives = 5;
	int currentLives = maxLives;
	float gapbtwpoos = 20.0f;
	bool isRoundOver;
};