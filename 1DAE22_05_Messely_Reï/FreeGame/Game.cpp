#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here

}

void Draw()
{
	ClearBackground(0,0,0);

	// Put your own draw statements here
	SetColor(g_White);
	DrawDottedLine();
	DrawFirstPaddle();
	DrawSecondPaddle();
	DrawBall();
	SetColor(g_White);
	DrawNumber(g_WindowWidth / 2 - 100, g_WindowHeight / 2 + 40, g_ScoreP1);
	DrawNumber(g_WindowWidth / 2 + 60, g_WindowHeight / 2 + 40, g_ScoreP2);
}

void Update(float elapsedSec)
{
	// process input, do physics 

	// e.g. Check keyboard state
	/*const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if ( pStates[SDLK_w] )
	{
		std::cout << "Right arrow key is down\n";
		MoveFirstPaddle(g_PaddleSpeed);
	}
	if ( pStates[SDLK_s] && pStates[SDL_SCANCODE_UP])
	{
		std::cout << "Left and up arrow keys are down\n";
		MoveFirstPaddle(-g_PaddleSpeed);
	}*/
	
	CalculateBall();
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
	const bool onKeyUpEventConsoleInput{ g_ViewDebugging };
	switch (key)
	{
	case SDLK_w:
		if (onKeyUpEventConsoleInput == true)
		{
			std::cout << "w key pressed\n";
		}
		MoveFirstPaddle(g_PaddleSpeed);
		break;
	case SDLK_s:
		if (onKeyUpEventConsoleInput == true)
		{
			std::cout << "s key pressed\n";
		}
		MoveFirstPaddle(-g_PaddleSpeed);
		break;
	case SDLK_UP:
		if (onKeyUpEventConsoleInput == true)
		{
			std::cout << "Up arrow key pressed\n";
		}
		MoveSecondPaddle(g_PaddleSpeed);
		break;
	case SDLK_DOWN:
		if (onKeyUpEventConsoleInput == true)
		{
			std::cout << "Down arrow key pressed\n";
		}
		MoveSecondPaddle(-g_PaddleSpeed);
		break;
	case SDLK_a:
		if (onKeyUpEventConsoleInput == true)
		{
			std::cout << "a key pressed\n";
		}
		ResetScore();
		break;
	case SDLK_i:
		ShowInfo();
		break;
	case SDLK_p:
		if (g_GamePaused == false) 
		{
			g_GamePaused = true;
			std::cout << "GAME IS PAUSED\n";
		}
		else 
		{
			g_GamePaused = false;
			std::cout << "GAME IS UNPAUSED\n";
		}
		break;
	case SDLK_g:
		if (g_EnableSpeedIncrease == true) 
		{
			g_EnableSpeedIncrease = false;
			std::cout << "DISABLED SPEED INCREASE\n";
		}
		else 
		{
			g_EnableSpeedIncrease = true;
			std::cout << "ENABLED SPEED INCREASE\n";
		}
		break;
	case SDLK_d:
		if (g_ViewDebugging == true)
		{
			g_ViewDebugging = false;
			std::cout << "DISABLED DEBUGGING\n";
		}
		else
		{
			g_ViewDebugging = true;
			std::cout << "ENABLED DEBUGGING\n";
		}
		break;
	}
}
#pragma region MouseEventHandling
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{

}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	////std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//switch (e.button)
	//{
	//case SDL_BUTTON_LEFT:
	//{
	//	//std::cout << "Left mouse button released\n";
	//	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
	//	break;
	//}
	//case SDL_BUTTON_RIGHT:
	//	//std::cout << "Right mouse button released\n";
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	//std::cout << "Middle mouse button released\n";
	//	break;
	//}
}
#pragma endregion MouseEventHandling
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here
void DrawFirstPaddle()
{
	FillRect(g_FirstPaddleBL.x, g_FirstPaddleBL.y + g_FirstPaddleTranslation, g_PaddleWidth, g_PaddleHeight);
}
void DrawSecondPaddle()
{
	FillRect(g_SecondPaddleBL.x, g_SecondPaddleBL.y + g_SecondPaddleTranslation, g_PaddleWidth, g_PaddleHeight);
}
void MoveFirstPaddle(float direction)
{
	if ((direction > 0) && (g_FirstPaddleTranslation < ((g_WindowHeight / 2)-g_PaddleHeight /2) )) 
	{
		g_FirstPaddleTranslation += direction;
	}
	else if ((direction < 0) && (g_FirstPaddleTranslation > (-g_WindowHeight / 2)+g_PaddleHeight / 2))
	{
		g_FirstPaddleTranslation += direction;
	}
}
void MoveSecondPaddle(float direction)
{
	if ((direction > 0) && (g_SecondPaddleTranslation < ((g_WindowHeight / 2) - g_PaddleHeight / 2)))
	{
		g_SecondPaddleTranslation += direction;
	}
	else if ((direction < 0) && (g_SecondPaddleTranslation > (-g_WindowHeight / 2) + g_PaddleHeight / 2))
	{
		g_SecondPaddleTranslation += direction;
	}
}
void DrawDottedLine() 
{
	const float amountOfDots{ 10 };
	const float lengthDot{ g_WindowHeight / ( 2 * amountOfDots) };
	for (float i{}; i <= (2 * amountOfDots); i += 2)
	{
		DrawLine(g_WindowWidth / 2, 0+i*lengthDot, g_WindowWidth / 2, (i+1)* lengthDot);
		
	}
}
void DrawBall() 
{
	SetColor(SwitchBallColour(g_BallSpeed));
	FillEllipse(g_BallCenterpoint.x + g_BallTranslation.x, g_BallCenterpoint.y + g_BallTranslation.y, g_BallRad, g_BallRad);
}
void CalculateBall() 
{
	const bool CalculateBallDebugging{ g_ViewDebugging };
	if (((g_BallCenterpoint.x + g_BallTranslation.x) >= g_SecondPaddleBL.x) && ((g_BallCenterpoint.y + g_BallTranslation.y >= g_SecondPaddleBL.y + g_SecondPaddleTranslation ) && (g_BallCenterpoint.y + g_BallTranslation.y <= g_SecondPaddleBL.y + g_SecondPaddleTranslation + g_PaddleHeight)))
	{
		if (g_BallCenterpoint.x + g_BallTranslation.x <= g_SecondPaddleBL.x + 2 ) {
			if (g_BallCenterpoint.y + g_BallTranslation.y <= (g_SecondPaddleBL.y + g_SecondPaddleTranslation) / 2) 
			{
				if (g_ViewDebugging == true)
				{
					std::cout << "Hit top part of right paddle\n";
				}
			}
			else 
			{
				if (g_ViewDebugging == true) 
				{
					std::cout << "Hit bottom part of right paddle\n";
				}
			}
			g_BallXDirection = -1;
			g_BallSpeed += g_BallSpeedIncrease * g_EnableSpeedIncrease;
			if (CalculateBallDebugging == true)
			{
			std::cout << "Hitting the side of right paddle!\n";
			}
		}
		else if (g_BallCenterpoint.y + g_BallTranslation.y <= g_SecondPaddleBL.y + g_SecondPaddleTranslation)
		{
			g_BallYDirection = -1;
			if (CalculateBallDebugging == true)
			{
				std::cout << "Hitting bottom side of right paddle!\n";
			}
		}
		else if ( g_BallCenterpoint.y + g_BallTranslation.y >= g_SecondPaddleBL.y + g_PaddleHeight + g_SecondPaddleTranslation)
		{
			g_BallYDirection = 1;
			if (CalculateBallDebugging == true) 
			{
				std::cout << "Hitting top side of right paddle!\n";
			}
		}
	}
	else if (g_BallTranslation.x >= g_WindowWidth / 2 )
	{
		g_BallXDirection = -1;
		++g_ScoreP1;
		g_BallSpeed = 1;
		g_BallTranslation.x = 0; g_BallTranslation.y = 0;
		if (CalculateBallDebugging == true)
		{
			std::cout << "Scored right\n" << "[P1] SCORE: " << g_ScoreP1 << std::endl;
		}
	}
	else if (((g_BallCenterpoint.x + g_BallTranslation.x) <= (g_FirstPaddleBL.x + g_PaddleWidth)) && ((g_BallCenterpoint.y + g_BallTranslation.y >= g_FirstPaddleBL.y + g_FirstPaddleTranslation) && (g_BallCenterpoint.y + g_BallTranslation.y <= g_FirstPaddleBL.y + g_FirstPaddleTranslation + g_PaddleHeight)))
	{
		if (g_BallCenterpoint.x + g_BallTranslation.x <= g_FirstPaddleBL.x + g_PaddleWidth -2) {
			g_BallXDirection = 1;
			g_BallSpeed += g_BallSpeedIncrease * g_EnableSpeedIncrease;
			if (CalculateBallDebugging == true)
			{
				std::cout << "Hitting the side of left paddle!\n";
			}
		}
		else if (g_BallCenterpoint.y + g_BallTranslation.y <= g_FirstPaddleBL.y + g_FirstPaddleTranslation)
		{
			g_BallYDirection = -1;
			if (CalculateBallDebugging == true)
			{
				std::cout << "Hitting bottom side of right paddle!\n";
			}
		}
		else if (g_BallCenterpoint.y + g_BallTranslation.y >= g_FirstPaddleBL.y + g_PaddleHeight + g_FirstPaddleTranslation)
		{
			g_BallYDirection = 1;
			if (CalculateBallDebugging == true)
			{
				std::cout << "Hitting top side of right paddle!\n";
			}
		}
	}
	else if (g_BallTranslation.x <= -g_WindowWidth / 2) 
	{
		g_BallXDirection = 1;
		++g_ScoreP2;
		g_BallSpeed = 1;
		g_BallTranslation.x = 0; g_BallTranslation.y = 0;
		if (CalculateBallDebugging == true)
		{
			std::cout << "Scored left\n" << "[P2] SCORE: " << g_ScoreP2 << std::endl;
		}
	}
	if (g_BallTranslation.y >= g_WindowHeight / 2) 
	{
		g_BallYDirection = -1;
		if (CalculateBallDebugging == true)
		{
			std::cout << "hit top\n";
		}
	}
	else if (g_BallTranslation.y <= -g_WindowHeight / 2)
	{
		g_BallYDirection = 1;
		if (CalculateBallDebugging == true)
		{
			std::cout << "hit bottom\n";
		}
	}
	if (g_GamePaused == false) 
	{
		g_BallTranslation.x += g_BallXDirection*g_BallSpeed;
		g_BallTranslation.y += g_BallYDirection*g_BallSpeed;
	}
}
void ShowInfo() 
{
	std::cout << "\n" // Create some space so it stands out more
			  <<"===== INFO =====\n"
			  << " Player 1:\n" 
			  << " W = Up\n"
		      << " S = Down\n\n"
			  << " Player 2:\n"
			  << " Up arrow = Up\n"
			  << " Down arrow = Down\n\n" 
			  << " Misc:\n" 
			  << " A = Reset score and place ball in the middle\n"
			  << " Note: Max score is 9\n"
			  << " P = Freezes the ball and pauses the game\n" 
			  << " G = Enables/Disables Speed increase (Increases speed everytime the ball hits a paddle)\n"
			  << " Note: The ball changes colour depending on the speed of the ball\n"
			  << " D = Enables/Disables Debugging\n"
			  <<"\n"; // Create some space so its stands out more
}
void ResetScore()
{
	g_ScoreP1 = 0;
	g_ScoreP2 = 0;
	g_BallTranslation.x = 0; g_BallTranslation.y = 0;
	std::cout << "SCORE HAS BEEN RESET\n";
}

