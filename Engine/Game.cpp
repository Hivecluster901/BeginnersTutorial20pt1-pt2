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
	walls( 0.0f,float( gfx.ScreenWidth ),0.0f,float( gfx.ScreenHeight ) ),
	ball(ballStartingPos, ballStartingVel),
	soundPad( L"Sounds\\arkpad.wav" ),
	soundBrick( L"Sounds\\arkbrick.wav" ),
	soundReady(L"Sounds\\ready.wav"),
	pad(paddleStartingPos,50.0f,15.0f )
{
	const Color colors[4] = { Colors::Red,Colors::Green,Colors::Blue,Colors::Cyan };

	const Vec2 topLeft( 40.0f,40.0f );

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
	for (int j = 0; j < maxLives - 1; j++)
	{
		lives[j] = Ball(Vec2(40.0f + 20.0f * j, 20.0f),Vec2(0.0f, 0.0f));
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
	if (!isGameStarted && !isGameCompletelyOver)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			isGameStarted = true;
		}
	}
	else
	{
		if (!isGameOver)
		{
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
				pad.ResetCooldown();
				soundPad.Play();
				if (ball.IsCollidedWithBottom())
				{
					isGameOver = true;
					remainingLives--;
				}
			}
		}
		else if (isGameOver && remainingLives > 0)
		{
			if (wnd.kbd.KeyIsPressed(VK_RETURN))
			{
				isGameOver = false;
			}
			//soundReady.Play(1.0F, 0.05F);
			ball.Reset(ballStartingPos, ballStartingVel);
			pad.Reset(paddleStartingPos);
		}
		else
		{
			isGameCompletelyOver = true;
		}
	}	
}


void Game::ComposeFrame()
{
	if (!isGameStarted)
	{
		SpriteCodex::DrawTitle(screenCenter, gfx);
	}
	else if( !isGameCompletelyOver)
	{
		if (isGameOver)
		{
			SpriteCodex::DrawReady(screenCenter, gfx);
		}
		ball.Draw(gfx);
		for (const Brick& b : bricks)
		{
			b.Draw(gfx);
		}
		pad.Draw(gfx);
		for (int i = 0; i < remainingLives - 1; i++)
		{
			lives[i].Draw(gfx);
		}
	}
	else if(isGameCompletelyOver)
	{ 
		SpriteCodex::DrawGameOver(screenCenter,gfx);
	}
}
