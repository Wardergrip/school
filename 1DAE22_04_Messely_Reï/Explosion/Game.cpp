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
	ClearBackground();

	// Put your own draw statements here
	DrawExplosion();
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
	UpdateExplosion();
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
	//switch (key)
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
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
	std::cout << "  [" << e.x << ", " << e.y << "]\n";
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
	{
		std::cout << "Left mouse button released\n";
		Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
		g_MousePos = mousePos;
		ProcessMouseClick();
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
void ProcessMouseClick() 
{
	if (((g_MousePos.x >= g_BombPoint.x) && (g_MousePos.x <= g_BombPoint.x + g_BombSize) && (g_MousePos.y >= g_BombPoint.y) && (g_MousePos.y <= g_BombPoint.y + g_BombSize)) && g_IsExploding == false)
	{
		g_IsExploding = true;
		g_MousePos.x = -1; g_MousePos.y = -1; // Move mousepos to impossible range to prevent feedbackloop
	}
	else 
	{
		g_MousePos.x = -1; g_MousePos.y = -1; // Move mousepos to impossible range to prevent that clicking the exploded bomb makes a new explosion
	}
}
void DrawExplosion() 
{
	if (g_IsExploding == false)
	{
		SetColor(g_Black);
		FillRect(g_BombPoint, g_BombSize, g_BombSize);
	}
	else
	{
		SetColor(g_ExplodedBombColour);
		FillRect(g_BombPoint, g_BombSize, g_BombSize);
	}
	if (g_IsExploding == true) 
	{
		SetColor(g_Red);
		FillRect(g_ExplosionPoint.x + g_Drift, g_ExplosionPoint.y + g_Drift, g_ExplosionSize, g_ExplosionSize);
		FillRect(g_ExplosionPoint.x - g_Drift, g_ExplosionPoint.y + g_Drift, g_ExplosionSize, g_ExplosionSize);
		FillRect(g_ExplosionPoint.x + g_Drift, g_ExplosionPoint.y - g_Drift, g_ExplosionSize, g_ExplosionSize);
		FillRect(g_ExplosionPoint.x - g_Drift, g_ExplosionPoint.y - g_Drift, g_ExplosionSize, g_ExplosionSize);
	}
}
void UpdateExplosion()
{
	if (g_IsExploding == true)
	{
		if (((g_Drift >= ((g_WindowWidth / 2) + g_ExplosionSize / 2))) || (g_Drift >= ((g_WindowHeight / 2) + g_ExplosionSize / 2)))
		{
			std::cout << "Resetting...\n";
			g_IsExploding = false;
			g_Drift = 0;
		}
		else 
		{
			++g_Drift;
		}
	}
}
#pragma endregion ownDefinitions