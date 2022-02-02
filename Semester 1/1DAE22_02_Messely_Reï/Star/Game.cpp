#include "pch.h"
#include "Game.h"
#define _USE_MATH_DEFINES
#include <cmath>

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
	DrawStar();
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
void DrawStar() 
{
	const Point2f centerPoint{ g_WindowWidth / 2, g_WindowHeight / 2 };
	const Color4f starColor{ 1.0f,0.0f,0.0f,1.0f }; // Fully red
	SetColor(starColor);
	float angle{ 0 }; 
#pragma region OuterPointCoords
	float radius{ g_StarOuterRadius };

	const Point2f outerPoint1{ centerPoint.x + (cosf(angle) * radius), centerPoint.y + (sinf(angle) * radius)};
	angle += float(M_PI / 2.0f);
	const Point2f outerPoint2{ centerPoint.x + (cosf(angle) * radius), centerPoint.y + (sinf(angle) * radius) };
	angle += float(M_PI / 2.0f);
	const Point2f outerPoint3{ centerPoint.x + (cosf(angle) * radius), centerPoint.y + (sinf(angle) * radius) };
	angle += float(M_PI / 2.0f);
	const Point2f outerPoint4{ centerPoint.x + (cosf(angle) * radius), centerPoint.y + (sinf(angle) * radius) };
#pragma endregion
#pragma region middlePointCoords
	angle = float(M_PI / 4.0f);
	radius = (2 * g_StarOuterRadius) / 3.0f;

	const Point2f middlePoint1{ centerPoint.x + (cosf(angle) * radius), centerPoint.y + (sinf(angle) * radius) };
	angle += float(M_PI / 2.0f);
	const Point2f middlePoint2{ centerPoint.x + (cosf(angle) * radius), centerPoint.y + (sinf(angle) * radius) };
	angle += float(M_PI / 2.0f);
	const Point2f middlePoint3{ centerPoint.x + (cosf(angle) * radius), centerPoint.y + (sinf(angle) * radius) };
	angle += float(M_PI / 2.0f);
	const Point2f middlePoint4{ centerPoint.x + (cosf(angle) * radius), centerPoint.y + (sinf(angle) * radius) };
#pragma endregion
#pragma region closePointCoords1
	angle = float(M_PI / 6.0f);
	radius = g_StarOuterRadius / 3.0f;

	const Point2f closePoint1{ centerPoint.x + (cosf(angle) * radius), centerPoint.y + (sinf(angle) * radius) };
	angle += float(M_PI / 2.0f);
	const Point2f closePoint2{ centerPoint.x + (cosf(angle) * radius), centerPoint.y + (sinf(angle) * radius) };
	angle += float(M_PI / 2.0f);
	const Point2f closePoint3{ centerPoint.x + (cosf(angle) * radius), centerPoint.y + (sinf(angle) * radius) };
	angle += float(M_PI / 2.0f);
	const Point2f closePoint4{ centerPoint.x + (cosf(angle) * radius), centerPoint.y + (sinf(angle) * radius) };
#pragma endregion
#pragma region closePointCoords2
	angle = float(M_PI / 3.0f);
	radius = g_StarOuterRadius / 3.0f;

	const Point2f closePoint5{ centerPoint.x + (cosf(angle) * radius), centerPoint.y + (sinf(angle) * radius) };
	angle += float(M_PI / 2.0f);
	const Point2f closePoint6{ centerPoint.x + (cosf(angle) * radius), centerPoint.y + (sinf(angle) * radius) };
	angle += float(M_PI / 2.0f);
	const Point2f closePoint7{ centerPoint.x + (cosf(angle) * radius), centerPoint.y + (sinf(angle) * radius) };
	angle += float(M_PI / 2.0f);
	const Point2f closePoint8{ centerPoint.x + (cosf(angle) * radius), centerPoint.y + (sinf(angle) * radius) };
#pragma endregion
#pragma region DrawingTheStar
	const float borderThickness{1.0f};
	// Top right
	DrawLine(outerPoint1, closePoint1, borderThickness);
	DrawLine(closePoint1, middlePoint1, borderThickness);
	DrawLine(middlePoint1, closePoint5, borderThickness);
	DrawLine(closePoint5, outerPoint2, borderThickness);
	// Top left
	DrawLine(outerPoint2, closePoint2, borderThickness);
	DrawLine(closePoint2, middlePoint2, borderThickness);
	DrawLine(middlePoint2, closePoint6, borderThickness);
	DrawLine(closePoint6, outerPoint3, borderThickness);
	// Bottom left
	DrawLine(outerPoint3, closePoint3, borderThickness);
	DrawLine(closePoint3, middlePoint3, borderThickness);
	DrawLine(middlePoint3, closePoint7, borderThickness);
	DrawLine(closePoint7, outerPoint4, borderThickness);
	// Bottom right
	DrawLine(outerPoint4, closePoint4, borderThickness);
	DrawLine(closePoint4, middlePoint4, borderThickness);
	DrawLine(middlePoint4, closePoint8, borderThickness);
	DrawLine(closePoint8, outerPoint1, borderThickness);
#pragma endregion
}
#pragma endregion ownDefinitions