#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
#pragma region ExampleArray
	/*for (int i{0}; i < 200; i++)
	{
		g_Boxes[i].rect.left = 10.0f;
		g_Boxes[i].rect.bottom = 10.0f * i;
		g_Boxes[i].rect.width = float(GenerateRandom(10, 100));
		g_Boxes[i].rect.height = float(GenerateRandom(10, 15));
	}*/
#pragma endregion
	InitialiseBoxes();
}

void Draw()
{
	ClearBackground(0,0,0);

	// Put your own draw statements here
	if (!g_IsMainMenuActive)
	{
		SetColor(g_SoftBlue);
		DrawPlatform(g_PlatformPos, g_PlatformLength, g_PlatformHeight);
		DrawBall(g_MainBallPos, g_MainBallRadius);
	}
	else 
	{
		//DrawMainMenu();
		for (int i{ 0 }; i < g_AmountOfBoxes; i++)
		{
			SetColor(RandomColor());
			FillRect(g_Boxes[i].rect);
		}
	}
	
}

void Update(float elapsedSec)
{
	// process input, do physics 

	// e.g. Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
	if (!g_IsMainMenuActive)
	{
		g_PlatformPos.x = g_MousePos.x;
		UpdateBall(g_MainBallPos, g_MainBallRadius, g_MainBallVelocity, elapsedSec, g_MainBallUpDown, g_MainBallLeftRight);
		UpdateBox(g_PlatformRect, g_MainBallPos, g_MainBallUpDown, g_MainBallLeftRight, true);
		if (g_ShowDebugging) std::cout << "FRAMERATE: " << 1 / elapsedSec << std::endl;
	}
}

void End()
{
	// free game resources here
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{

}

void OnKeyUpEvent(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_SPACE:
		std::cout << "Space key released\n";
		g_MainBallFreeze = false;
		break;
	}
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	g_MousePos.x = float(e.x); 
	g_MousePos.y = float(g_WindowHeight - e.y);
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{

}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
	{
		std::cout << "Left mouse button released\n";
		g_ClickedMousePos.x = float(e.x);
		g_ClickedMousePos.y = float(g_WindowHeight - e.y);
		break;
	}
	}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here
void DrawPlatform(float x, float y, float totLength, float totHeight)
{
	FillRect(x - totLength / 2, y - totHeight / 2, totLength, totHeight);
	g_PlatformRect.left = x - totLength / 2;
	g_PlatformRect.bottom = y - totHeight / 2;
	g_PlatformRect.width = totLength;
	g_PlatformRect.height = totHeight;
}
void DrawPlatform(const Point2f& midPos, float totLength, float totHeight)
{
	DrawPlatform(midPos.x, midPos.y, totLength, totHeight);
}

void DrawBall(float x, float y, float r)
{
	FillEllipse(x, y, r, r);
}
void DrawBall(const Point2f& pos, float r)
{
	DrawBall(pos.x, pos.y, r);
}

void UpdateBall(float& x, float& y, float r, float velocity, float elapsedSec, Direction& upDown, Direction& leftRight)
{
	if (!g_MainBallFreeze) 
	{
		// Hit right side
		if (x <= r) 
		{
			leftRight = Direction::right;
			if (g_ShowDebugging) std::cout << "LeftRight Direction: " << int(g_MainBallLeftRight) << std::endl;
		}
		// Hit left side
		else if (x >= g_WindowWidth - r)
		{
			leftRight = Direction::left;
			if (g_ShowDebugging) std::cout << "LeftRight Direction: " << int(g_MainBallLeftRight) << std::endl;
		}
		// Hit bottom
		if (y <= r) 
		{
			if (g_Lives > 0) g_MainBallUpDown = Direction::up;
			DestroyBall(x, y);
			if (g_ShowDebugging) std::cout << "UpDown Direction: " << int(g_MainBallUpDown) << std::endl;
		}
		// Hit top
		else if (y >= (g_WindowHeight - r)) 
		{
			upDown = Direction::down;
			if (g_ShowDebugging) std::cout << "UpDown Direction: " << int(g_MainBallUpDown) << std::endl;
		}
		x += velocity * elapsedSec * int(g_MainBallLeftRight);
		y += velocity * elapsedSec * int(g_MainBallUpDown);
	}
	else if (g_Lives <= 0) 
	{
		g_MainBallPos.y = - r;
	}
	else 
	{
		x = g_PlatformPos.x;
		y = g_PlatformPos.y + g_PlatformHeight + r;
	}
}
void UpdateBall(Point2f& pos, float r, float velocity, float elapsedSec, Direction& upDown, Direction& leftRight)
{
	UpdateBall(pos.x, pos.y, r, velocity, elapsedSec, upDown, leftRight);
}

