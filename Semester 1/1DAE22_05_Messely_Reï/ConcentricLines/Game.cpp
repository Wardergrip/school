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
	DrawLines();
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
	/*case SDLK_LEFT:
		std::cout << "Left arrow key released\n";
		break;*/
	case SDLK_RIGHT:
		std::cout << "Right arrow key released\n";
		SwitchColor();
		break;
	/*case SDLK_1:
	case SDLK_KP_1:
		std::cout << "Key 1 released\n";
		break;*/
	}
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	std::cout << "  [" << e.x << ", " << e.y << "]\n";
	Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
	g_MousePos = mousePos;
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
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here
void DrawLines() 
{
	const float step{ 9.0f };
	switch (g_Color)
	{
	case Color::red:
		SetColor(1, 0, 0, 1);
		break;
	case Color::green:
		SetColor(0, 1, 0, 1);
		break;
	case Color::blue:
		SetColor(0, 0, 1, 1);
		break;
	}

	for (float i{ 0 }; i <= g_WindowWidth; i += step) // Draw lines from bottom
	{
		DrawLine(i, 0, g_MousePos.x, g_MousePos.y);
	}
	for (float i{ 0 }; i <= g_WindowHeight; i += step) // Draw lines from left
	{
		DrawLine(0, i, g_MousePos.x, g_MousePos.y);
	}
	for (float i{ 0 }; i <= g_WindowWidth; i += step) // Draw lines from top
	{
		DrawLine(i, g_WindowHeight, g_MousePos.x, g_MousePos.y);
	}
	for (float i{ 0 }; i <= g_WindowHeight; i += step) // Draw lines from right
	{
		DrawLine(g_WindowWidth, i, g_MousePos.x, g_MousePos.y);
	}
}
void SwitchColor() 
{
	switch (g_Color)
	{
	case Color::red:
		g_Color = Color::green;
		break;
	case Color::green:
		g_Color = Color::blue;
		break;
	case Color::blue:
		g_Color = Color::red;
		break;
	}
}
#pragma endregion ownDefinitions