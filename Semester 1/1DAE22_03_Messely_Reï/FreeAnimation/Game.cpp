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
	DrawCircle1();
	DrawCircle2();
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

	g_CircleRadius1 = float(int(g_CircleRadius1 + 1) % int(g_WindowHeight / 2));
	g_CircleRadius2 = g_WindowHeight / 2 - g_CircleRadius1;
	g_TransparentnessCalculation = (float((int(g_TransparentnessCalculation + 1)) % 2001));
	g_Transparentness = g_TransparentnessCalculation / 2000.0f;
	std::cout << g_TransparentnessCalculation << std::endl;
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
void DrawCircle1()
{
	SetColor(0.0f, 0.0f, 0.0f, 1.0f);
	DrawArc(g_CenterPoint, g_CircleRadius1, g_CircleRadius1, 0, 2 * g_Pi);
	SetColor(1.0f, 0.0f, 0.0f, g_Transparentness);
	FillArc(g_CenterPoint, g_CircleRadius1, g_CircleRadius1, 0, 2 * g_Pi);
}
void DrawCircle2()
{
	SetColor(0.0f, 0.0f, 0.0f, 1.0f);
	DrawArc(g_CenterPoint, g_CircleRadius2, g_CircleRadius2, 0, 2 * g_Pi);
	SetColor(1.0f, 1.0f, 0.0f, g_Transparentness);
	FillArc(g_CenterPoint, g_CircleRadius2, g_CircleRadius2, 0, 2 * g_Pi);
}
#pragma endregion ownDefinitions