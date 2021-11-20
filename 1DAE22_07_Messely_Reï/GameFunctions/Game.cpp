#include "pch.h"
#include "Game.h"

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
	SetColor(1, 1, 1, 1);
	FillEllipse(g_RandomCircle.center, g_Radius, g_Radius);
	FillRect(g_RandomRect);
	SetColor(1, 0, 0, 1);
	if (IsPointInCircle(g_RandomCircle.center, g_Radius, g_MousePos)) DrawEllipse(g_RandomCircle.center, g_Radius, g_Radius,3);
	if (IsInsideRect(g_RandomRect, g_MousePos)) DrawRect(g_RandomRect, 3);
	if (IsOverlapping(g_RandomRect, g_MouseRect)) SetColor(1, 0, 0, 0.5f);
	else SetColor(0, 1, 0, 0.5f);
	FillRect(g_MouseRect);
	if (IsOverlapping(g_RandomCircle, g_MouseCircle)) SetColor(1, 0, 0, 0.5f);
	else SetColor(0, 1, 0, 0.5f);
	FillEllipse(g_MouseCircle.center, g_MouseCircle.radius,g_MouseCircle.radius);
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

	g_MouseRect.left = g_MousePos.x;
	g_MouseRect.bottom = g_MousePos.y;
	g_MouseCircle.center = g_MousePos;
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
	g_MousePos.x = float(e.x);
	g_MousePos.y = float(g_WindowHeight - e.y);
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

#pragma endregion ownDefinitions