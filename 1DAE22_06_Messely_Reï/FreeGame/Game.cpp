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
		SetColor(g_SoftYellow);
		for (int i{ 0 }; i < g_AmountOfBoxes; i++)
		{
			if (g_Boxes[i].isVisible) FillRect(g_Boxes[i].rect);
		}
		SetColor(g_SoftBlue);
		DrawPlatform(g_PlatformPos, g_PlatformLength, g_PlatformHeight);
		SetColor(1, 1, 1, 1);
		DrawBall(g_MainBallPos, g_MainBallRadius);
	}
	else 
	{
		DrawMainMenu();
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
		UpdatePlatform(g_PlatformRect, g_MainBallPos, g_MainBallUpDown, g_MainBallLeftRight);
		if (g_ShowDebugging) std::cout << "FRAMERATE: " << 1 / elapsedSec << std::endl;
		for (unsigned int i{ 0 }; i < g_AmountOfBoxes; i++) 
		{
			UpdateBox(g_Boxes[i], g_MainBallPos, g_MainBallUpDown, g_MainBallLeftRight);
		}
		g_PassedTime += elapsedSec;
		if (g_AmountHit >= g_AmountOfBoxes) // If no boxes are left
		{
			g_IsMainMenuActive = true;
			std::cout << "You finished the game with " << g_Lives << " lives and a time of " << g_PassedTime << std::endl;
			g_Lives = 3;
			g_PassedTime = 0;
			g_AmountHit = 0;
			g_ClickedMousePos.x = -1;
			for (int i {0}; i < g_AmountOfBoxes; i++) 
			{
				g_Boxes[i].isVisible = true;
			}
		}
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
		if (g_ShowDebugging) std::cout << "Space key released\n";
		g_MainBallFreeze = false;
		break;
	case SDLK_d:
		if (g_ShowDebugging) std::cout << "DEBUG OFF\n";
		else std::cout << "DEBUG ON\n";
		g_ShowDebugging = !g_ShowDebugging;
		break;
	case SDLK_i:
		ShowInfo();
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
		if(g_ShowDebugging) std::cout << "Left mouse button released\n";
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
			g_IsMainMenuActive = true;
			g_Lives = 3;
			g_PassedTime = 0;
			g_AmountHit = 0;
			g_ClickedMousePos.x = -1;
			for (int i{ 0 }; i < g_AmountOfBoxes; i++)
			{
				g_Boxes[i].isVisible = true;
			}
		}
	}
}
void DestroyBall(Point2f& pos)
{
	DestroyBall(pos.x, pos.y);
}

