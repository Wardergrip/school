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
	float rectSize{ 10 };
	ClearBackground();

	// Put your own draw statements here
	SetColor(1, 0, 0, 1);
	FillRect(g_MousePos.x - (rectSize /2), g_MousePos.y - (rectSize / 2), rectSize, rectSize);
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
	if (g_CurrentEvent != g_PreviousEvent) {
		switch (g_CurrentEvent)
		{
		case CurrentEvent::OnKeyUpEvent:
			std::cout << "OnKeyUpEvent\n";
			break;
		case CurrentEvent::OnKeyDownEvent:
			std::cout << "OnKeyDownEvent\n";
			break;
		case CurrentEvent::OnMouseMotionEvent:
			std::cout << "OnMouseMotionEvent\n";
			break;
		case CurrentEvent::OnMouseDownEvent:
			std::cout << "OnMouseDownEvent\n";
			break;
		case CurrentEvent::OnMouseUpEvent:
			std::cout << "OnMouseUpEvent\n";
			break;
		default:
			std::cout << "No event\n";
			break;
		}
	}
	g_PreviousEvent = g_CurrentEvent;
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
	g_CurrentEvent = CurrentEvent::OnKeyDownEvent;
	switch (key)
	{
	case SDLK_LEFT:
		std::cout << "	Left arrow key pressed\n";
		break;
	case SDLK_RIGHT:
		std::cout << "	Right arrow key pressed\n";
		break;
	case SDLK_1:
	case SDLK_KP_1:
		std::cout << "	Key 1 pressed\n";
		break;
	default:
		std::cout << "	" << char(key) << " pressed\n";
		break;
	}
}

void OnKeyUpEvent(SDL_Keycode key)
{
	g_CurrentEvent = CurrentEvent::OnKeyUpEvent;
	switch (key)
	{
	case SDLK_LEFT:
		std::cout << "	Left arrow key released\n";
		break;
	case SDLK_RIGHT:
		std::cout << "	Right arrow key released\n";
		break;
	case SDLK_1:
	case SDLK_KP_1:
		std::cout << "	Key 1 released\n";
		break;
	default:
		std::cout << "	" << char(key) << " released\n";
		break;
	}
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	g_CurrentEvent = CurrentEvent::OnMouseMotionEvent;
	std::cout << "  [" << e.x << ", " << e.y << "]\n";
	Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
	g_MousePos = mousePos;
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	g_CurrentEvent = CurrentEvent::OnMouseDownEvent;
}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	g_CurrentEvent = CurrentEvent::OnMouseUpEvent;
	std::cout << "  [" << e.x << ", " << e.y << "]\n";
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
	{
		std::cout << "Left mouse button released\n";
		Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
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

#pragma endregion ownDefinitions