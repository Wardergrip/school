#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	Generate();
	PrintRandomNumbers();
}

void Draw()
{
	ClearBackground();

	// Put your own draw statements here
	DrawElevator(g_ElevatorPos, g_Direction);
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
#pragma region Timer
	g_Timer += elapsedSec;
	if (int(g_Timer) != int(g_PreviousTimer)) 
	{
		Generate();
		PrintRandomNumbers();
	}
	g_PreviousTimer = g_Timer;
#pragma endregion Timer
	g_ElapsedSec = elapsedSec;
	CalculateMovement();
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
	case SDLK_n:
		Generate();
		PrintRandomNumbers();
		break;
	}
}

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
	// std::cout << "  [" << e.x << ", " << e.y << "]\n";
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
	{
		// std::cout << "Left mouse button released\n";
		Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
		if (CheckInsideRect(g_ElevatorPos, g_ElevatorWallThickness, g_ElevatorTotalHeight, mousePos)) 
		{
			// std::cout << "Clicked\n";
			SwitchMovement();
		}
		else if (CheckInsideRect(g_ElevatorPos, g_ElevatorTotalWidth, g_ElevatorWallThickness, mousePos)) 
		{
			// std::cout << "Clicked\n";
			SwitchMovement();
		}
		else if (CheckInsideRect(g_ElevatorPos.x, g_ElevatorPos.y + g_ElevatorTotalHeight - g_ElevatorWallThickness, g_ElevatorTotalWidth, g_ElevatorWallThickness, mousePos)) 
		{
			// std::cout << "Clicked\n";
			SwitchMovement();
		}
		else if (CheckInsideRect(g_ElevatorPos.x + g_ElevatorTotalWidth - g_ElevatorWallThickness, g_ElevatorPos.y, g_ElevatorTotalWidth, g_ElevatorTotalHeight, mousePos)) 
		{
			// std::cout << "Clicked\n";
			SwitchMovement();
		}
		break;
	}
	case SDL_BUTTON_RIGHT:
		std::cout << "Right mouse button released\n";
		break;
	case SDL_BUTTON_MIDDLE:
		std::cout << "Middle mouse button released\n";
		break;
	}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here
void Generate() 
{
	const int previousEven{ g_Even };
	const int previousOdd{ g_Odd };
	const int previousAny{ g_Any };
	
	do 
	{
		g_Even = GenerateRandom(0, 9);
		// std::cout << "E: " << g_Even << std::endl; // Generate number 
		// std::cout << ((g_Even % 2 == 1)) << " " << (g_Even != previousEven) << std::endl; // Thruth table
	} while ((g_Even % 2 == 1) || (g_Even == previousEven));
	do 
	{
		g_Odd = GenerateRandom(0, 9);
		//std::cout << "O: " << g_Odd << std::endl;
	} while ((g_Odd % 2 == 0) || (g_Odd == previousOdd));
	do 
	{
		g_Any = GenerateRandom(0, 9);
		// std::cout << "A: " << g_Any << std::endl;
	} while (g_Any == previousAny);
	
}
void PrintRandomNumbers() 
{
	std::cout << "Even: " << g_Even << ", ";
	std::cout << "Odd: " << g_Odd << ", ";
	std::cout << "Any: " << g_Any << std::endl;
}
void DrawElevator(float x, float y, ElevatorDirection direction) 
{
	SetColor(51 / 255.0f, 51 / 255.0f, 229 / 255.0f, 1.0f); // Dark blue
	FillRect(x, y, g_ElevatorTotalWidth, g_ElevatorTotalHeight);
	switch (direction)
	{
	case ElevatorDirection::idle:
		SetColor(g_IdleColour);
		break;
	case ElevatorDirection::up:
		SetColor(g_UpColour);
		break;
	case ElevatorDirection::down:
		SetColor(g_DownColour);
		break;
	}
	FillRect(x + g_ElevatorWallThickness, y + g_ElevatorWallThickness, g_ElevatorTotalWidth - 2 * g_ElevatorWallThickness, g_ElevatorTotalHeight - 2 * g_ElevatorWallThickness);
}
void DrawElevator(Point2f xy, ElevatorDirection direction) 
{
	DrawElevator(xy.x, xy.y, direction);
}

void SwitchMovement() 
{
	if (g_Direction == ElevatorDirection::idle) 
	{
		g_Direction = g_PreviousDirection;
	}
	else 
	{
		g_PreviousDirection = g_Direction;
		g_Direction = ElevatorDirection::idle;
	}
}
void CalculateMovement() 
{
	if (g_Direction != ElevatorDirection::idle) 
	{
		if (g_ElevatorPos.y <= g_Border) 
		{
			g_Direction = ElevatorDirection::up;
		}
		else if (g_ElevatorPos.y >= g_WindowHeight - g_Border - g_ElevatorTotalHeight) 
		{
			g_Direction = ElevatorDirection::down;
		}
		switch (g_Direction)
		{
		case ElevatorDirection::idle:
			break;
		case ElevatorDirection::up:
			g_ElevatorPos.y += (g_Speed * g_ElapsedSec);
			break;
		case ElevatorDirection::down:
			g_ElevatorPos.y -= (g_Speed * g_ElapsedSec);
			break;
		default:
			break;
		}
	}
}
#pragma endregion ownDefinitions