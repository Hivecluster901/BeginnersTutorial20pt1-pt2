/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "Ball.h"
#include "Sound.h"
#include "Brick.h"
#include "Paddle.h"
#include "LifeCounter.h"
#include "SpriteCodex.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel( float dt );
	/********************************/
	/*  User Functions              */
	void DrawBorder(Graphics& gfx) const;
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	static constexpr float brickWidth = 40.0f;
	static constexpr float brickHeight = 24.0f;
	static constexpr int nBricksAcross = 12;
	static constexpr int nBricksDown = 4;
	static constexpr int nBricks = nBricksAcross * nBricksDown;
	static constexpr float borderWidth = 10.0f;
	static constexpr float padding = 1.0f;
	bool soundReadyAlreadyPlayed = false;
	bool isGameStarted = false;
	FrameTimer ft;
	LifeCounter lifeCounter;
	Vec2 ballStartingPos = Vec2(324.0f, 300.0f);
	Vec2 ballStartingVel = Vec2(-300.0f, -300.0f);
	Vec2 paddleStartingPos = Vec2(400.0f, 525.0f);
	Vec2 bricksCenter = Vec2(400.0f, 150.0f);
	const Vec2 topLeft = bricksCenter - Vec2(nBricksAcross / 2.0f * brickWidth, nBricksDown / 2.0f * brickHeight);
	Ball ball;
	Brick bricks[nBricks];
	Paddle pad;
	RectF walls;
	Sound soundPad;
	Sound soundBrick;
	Sound soundFart;
	Sound soundReady;
	/********************************/
};