// Reï Messely 1DAE22
#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	PrintLetters();
	std::cout << "\n\n";
}

void Draw()
{
	ClearBackground();

	// Put your own draw statements here
	SetColor(g_CurrentColor);
	FillEllipse(g_CirclePos, g_CurrentRadius, g_CurrentRadius);

}

void Update(float elapsedSec)
{
	// process input, do physics 
	switch (g_CircleState)
	{
	case CircleState::growing:
		g_CurrentColor = g_NewColor;
		if (IsHittingBorder())
		{
			std::cout << "Ouch!\n";
			g_CurrentColor = g_ErrorColor;
			g_CircleState = CircleState::shrinking;
			std::cout << "Shrinking state.\n";
		}
		else if (g_CurrentRadius <= g_NewRadius) 
		{
			g_CurrentRadius += float(g_Speed);
		}
		else 
		{
			g_CircleState = CircleState::shrinking;
			std::cout << "Shrinking state.\n";
		}
		break;
	case CircleState::shrinking:
		if (g_CurrentRadius > 0) 
		{
			g_CurrentRadius -= float(g_Speed);
			if (g_CurrentRadius < 0) // Making sure the radius will not become 0
			{
				g_CurrentRadius = 0;
			}
		}
		else 
		{
			g_CircleState = CircleState::waiting;
			std::cout << "Waiting state.\n\n";
		}
		break;
	case CircleState::waiting:
		break;
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
	case SDLK_UP:
		if (g_Speed < 5) 
		{
			g_Speed += g_Step;
		}
		std::cout << "g_Speed = " << g_Speed << std::endl;
		break;
	case SDLK_DOWN:
		if (g_Speed > 0.2) 
		{
			g_Speed -= g_Step;
		}
		std::cout << "g_Speed = " << g_Speed << std::endl;
		break;
	}
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{

}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{

}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
		if (g_CircleState == CircleState::waiting) 
		{
			g_CircleState = CircleState::growing;
			// Do while to prevent having the same radius or color back to back, as requested
			do {
				g_NewRadius = float(GenerateRandom(g_MinRadius, g_MaxRadius));
			} while (g_NewRadius == g_PreviousRadius);
			g_PreviousRadius = g_NewRadius;
			do {
				g_NewColor = RandomColor();
			} while ((g_NewColor.r == g_PreviousColor.r) && (g_NewColor.g == g_PreviousColor.g) && (g_NewColor.b == g_PreviousColor.b));
			g_PreviousColor = g_NewColor;
			g_CirclePos = mousePos;
			std::cout << "Growing state.\n";
			std::cout << "Radius is " << g_NewRadius << std::endl;
		}
		else 
		{
			g_NewPos = mousePos; // Remembering new position as requested in the assignment
		}
		break;
	}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here
void PrintLetters() 
{
	int input{};
	int amount{};
	std::cout << "How many charachters per line?";
	std::cin >> input;
	std::cout << std::endl;
	for (int i{97}; i < 123; i++ ) 
	{
		std::cout << char(i);
		++amount;
		if (amount % input == 0) 
		{
			std::cout << std::endl;
		}
	}
}
bool IsHittingBorder() 
{
	if ((g_CirclePos.y + g_CurrentRadius >= g_WindowHeight) || (g_CirclePos.x + g_CurrentRadius >= g_WindowWidth)) 
	{
		return true;
	}
	else if ((g_CirclePos.y - g_CurrentRadius <= 0) || (g_CirclePos.x - g_CurrentRadius <= 0)) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}
#pragma endregion ownDefinitions