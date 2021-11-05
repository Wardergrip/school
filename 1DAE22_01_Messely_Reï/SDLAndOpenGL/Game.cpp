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

	// Put your own draw statements here
	// Draw border
	SetColor(39 / 255.0f, 104 / 255.0f, 39 / 255.0f);
	DrawRect(0, 0, g_WindowWidth, g_WindowHeight, 2.0f);
	// Draw red lines
	SetColor(248 / 255.0f, 145 / 255.0f, 147 / 255.0f);
	DrawLine(0, g_WindowHeight, g_WindowWidth, 0);
	DrawLine(0, 0, g_WindowWidth, g_WindowHeight);
	// Draw blue square
	SetColor(20 / 255.0f, 20 / 255.0f, 240 / 255.0f);
	float sideLength{ 4.0f };
	FillRect(g_WindowWidth / 2 - sideLength / 2, g_WindowHeight / 2 - sideLength / 2, sideLength, sideLength);
	// Draw white lines
	SetColor(1.0f, 1.0f, 1.0f);
		// Verticals
	DrawLine(g_WindowWidth / 3, 0, g_WindowWidth / 3, g_WindowHeight);
	DrawLine(2 * g_WindowWidth / 3, 0, 2 * g_WindowWidth / 3, g_WindowHeight);
		// Horizontals
	DrawLine(0, g_WindowHeight / 3, g_WindowWidth, g_WindowHeight / 3);
	DrawLine(0, 2 * g_WindowHeight / 3, g_WindowWidth, 2 * g_WindowHeight / 3);
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

#pragma endregion ownDefinitions