void DestroyBall(float x, float y) 
{
	if ((x == g_MainBallPos.x) && (y == g_MainBallPos.y))
	{
		if (g_Lives > 0)
		{
			--g_Lives;
			x = g_PlatformPos.x;
			y = g_PlatformPos.y + (g_PlatformHeight / 2) + g_MainBallRadius;
			g_MainBallFreeze = true;
		}
		else
		{
			std::cout << "Game over!\n";
			g_MainBallFreeze = true;
		}
	}
}
void DestroyBall(Point2f& pos)
{
	DestroyBall(pos.x, pos.y);
}

void UpdateBox(Rectf& rect, const Point2f& ballPos, Direction& upDown, Direction& leftRight, bool isPlatform) 
{
	if(CheckInsideRect(rect.left,rect.bottom,rect.width,rect.height, ballPos))
	{
		float offSet{ 2 };
		if (isPlatform) 
		{
			// Hitting left
			if (ballPos.x <= rect.left + offSet) 
			{
				if (g_ShowDebugging) std::cout << "Hitting left of platform\n";
				leftRight = Direction::left;
			}
			// Hitting right
			else if (ballPos.x >= rect.left + rect.width - offSet)
			{
				if (g_ShowDebugging) std::cout << "Hitting right of platform\n";
				leftRight = Direction::right;
			}
			// Hitting bottom
			else if (ballPos.y <= rect.bottom + offSet)
			{
				if (g_ShowDebugging) std::cout << "Hitting bottom of platform\n";
				upDown = Direction::down;
			}
			// Hitting top
			else if (ballPos.y >= rect.bottom + rect.height - offSet)
			{
				// Depending on what side of the platform the ball hits the platform, the direction will change
				if (ballPos.x >= rect.left + rect.width / 2) leftRight = Direction::right;
				else leftRight = Direction::left;
				//
				if (g_ShowDebugging) std::cout << "Hitting top of platform\n";
				upDown = Direction::up;
			}
		}
		
		else { // Standard procedure
			// Hitting left
			if (ballPos.x <= rect.left + offSet)
			{
				if (g_ShowDebugging) std::cout << "Hitting left of box\n";
				leftRight = Direction::left;
				DestroyBox(rect);
			}
			// Hitting right
			else if (ballPos.x >= rect.left + rect.width - offSet)
			{
				if (g_ShowDebugging) std::cout << "Hitting right of box\n";
				leftRight = Direction::right;
				DestroyBox(rect);
			}
			// Hitting bottom
			else if (ballPos.y <= rect.bottom + offSet)
			{
				if (g_ShowDebugging) std::cout << "Hitting bottom of box\n";
				upDown = Direction::down;
				DestroyBox(rect);
			}
			// Hitting top
			else if (ballPos.y >= rect.bottom + rect.height - offSet)
			{
				if (g_ShowDebugging) std::cout << "Hitting top of box\n";
				upDown = Direction::up;
				DestroyBox(rect);
			}
		}
	}
}

void DestroyBox(Rectf& rect) 
{
	rect.left = -rect.width - 1;
}

void DrawMainMenu() 
{
	const float buttonLength{ 150 }, buttonHeight{ 30 };
#pragma region StartButton
	const Rectf startButton{ (g_WindowWidth / 2) - (buttonLength / 2), (g_WindowHeight / 2) - (buttonHeight / 2), buttonLength, buttonHeight };
	SetColor(g_SoftBlue);
	FillRect(startButton);
	if (CheckInsideRect(startButton.left,startButton.bottom,startButton.width,startButton.height,g_ClickedMousePos)) 
	{
		if (g_ShowDebugging) std::cout << "Start clicked\n";
		g_IsMainMenuActive = false;
	}
#pragma endregion
#pragma region InfoButton
	const Rectf infoButton{startButton.left, startButton.height - buttonHeight - 10, buttonLength, buttonHeight};
	SetColor(g_SoftYellow);
	FillRect(infoButton);
	if (CheckInsideRect(infoButton.left, infoButton.bottom, infoButton.width, infoButton.height, g_ClickedMousePos))
	{
		if (g_ShowDebugging) std::cout << "Info clicked\n";
	}
#pragma endregion

}

void InitialiseBoxes()
{
	const float offSet{10};
	const float boxLength{ g_WindowWidth / sqrtf(g_AmountOfBoxes) - offSet };
	for (unsigned int i{ 0 }; i < g_AmountOfBoxes; i++)
	{
		g_Boxes[i].rect.width = boxLength;
		g_Boxes[i].rect.height = boxLength;
		g_Boxes[i].rect.bottom = offSet + i * g_Boxes[i].rect.height;
		g_Boxes[i].rect.left = offSet + i * g_Boxes[i].rect.width;
	}
}
#pragma endregion ownDefinitions