#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	// 
	// Dot Product test
	if (true)
	{
		const Vector2f example1{80,0};
		const Vector2f example2{ 0,50 };
		const Vector2f example3{ 0,25 };
		std::cout << "E1: " << ToString(example1) << " E2: " << ToString(example2) << " DotProduct: " << DotProduct(example1, example2) << std::endl;
		std::cout << "E1: " << ToString(example2) << " E2: " << ToString(example3) << " DotProduct: " << DotProduct(example2, example3) << std::endl;
	}
	// Cross Product test
	if (true)
	{
		const Vector2f example1{ 80,0 };
		const Vector2f example2{ 0,50 };
		const Vector2f example3{ 0,25 };
		std::cout << "E1: " << ToString(example1) << " E2: " << ToString(example2) << " CrossProduct: " << CrossProduct(example1, example2) << std::endl;
		std::cout << "E1: " << ToString(example2) << " E2: " << ToString(example1) << " CrossProduct: " << CrossProduct(example2, example1) << std::endl;
	}
	// Angle Between test
	if (true) 
	{
		const Vector2f example1{ 10,0 };
		const Vector2f example2{ 0,10 };
		std::cout << "E1: " << ToString(example1) << " E2: " << ToString(example2) << " AngleBetween: " << AngleBetween(example1, example2) <<  "rad" << " or " << AngleBetween(example1, example2) * (180.0f / g_Pi) << "deg" << std::endl;
	}
}

void Draw()
{
	ClearBackground(0,0,0);

	// Put your own draw statements here
	SetColor(1, 1, 0, 1);
	//DrawVector(g_VectorA, g_StartingPointA);
	//Vector2f mouseVector{ g_CurrentMousePos.x - g_MiddleOfScreen.x, g_CurrentMousePos.y - g_MiddleOfScreen.y};
	//DrawVector(mouseVector, g_MiddleOfScreen);
	//DrawVector(mouseVector);
	// 
	// Add
	// 
	SetColor(1, 1, 0, 1);
	DrawVector(g_VectorA);
	DrawVector(g_VectorB, VectorToPoint(g_VectorA));
	DrawVector(Add(g_VectorA, g_VectorB));
	//
	// Substract
	//
	SetColor(0, 1, 1, 1);
	DrawVector(g_VectorB);
	DrawVector(Substract(g_VectorA, g_VectorB), VectorToPoint(g_VectorB));
	// 
	// Scalar projection 
	//
	SetColor(1, 0, 1, 1);
	DrawVector(g_VectorC, g_MiddleOfScreen); // Rotating vector
	SetColor(1, 1, 1, 1);
	//DrawVector(Normalize(g_VectorA), g_MiddleOfScreen); // Normalized Vector
	SetColor(1, 0, 0, 1);
	float dotProduct{DotProduct(g_VectorC, Normalize(g_VectorA))};
	Vector2f vectorD{ Normalize(g_VectorA).x * dotProduct,Normalize(g_VectorA).y * dotProduct };
	DrawVector(vectorD, g_MiddleOfScreen);
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

	g_Angle += elapsedSec;
	g_VectorC.x = 100 * cos(g_Angle);
	g_VectorC.y = 100 * sin(g_Angle);
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
	g_CurrentMousePos.x = float(e.x);
	g_CurrentMousePos.y = float(g_WindowHeight - e.y);
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