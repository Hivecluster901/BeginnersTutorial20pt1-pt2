/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ball( ballStartingPos,ballStartingVel ),
	walls( topLeft - Vec2(0.0f, topLeft.y - borderWidth - padding), Vec2(topLeft.x + brickWidth * nBricksAcross,(float)gfx.ScreenHeight - borderWidth - padding) ),
	soundPad( L"Sounds\\arkpad.wav" ),
	soundBrick( L"Sounds\\arkbrick.wav" ),
	soundFart(L"Sounds\\fart.wav"),
	soundReady(L"Sounds\\ready.wav"),
	pad(paddleStartingPos,35.0f,7.0f )
{
	const Color colors[4] = { Colors::Red,Colors::Green,Colors::Blue,Colors::Cyan };

	int i = 0;
	for( int y = 0; y < nBricksDown; y++ )
	{
		const Color c = colors[y];
		for( int x = 0; x < nBricksAcross; x++ )
		{
			bricks[i] = Brick( RectF(
				topLeft + Vec2( x * brickWidth,y * brickHeight ),
				brickWidth,brickHeight ),c );
			i++;
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	float elapsedTime = ft.Mark();
	while( elapsedTime > 0.0f )
	{
		const float dt = std::min( 0.0025f,elapsedTime );
		UpdateModel( dt );
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel( float dt )
{
	if (!isGameStarted)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			isGameStarted = true;
		}
	}
	else if (!lifeCounter.IsGameOver())
	{
		if (!lifeCounter.Dead(ball))
		{
			soundReady.StopAll();
			soundReadyAlreadyPlayed = false;
			pad.Update(wnd.kbd, dt);
			pad.DoWallCollision(walls);

			ball.Update(dt);

			bool collisionHappened = false;
			float curColDistSq;
			int curColIndex;
			for (int i = 0; i < nBricks; i++)
			{
				if (bricks[i].CheckBallCollision(ball))
				{
					const float newColDistSq = (ball.GetPosition() - bricks[i].GetCenter()).GetLengthSq();
					if (collisionHappened)
					{
						if (newColDistSq < curColDistSq)
						{
							curColDistSq = newColDistSq;
							curColIndex = i;
						}
					}
					else
					{
						curColDistSq = newColDistSq;
						curColIndex = i;
						collisionHappened = true;
					}
				}
			}

			if (collisionHappened)
			{
				pad.ResetCooldown();
				bricks[curColIndex].ExecuteBallCollision(ball);
				soundBrick.Play();
			}

			if (pad.DoBallCollision(ball))
			{
				soundPad.Play();
			}

			if (ball.DoWallCollision(walls))
			{
				if (lifeCounter.Dead(ball))
				{
					soundFart.Play();
				}
				pad.ResetCooldown();
				soundPad.Play();
			}
		}
		else
		{
			if (!soundReadyAlreadyPlayed)
			{
				soundReady.Play();
				soundReadyAlreadyPlayed = true;
			}
			ball.ResetBall(ballStartingPos, ballStartingVel);
			lifeCounter.ResetRoundOverConditon(dt);
		}
	}
}

void Game::ComposeFrame()
{
	if (!isGameStarted)
	{
		SpriteCodex::DrawTitle(Vec2(400.0f, 300.0f), gfx);
	}
	else
	{
		for (Brick& b : bricks)
		{
			b.Draw(gfx);
		}
		lifeCounter.Draw(gfx);
		gfx.DrawBorder(walls, padding, borderWidth, Colors::Blue);
		pad.Draw(gfx);
		if (lifeCounter.IsGameOver())
		{
			SpriteCodex::DrawGameOver(Vec2(400.0f, 300.0f), gfx);
		}
		else if (lifeCounter.Dead(ball))
		{
			SpriteCodex::DrawReady(Vec2(400.0f, 300.0f), gfx);
		}
		else
		{
			ball.Draw(gfx);
		}
	}
}
