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
	ClearBackground();
	SetColor(g_BackgroundColor);
	FillRect(0, 0, g_WindowWidth, g_WindowHeight);
	// Put your own draw statements here
	DrawLineHorizontalOne();
	DrawLineHorizontalTwo();
	DrawLineVerticalOne();
	DrawLineVerticalTwo();
	DrawYellowBox();
}

void Update(float elapsedSec)
{
#pragma region Misc



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
#pragma endregion
	g_GlobalPos = float(int(++g_GlobalPos) % int(g_WindowHeight));
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
void DrawLineHorizontalOne() 
{
	SetColor(g_White);
	DrawLine(0, g_GlobalPos, g_WindowWidth, g_GlobalPos);
}
void DrawLineHorizontalTwo()
{
	SetColor(g_White);
	DrawLine(0, g_WindowHeight - g_GlobalPos, g_WindowWidth, g_WindowHeight - g_GlobalPos);
}
void DrawLineVerticalOne()
{
	SetColor(g_White);
	DrawLine(g_GlobalPos, 0, g_GlobalPos, g_WindowHeight);
}
void DrawLineVerticalTwo()
{
	SetColor(g_White);
	DrawLine(g_WindowWidth - g_GlobalPos, 0, g_WindowWidth - g_GlobalPos, g_WindowHeight);
}
void DrawYellowBox()
{
	SetColor(g_Yellow);
	DrawLine(g_GlobalPos, 0, g_WindowWidth, g_GlobalPos);
	DrawLine(g_WindowWidth, g_GlobalPos, g_WindowWidth - g_GlobalPos, g_WindowHeight);
	DrawLine(g_WindowWidth - g_GlobalPos, g_WindowHeight, 0, g_WindowHeight - g_GlobalPos);
	DrawLine(0, g_WindowHeight - g_GlobalPos, g_GlobalPos, 0);
}
#pragma endregion ownDefinitions