#pragma once
#include"Vec2.h"
#include "Graphics.h"

class RectF {
public:
	RectF(float left_in, float right_in, float top_in, float bottom_in);
	RectF(const Vec2& topLeft, const Vec2& bottomRight);
	RectF(const Vec2& topLeft, float width, float height);
	static RectF FromCenter(const Vec2 center, float halfWidth, float halfHeight);
public:
	float left;
	float right; 
	float top; 
	float bottom;
};