void UpdatePlatform(Rectf& rect, const Point2f& ballPos, Direction& upDown, Direction& leftRight)
{
	if (CheckInsideRect(rect.left, rect.bottom, rect.width, rect.height, ballPos))
	{
		float offSet{ 2 };
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
}

void UpdateBox(BreakableBox& box, const Point2f& ballPos, Direction& upDown, Direction& leftRight) 
{
	if(CheckInsideRect(box.rect.left, box.rect.bottom, box.rect.width, box.rect.height, ballPos))
	{
		if (box.isVisible) 
		{
			float offSet{ 2 };
			// Hitting left
			if (ballPos.x <= box.rect.left + offSet)
			{
				if (g_ShowDebugging) std::cout << "Hitting left of box\n";
				leftRight = Direction::left;
				HideBox(box);
			}
			// Hitting right
			else if (ballPos.x >= box.rect.left + box.rect.width - offSet)
			{
				if (g_ShowDebugging) std::cout << "Hitting right of box\n";
				leftRight = Direction::right;
				HideBox(box);
			}
			// Hitting bottom
			else if (ballPos.y <= box.rect.bottom + offSet)
			{
				if (g_ShowDebugging) std::cout << "Hitting bottom of box\n";
				upDown = Direction::down;
				HideBox(box);
			}
			// Hitting top
			else if (ballPos.y >= box.rect.bottom + box.rect.height - offSet)
			{
				if (g_ShowDebugging) std::cout << "Hitting top of box\n";
				upDown = Direction::up;
				HideBox(box);
			}		
		}
	}
}

void HideBox(BreakableBox& box) 
{
	box.isVisible = false;
	++g_AmountHit;
}

void DrawMainMenu() 
{
#pragma region Title
	SetColor(g_SoftGreen);
	const Point2f startingPoint{ 120,200 };
	FontLoader('B', startingPoint, 7, 7, 2);
	FontLoader('R', startingPoint.x + 32, startingPoint.y, 7, 7, 2);
	FontLoader('E', startingPoint.x + 64, startingPoint.y, 7, 7, 2);
	FontLoader('A', startingPoint.x + 96, startingPoint.y, 7, 7, 2);
	FontLoader('K', startingPoint.x + 128, startingPoint.y, 7, 7, 2);
	FontLoader('I', startingPoint.x + 192, startingPoint.y, 7, 7, 2);
	FontLoader('N', startingPoint.x + 224, startingPoint.y, 7, 7, 2);
#pragma endregion
	const float buttonLength{ 150 }, buttonHeight{ 30 };
#pragma region StartButton
	const Rectf startButton{ (g_WindowWidth / 2) - (buttonLength / 2), (g_WindowHeight / 2) - (buttonHeight / 2), buttonLength, buttonHeight };
	const float xOffsetStartText{35};
	SetColor(g_SoftBlue);
	FillRect(startButton);
	FontLoader('S', startButton.left + 2 + xOffsetStartText, startButton.bottom-3, 3, 4, 1);
	FontLoader('T', startButton.left + 16 + xOffsetStartText, startButton.bottom - 3, 3, 4, 1);
	FontLoader('A', startButton.left + 32 + xOffsetStartText, startButton.bottom - 3, 3, 4, 1);
	FontLoader('R', startButton.left + 48 + xOffsetStartText, startButton.bottom - 3, 3, 4, 1);
	FontLoader('T', startButton.left + 64 + xOffsetStartText, startButton.bottom - 3, 3, 4, 1);
	if (CheckInsideRect(startButton.left,startButton.bottom,startButton.width,startButton.height,g_ClickedMousePos)) 
	{
		if (g_ShowDebugging) std::cout << "Start clicked\n";
		g_IsMainMenuActive = false;
	}
#pragma endregion
#pragma region InfoButton
	const Rectf infoButton{startButton.left, startButton.bottom - buttonHeight - 10, buttonLength, buttonHeight};
	const float xOffsetInfoText{ 40 };
	SetColor(g_SoftYellow);
	FillRect(infoButton);
	FontLoader('I', infoButton.left + 2 + xOffsetInfoText, infoButton.bottom - 3, 3, 4, 1);
	FontLoader('N', infoButton.left + 16 + xOffsetInfoText, infoButton.bottom - 3, 3, 4, 1);
	FontLoader('F', infoButton.left + 32 + xOffsetInfoText, infoButton.bottom - 3, 3, 4, 1);
	FontLoader('O', infoButton.left + 48 + xOffsetInfoText, infoButton.bottom - 3, 3, 4, 1);
	if (CheckInsideRect(infoButton.left, infoButton.bottom, infoButton.width, infoButton.height, g_ClickedMousePos))
	{
		if (g_ShowDebugging) std::cout << "Info clicked\n";
		g_ClickedMousePos.x = -1; // Out of bounds to prevent multiple triggers
		ShowInfo();
	}
#pragma endregion

}

void InitialiseBoxes()
{
	const float yOffSet{150};
	const int amount{ int(sqrt(g_AmountOfBoxes)) };
	const float spaceBetween{5};
	const float boxLength{ (g_WindowWidth - (amount + 1) * spaceBetween) / 12.0f};
	for (unsigned int i{ 0 }; i < g_AmountOfBoxes; i++)
	{
		g_Boxes[i].rect.width = boxLength;
		g_Boxes[i].rect.height = 5;
		g_Boxes[i].rect.left = (i%amount + 1) * spaceBetween + (i%amount * g_Boxes[i].rect.width); 
		g_Boxes[i].rect.bottom = yOffSet + ((i/amount) + 1) * spaceBetween + (i/amount) * g_Boxes[i].rect.height;
		g_Boxes[i].isVisible = true;
	}
}

void ShowInfo()
{
	std::cout
		<< "\n== BREAK IN INFO ==\n"
		<< "You have 3 balls and need to break all the blocks\n"
		<< " - Mouse to move platform\n"
		<< " - Space to launch ball\n"
		<< " - Space to respawn ball\n"
		<< " - D to show debugging messages\n"
		<< " - I to show info\n"
		<< "\n";
}

#pragma endregion ownDefinitions

#pragma region JonasSamynText
void FontLoader(char character, Point2f location, float width, float height, int color)
{
	TextCheckColor(color);

	switch (character)
	{
	case 'a':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0,	0,
						   0, color, color,	0,
						   0, 0, 0,	color,
						   0, color, color, color,
						   color, 0, 0,	color,
						   0, color, color,	color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'A':
	{
		int Letter[28] = { 0,	  color, color, 0,
						   color, 0, 0,			color,
						   color, 0, 0,			color,
						   color, 0, 0,			color,
						   color, color, color, color,
						   color, 0, 0,			color,
						   color, 0, 0,			color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'b':
	{
		int Letter[28] = { color, 0, 0, 0,
						   color, 0, 0,	0,
						   color, 0, 0,	0,
						   color, color, color, 0,
						   color, 0, 0,		color,
						   color, 0, 0,		color,
						   color, color, color, 0 };

		LetterDrawer(Letter, width, height, location);

	}
	break;
	case 'B':
	{
		int Letter[28] = { color, color, color, 0,
						   color, 0, 0,		color,
						   color, 0, 0,		color,
						   color, color, color, 0,
						   color, 0, 0,		color,
						   color, 0, 0,		color,
						   color, color, color, 0 };

		LetterDrawer(Letter, width, height, location);

	}
	break;
	case 'c':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0,	0,
						   0, color, color, 0,
						   color, 0, 0, color,
						   color, 0, 0, 0,
						   color, 0, 0,	color,
						   0, color, color, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'C':
	{
		int Letter[28] = { 0, color, color, 0,
						   color, 0, 0,		color,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, 0, 0,		color,
						   0, color, color, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'd':
	{
		int Letter[28] = { 0, 0, 0,		color,
						   0, 0, 0,		color,
						   0, 0, 0,		color,
						   0, color, color,	color,
						   color, 0, 0,	color,
						   color, 0, 0,	color,
						   0, color, color, color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'D':
	{
		int Letter[28] = { color, color, color, 0,
						   color, 0, 0,		color,
						   color, 0, 0,		color,
						   color, 0, 0,		color,
						   color, 0, 0,		color,
						   color, 0, 0,		color,
						   color, color, color, 0, };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'e':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, color, color, 0,
						   color, 0, 0, color,
						   color, color, color, color,
						   color, 0, 0, 0,
						   0, color, color, color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'E':
	{
		int Letter[28] = { color, color, color, color,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, color, color, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, color, color, color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'f':
	{
		int Letter[28] = { 0, color, color, 0,
						   color, 0, 0, color,
						   color, 0, 0, 0,
						   color, color, color, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0, };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'F':
	{
		int Letter[28] = { color, color, color, color,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, color, color, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0, };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'g':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0,	0,
						   0, color, color,	color,
						   color, 0, 0, color,
						   0, color, color, color,
						   0, 0, 0, color,
						   0, color, color, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'G':
	{
		int Letter[28] = { 0,	 color, color, 0,
						   color,0,		0,	   color,
						   color,0,		0,	   0,
						   color,0,		0,	   0,
						   color,0,		color, color,
						   color,0,		0,	   color,
						   0,	 color, color, 0, };
		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'h':
	{
		int Letter[28] = { color, 0,	 0,		0,
						   color, 0,	 0,		0,
						   color, 0,	 0,		0,
						   color, color, color, 0,
						   color, 0,	 0,		color,
						   color, 0,	 0,		color,
						   color, 0,	 0,		color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'H':
	{
		int Letter[28] = { color, 0,	 0,		color,
						   color, 0,	 0,		color,
						   color, 0,	 0,		color,
						   color, color, color, color,
						   color, 0,	 0,		color,
						   color, 0,	 0,		color,
						   color, 0,	 0,		color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'i':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, color, 0,
						   0, 0, 0, 0,
						   0, 0, color, 0,
						   0, 0, color, 0,
						   0, 0, color, 0,
						   0, 0, color, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'I':
	{
		int Letter[28] = { 0, color, color, color,
						   0,	  0, color, 0,
						   0,	  0, color, 0,
						   0,	  0, color, 0,
						   0,	  0, color, 0,
						   0,	  0, color, 0,
						   0, color, color, color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'j':
	{
		int Letter[28] = { 0,	  0,	 0,	color,
						   0,	  0,	 0,	0,
						   0,	  0,	 0,	color,
						   0,	  0,	 0,	color,
						   0, 0,	 0,		color,
						   0, color,	 0,	color,
						   0,	  0, color, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'J':
	{
		int Letter[28] = { 0,	  0,	 0,		color,
						   0,	  0,	 0,		color,
						   0,	  0,	 0,		color,
						   0,	  0,	 0,		color,
						   color, 0,	 0,		color,
						   color, 0,	 0,		color,
						   0,	  color, color, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'k':
	{
		int Letter[28] = { color, 0, 0, 0,
						   color, 0, 0,			color,
						   color, 0, 0,			color,
						   color, color, color, 0,
						   color, 0, 0,			color,
						   color, 0, 0,			color,
						   color, 0, 0,			color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'K':
	{
		int Letter[28] = { color, 0, 0, color,
						   color, 0, 0, color,
						   color, 0, color, 0,
						   color, color, 0, 0,
						   color, 0, color, 0,
						   color, 0, 0, color,
						   color, 0, 0, color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'l':
	{
		int Letter[28] = { color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   0, color, 0, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'L':
	{
		int Letter[28] = { color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, color, color, color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'm':
	{
		int Letter[28] = { 0, 0, 0,	0,
						   0, 0, 0, 0,
						   color, color, 0,	    color,
						   color, 0,	 color,	color,
						   color, 0,	 color,	color,
						   color, 0,	 color,	color,
						   color, 0,	 color,	color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'M':
	{
		int Letter[28] = { color, 0,	 0,		color,
						   color, color, color, color,
						   color, color, color,	color,
						   color, 0,	 0,		color,
						   color, 0,	 0,		color,
						   color, 0,	 0,		color,
						   color, 0,	 0,		color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'n':
	{
		int Letter[28] = { 0, 0, 0,	0,
						   0, 0, 0, 0,
						   color, color, color,  0,
						   color, 0, 0,			color,
						   color, 0, 0,			color,
						   color, 0, 0,			color,
						   color, 0, 0,			color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'N':
	{
		int Letter[28] = { color, 0,	0,		color,
						   color, color,0,		color,
						   color, 0,	color,  color,
						   color, 0,	0,		color,
						   color, 0,	0,		color,
						   color, 0,	0,		color,
						   color, 0,	0,		color, };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'o':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, color, color, 0,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   0, color, color, 0, };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'O':
	{
		int Letter[28] = { 0, color, color, 0,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   0, color, color, 0, };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'p':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0, 0,
						   color, color, color,	0,
						   color, 0, 0, color,
						   color, color, color, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0, };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'P':
	{
		int Letter[28] = { color, color, color, 0,
						   color, 0, 0,		color,
						   color, 0, 0,		color,
						   color, color, color, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0, };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'q':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, color, color, color,
						   color, 0, 0, color,
						   0, color, color, color,
						   0, 0, 0, color,
						   0, 0, 0, color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'Q':
	{
		int Letter[28] = { 0, color, color, 0,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   color, 0, color, 0,
						   0, color, 0, color, };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'r':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0,	0,
						   color, 0, color, color,
						   color, color, 0, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, 0, 0,	0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'R':
	{
		int Letter[28] = { color, color, color, 0,
						   color, 0, 0,			color,
						   color, 0, 0,			color,
						   color, color, color, 0,
						   color, 0, 0,		    color,
						   color, 0, 0,			color,
						   color, 0, 0,			color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 's':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0,	0,
						   0, color, color,	color,
						   color, 0, 0, 0,
						   0, color, color,	0,
						   0, 0, 0,	color,
						   color, color, color,	0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'S':
	{
		int Letter[28] = { 0, color, color, 0,
						   color, 0, 0, color,
						   color, 0, 0, 0,
						   0, color, color, 0,
						   0, 0, 0,		color,
						   color, 0, 0, color,
						   0, color, color, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 't':
	{
		int Letter[28] = { 0, color, 0, 0,
						   0, color, 0, 0,
						   color, color, color, color,
						   0, color, 0, 0,
						   0, color, 0, 0,
						   0, color, 0, color,
						   0, 0, color, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'T':
	{
		int Letter[28] = { 0, color, color, color,
						   0, 0, color, 0,
						   0, 0, color, 0,
						   0, 0, color, 0,
						   0, 0, color, 0,
						   0, 0, color, 0,
						   0, 0, color, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'u':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0, 0,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   0, color, color, color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'U':
	{
		int Letter[28] = { color, 0, 0, color,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   0, color, color, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'v':
	{
		int Letter[28] = { 0, 0, 0,	0,
						   0, 0, 0,	0,
						   color, 0, 0,	color,
						   color, 0, 0,			color,
						   color, 0, 0,			color,
						   color, color, color, color,
						   0,	  color, color,	0, };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'V':
	{
		int Letter[28] = { color, 0, 0,			color,
						   color, 0, 0,			color,
						   color, 0, 0,			color,
						   color, 0, 0,			color,
						   color, 0, 0,			color,
						   color, color, color, color,
						   0,	  color, color,	0, };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'w':
	{
		int Letter[28] = { 0, 0, 0,	0,
						   0, 0, 0,	0,
						   color, 0, 0,	color,
						   color, 0, 0,	        color,
						   color, 0,     color, color,
						   color, 0,	 color, color,
						   color, color, 0,		color, };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'W':
	{
		int Letter[28] = { color, 0, 0,			color,
						   color, 0, 0,			color,
						   color, 0, 0,			color,
						   color, 0, 0,			color,
						   color, 0, 0,			color,
						   color, color, color, color,
						   color, 0, 0,			color, };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'x':
	{
		int Letter[28] = { 0, 0, 0,	0,
						   0, 0, 0,	0,
						   color, 0, 0,	color,
						   color, 0, 0, color,
						   0, color, color,	0,
						   color, 0, 0,	color,
						   color, 0, 0,	color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'X':
	{
		int Letter[28] = { color, 0, 0,		color,
						   color, 0, 0,		color,
						   color, 0, 0,		color,
						   0,	color, color, 0,
						   color, 0, 0,		color,
						   color, 0, 0,		color,
						   color, 0, 0,		color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'y':
	{
		int Letter[28] = { 0, 0, 0,	0,
						   0, 0, 0,	0,
						   color, 0, 0,	color,
						   color, 0, 0, color,
						   0, color, color,	color,
						   0, 0, 0,	color,
						   0, color, color,	0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'Y':
	{
		int Letter[28] = { color, 0, 0,			color,
						   color, 0, 0,			color,
						   color, 0, 0,			color,
						   0,	  color, color, color,
						   0, 0, 0,				color,
						   color, 0, 0,			color,
						   0,	  color, color,	0, };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'z':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0,	0,
						   color, color, color,	color,
						   0, 0, 0, color,
						   0, color, color, 0,
						   color, 0, 0, 0,
						   color, color, color, color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case 'Z':
	{
		int Letter[28] = { color, color, color, color,
						   0, 0, 0,				color,
						   0, 0, 0,				color,
						   0,	  color, color, 0,
						   color, 0, 0, 0,
						   color, 0, 0, 0,
						   color, color, color, color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '0':
	{
		int Letter[28] = { 0, color, color, 0,
						   color, 0, 0, color,
						   color, 0, color, color,
						   color, color, 0, color,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   0, color, color, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '1':
	{
		int Letter[28] = { 0, 0,	 color, 0,
						   0, color, color, 0,
						   0, 0,	 color, 0,
						   0, 0,	 color, 0,
						   0, 0,	 color, 0,
						   0, 0,	 color, 0,
						   0, color, color, color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '2':
	{
		int Letter[28] = { 0,	  color,color, 0,
						   color, 0, 0,		color,
						   0, 0, 0,		color,
						   0, 0,	color, 0,
						   0,	color, 0, 0,
						   color, 0, 0, 0,
						   color, color, color, color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '3':
	{
		int Letter[28] = { 0, color, color, 0,
						   color, 0, 0, color,
						   0, 0, 0, color,
						   0, color, color, 0,
						   0, 0, 0, color,
						   color, 0, 0, color,
						   0, color, color, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '4':
	{
		int Letter[28] = { 0, 0,		color,	color,
						   0,	  color, 0,		color,
						   color, 0, 0,			color,
						   color, color, color, color,
						   0, 0, 0,				color,
						   0, 0, 0,				color,
						   0, 0, 0,				color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '5':
	{
		int Letter[28] = { color, color, color, color,
						   color, 0, 0, 0,
						   color, color, color, 0,
						   0, 0, 0,				color,
						   0, 0, 0,				color,
						   0, 0, 0,				color,
						   color, color, color, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '6':
	{
		int Letter[28] = { 0, 0,		 color, 0,
						   0,	  color, 0, 0,
						   color, 0, 0, 0,
						   color, color, color, 0,
						   color, 0, 0,			color,
						   color, 0, 0,			color,
						   0,	  color, color, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '7':
	{
		int Letter[28] = { color, color, color, color,
						   0, 0, 0,				color,
						   0, 0, 0,				color,
						   0, 0,		 color, 0,
						   0,	  color, 0, 0,
						   0,	  color, 0, 0,
						   0,	  color, 0, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '8':
	{
		int Letter[28] = { 0, color, color, 0,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   0, color, color, 0,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   0, color, color, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '9':
	{
		int Letter[28] = { 0, color, color, 0,
						   color, 0, 0, color,
						   color, 0, 0, color,
						   0, color, color, color,
						   0, 0, 0, color,
						   0, 0, color, 0,
						   0, color, 0, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '+':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, color, 0,
						   0, color, color, color,
						   0, 0, color, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '-':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, color, color, color,
						   0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '*':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, color, color, 0,
						   0, color, color, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '/':
	{
		int Letter[28] = { 0, 0, 0, color,
						   0, 0, 0, color,
						   0, 0, color, 0,
						   0, 0, color, 0,
						   0, 0, color, 0,
						   0, color, 0, 0,
						   0, color, 0, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '=':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, color, color, color,
						   0, 0, 0, 0,
						   0, color, color, color,
						   0, 0, 0, 0,
						   0, 0, 0, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '?':
	{
		int Letter[28] = { 0, color, color, 0,
						   color, 0, 0, color,
						   0, 0, 0, color,
						   0, 0, color, 0,
						   0, color, 0, 0,
						   0, 0, 0, 0,
						   0, color, 0, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '!':
	{
		int Letter[28] = { 0, color, 0, 0,
						   0, color, 0, 0,
						   0, color, 0, 0,
						   0, color, 0, 0,
						   0, color, 0, 0,
						   0, 0, 0, 0,
						   0, color, 0, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '.':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, color, 0, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case ',':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, color, 0,
						   0, color, 0, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	case ';':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, color, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, color, 0,
						   0, color, 0, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case ':':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, color, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, color, 0,
						   0, 0, 0, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '(':
	{
		int Letter[28] = { 0, 0, color, 0,
						   0, color, 0, 0,
						   0, color, 0, 0,
						   0, color, 0, 0,
						   0, color, 0, 0,
						   0, color, 0, 0,
						   0, 0, color, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case ')':
	{
		int Letter[28] = { 0, color, 0, 0,
						   0, 0, color, 0,
						   0, 0, color, 0,
						   0, 0, color, 0,
						   0, 0, color, 0,
						   0, 0, color, 0,
						   0, color, 0, 0 };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	case '_':
	{
		int Letter[28] = { 0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0,
						   color, color, color, color };

		LetterDrawer(Letter, width, height, location);
	}
	break;
	}
}
void FontLoader(char character, float x, float y, float width, float height, int color)
{
	const Point2f location{ x,y };
	FontLoader(character, location, width, height, color);
}

void LetterDrawer(int array[], float width, float height, Point2f location)
{
	float BlockWidth{ width };
	float BlockHeight{ height };

	int counter{};
	for (int y = 7; y > 0; y--)
	{
		for (int x = 0; x < 4; x++)
		{
			if (array[counter] != 0)
			{
				FillRect(location.x + BlockWidth * x, location.y + BlockHeight * y, BlockWidth, BlockHeight);
			}
			counter++;
		}
	}
}

void TextCheckColor(int color = 1)
{
	Color4f black(0 / 255.f, 0 / 255.f, 0 / 255.f, 1);
	Color4f red(255 / 255.f, 0 / 255.f, 0 / 255.f, 1);
	Color4f green(0 / 255.f, 255 / 255.f, 0 / 255.f, 1);
	Color4f blue(0 / 255.f, 0 / 255.f, 255 / 255.f, 1);

	switch (color)
	{
	case 1:
		SetColor(black);
		break;
	case 2:
		SetColor(red);
		break;
	case 3:
		SetColor(green);
		break;
	case 4:
		SetColor(blue);
		break;
	default:
		SetColor(black);
		break;
	}
}
#pragma endregion JonasSamynText