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
    walls(0.0f, (float)gfx.ScreenWidth, 0.0f, (float)gfx.ScreenHeight),
    ball(Vec2(300.0f, 300.0f), Vec2(300.0f, 300.0f)),
    pad(Vec2(500.0f,500.0f), 50.0f, 15.0f),
    soundPad(L"Sounds\\arkpad.wav"),
    soundBrick(L"Sounds\\arkbrick.wav")
{
    const Color color[nBricksDown] = { Colors::Red, Colors::Green, Colors::Blue, Colors::Cyan };
    const Vec2 topLeft(40.0f, 40.0f);
    int i = 0;
    for (int y = 0; y < nBricksDown; y++)
    {
        Color c = color[y];
        for (int x = 0; x < nBricksAcross; x++)
        {
            bricks[i] = Brick(RectF(topLeft + Vec2(brickWidth * x, brickHeight * y), brickWidth, brickHeight), c);
            i++;
        }
    }
    
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
    float dt = ft.Mark();
    pad.Update(wnd.kbd, dt);
    pad.DoWallCollision(walls);
    ball.Update(dt);
    if (ball.DoWallCollision(walls))
    {
        soundPad.Play();
    }
    if (pad.DoBallCollision(ball))
    {
        soundPad.Play();
    }
    for (Brick& brick : bricks)
    {
        if (brick.DoBallCollision(ball))
        {
            soundBrick.Play();
        }
    }
}

void Game::ComposeFrame()
{
    for (const Brick& brick : bricks)
    {
        brick.Draw(gfx);
    }
    ball.Draw(gfx);
    pad.Draw(gfx);
}
