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
	const Point2f p1{ 0,0 };
	const Point2f p2{ g_WindowWidth / 2, g_WindowHeight };
	const Point2f p3{ g_WindowWidth,0 };
	DrawSierpinskiTriangle(p1, p2, p3);
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
void DrawSierpinskiTriangle(const Point2f& left, const Point2f& top, const Point2f& right)
{
	const Point2f rg{ ((left.x + top.x) / 2.0f), ((left.y + top.y) / 2.0f) };
	const Point2f rb{ ((left.x + right.x) / 2.0f), left.y };
	const Point2f gb{ ((top.x + right.x) / 2.0f),rg.y };
	SetColor(1, 0, 0, 1);
	DrawTriangle(left, rg, rb); // red
	SetColor(0, 1, 0, 1);
	DrawTriangle(rg, top, gb); // green
	SetColor(0, 0, 1, 1);
	DrawTriangle(rb, gb, right); // blue
	if ((((right.x - left.x) / 2) > 10)) 
	{
		DrawSierpinskiTriangle(left, rg, rb); 
		DrawSierpinskiTriangle(rg, top, gb);
		DrawSierpinskiTriangle(rb, gb, right);
	}
}
#pragma endregion ownDefinitions