void DrawNumber(float x, float y, int number) 
{
	const float maxW{40}, maxH{80};
	switch (number)
	{
	case 0:
		FillRect(x, y, maxW, maxH / 4); // Bottom
		FillRect(x, y, maxW / 4, maxH);  // Left
		FillRect(x + (3 * maxW) / 4, y, maxW / 4, maxH); // Right
		FillRect(x, y + (3 * maxH) / 4, maxW, maxH / 4); // Top
		break;
	case 1:
		FillRect(x + (3 * maxW) / 4, y, maxW / 4, maxH); // Right
		break;
	case 2:
		FillRect(x, y, maxW, maxH / 4);  // Bottom
		FillRect(x, y + (3 * maxH) / 4, maxW, maxH / 4); // Top
		FillRect(x + (3*maxW) / 4, y + (maxH / 2), maxW / 4, maxH / 4); //Short right up
		FillRect(x, y + (maxH / 4), maxW / 4, maxH / 4); // short left down
		FillRect(x, y + (maxH / 4) + (maxH / 8), maxW, maxH / 4); // Mid bit
		break;
	case 3:
		FillRect(x, y, maxW, maxH / 4); // Bottom
		FillRect(x, y + (3 * maxH) / 4, maxW, maxH / 4); // Top
		FillRect(x, y + (maxH / 2) - maxH / 8, maxW, maxH / 4); // Mid bit
		FillRect(x + (3 * maxW) / 4, y, maxW / 4, maxH); // Right
		break;
	case 4:
		FillRect(x + (3 * maxW) / 4, y, maxW / 4, maxH); // Right
		FillRect(x, y + (maxH / 2) - maxH / 8, maxW, maxH / 4);  // Mid bit
		FillRect(x, y + (maxH / 2), maxW / 4, maxH / 2); // Short left up
		break;
	case 5:
		FillRect(x, y, maxW, maxH / 4); // Bottom
		FillRect(x, y + (3 * maxH) / 4, maxW, maxH / 4); // Top
		FillRect(x, y + (maxH / 2), maxW / 4, maxH / 4); //Short left up
		FillRect(x + (3 * maxW) / 4, y + (maxH / 4), maxW / 4, maxH / 4); // short right down
		FillRect(x, y + (maxH / 2) - maxH / 8, maxW, maxH / 4);  // Mid bit
		break;
	case 6:
		FillRect(x, y, maxW, maxH / 4); // Bottom
		FillRect(x, y + (3 * maxH) / 4, maxW, maxH / 4); // Top
		FillRect(x, y + (maxH / 2) - maxH / 8, maxW, maxH / 4);  // Mid bit
		FillRect(x + (3 * maxW) / 4, y + (maxH / 4), maxW / 4, maxH / 4); // short right down
		FillRect(x, y + (maxH / 4), maxW / 4, maxH / 4); // short left down
		FillRect(x, y, maxW / 4, maxH);  // Left
		break;
	case 7:
		FillRect(x + (3 * maxW) / 4, y, maxW / 4, maxH); // Right
		FillRect(x, y + (3 * maxH) / 4, maxW, maxH / 4); // Top
		break;
	case 8:
		FillRect(x, y, maxW, maxH / 4); // Bottom
		FillRect(x, y + (3 * maxH) / 4, maxW, maxH / 4); // Top
		FillRect(x, y + (maxH / 2) - maxH / 8, maxW, maxH / 4);  // Mid bit
		FillRect(x + (3 * maxW) / 4, y + (maxH / 4), maxW / 4, maxH / 4); // short right down
		FillRect(x, y + (maxH / 4), maxW / 4, maxH / 4); // short left down
		FillRect(x, y, maxW / 4, maxH);  // Left
		FillRect(x + (3 * maxW) / 4, y, maxW / 4, maxH); // Right
		break;
	default:
	case 9:
		FillRect(x, y, maxW, maxH / 4); // Bottom
		FillRect(x, y + (3 * maxH) / 4, maxW, maxH / 4); // Top
		FillRect(x + (3 * maxW) / 4, y, maxW / 4, maxH); // Right
		FillRect(x, y + maxH / 2, maxW / 4, maxH / 4); // Short left up
		FillRect(x, y + (maxH / 2) - maxH / 8, maxW, maxH / 4);  // Mid bit
		break;
	}
}
void DrawNumber(Point2f xy, int number) 
{
	DrawNumber(xy.x, xy.y, number);
}
Color4f SwitchBallColour(float speed) 
{
	if (g_EnableSpeedIncrease == true) {
		int value{ int((speed - 1) * 10) };
		switch (value)
		{
		case 0:
			return g_White;
			break;
		case 1:
			return g_LightYellow;
			break;
		case 2:
			return g_Yellow;
			break;
		case 3:
			return g_LightOrange;
			break;
		case 4:
			return g_Orange;
			break;
		case 5:
			return g_Orange;
			break;
		case 6:
			return g_DarkOrange;
			break;
		case 7:
			return g_LightRed;
			break;
		case 8:
			return g_Red;
			break;
		case 9:
			return g_DarkRed;
			break;
		case 10:
			return g_Purple;
			break;
		default:
			return g_Purple;
			break;
		}
	}
	return g_White;
}
#pragma endregion ownDefinitions