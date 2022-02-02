#include "pch.h"
#include "Game.h"
#include <cmath>
#define _USE_MATH_DEFINES
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
#pragma region DrawSquares
	SetColor(0, 0, 0, 1);
	DrawSquares(10, 230, 60, 10);
	DrawSquares(80, 230, 40, 5);
	DrawSquares(130, 230, 20, 3);
#pragma endregion
#pragma region ShrinkingTriangle
	SetColor(1,0,0,1);
	DrawEquilateralTriangle(200, 230, 60, 1);
	SetColor(0, 1, 0, 1);
	DrawEquilateralTriangle(210, 235, 40, 1);
	SetColor(0, 0, 1, 1);
	DrawEquilateralTriangle(215, 238, 30, 1);
#pragma endregion
#pragma region SmallerTriangles
	SetColor(0, 1, 1, 1);
	DrawEquilateralTriangle(280, 230, 30, 1);
	SetColor(1, 1, 0, 1);
	DrawEquilateralTriangle(310, 230, 30, 1);
	SetColor(1, 0, 1, 1);
	DrawEquilateralTriangle(295, 256, 30, 1);

	SetColor(0, 0, 0, 1);
	DrawEquilateralTriangle(280, 230, 30, 0);
	DrawEquilateralTriangle(310, 230, 30, 0);
	DrawEquilateralTriangle(295, 256, 30, 0);
#pragma endregion
#pragma region Pentagrams
	SetColor(1, 0, 0, 1);
	DrawPentagram(280, 190, 35);
	SetColor(0, 0, 1, 1);
	DrawPentagram(340, 190, 25);
#pragma endregion
#pragma region LinearGradients
	DrawLinearGradient(10, 195, 60, 10, g_Black, g_White);
	DrawLinearGradient(10, 177, 120, 15, g_Red, g_Magenta);
	DrawLinearGradient(10, 155, g_WindowWidth / 2 - 20, 20, g_Yellow, g_Salmon);
	DrawLinearGradient(10, 127, g_WindowWidth - 40, 25, g_Blue, g_Salmon);
#pragma endregion
#pragma region DotGrids
	SetColor(1, 0, 0, 1);
	DrawDotGrid(30, 50, 14, 3, 5, 29);
	SetColor(0, 1, 0, 1);
	DrawDotGrid(210, 80, 12, 2, 7, 25);
	SetColor(0, 0, 1, 1);
	DrawDotGrid(210, 80, 6, 2, 7, 25);
#pragma endregion
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
void DrawSquares(float x, float y, float size, float numberOfSquares)
{
	float step{ (size / numberOfSquares) * 0.5f };
	for (int i{0}; i < numberOfSquares; i++) 
	{
		DrawRect(x + i * step, y + i * step, size - 2 * i * step, size - 2 * i * step);
	}
}
void DrawSquares(const Point2f& BottomLeft, float size, float numberOfSquares)
{
	DrawSquares(BottomLeft.x, BottomLeft.y, size, numberOfSquares);
}

void DrawEquilateralTriangle(float x, float y, float size, bool isFilled)
{
	const Point2f bl{ x,y };
	const Point2f br{ bl.x + size, bl.y };
	const Point2f middle{ x + size * float(cos(1.04719755)), y + size * float(sin(1.04719755)) };
	if (isFilled == true) 
	{
		FillTriangle(bl, br, middle);
	}
	else 
	{
		DrawTriangle(bl, br, middle);
	}
}
void DrawEquilateralTriangle(const Point2f& bottomLeft, float size, bool isFilled) 
{
	DrawEquilateralTriangle(bottomLeft.x, bottomLeft.y, size, isFilled);
}

void DrawPentagram(float x, float y, float radius, float startingAngle, float thickness)
{
	float angle{ startingAngle };
	const Point2f p1{ x + (cos(angle) * radius), y + (sin(angle) * radius) };
	angle += 0.4f * float(M_PI);
	const Point2f p2{ x + (cos(angle) * radius), y + (sin(angle) * radius) };
	angle += 0.4f * float(M_PI);
	const Point2f p3{ x + (cos(angle) * radius), y + (sin(angle) * radius) };
	angle += 0.4f * float(M_PI);
	const Point2f p4{ x + (cos(angle) * radius), y + (sin(angle) * radius) };
	angle += 0.4f * float(M_PI);
	const Point2f p5{ x + (cos(angle) * radius), y + (sin(angle) * radius) };
	DrawLine(p1, p3, thickness);
	DrawLine(p1, p4, thickness);
	DrawLine(p2, p4, thickness);
	DrawLine(p2, p5, thickness);
	DrawLine(p3, p5, thickness);
}
void DrawPentagram(const Point2f& centerpoint, float radius, float startingAngle, float thickness) 
{
	DrawPentagram(centerpoint.x, centerpoint.y, radius, startingAngle, thickness);
}

void DrawLinearGradient(float x, float y, float width, float height, const Color4f& left, const Color4f& right)
{
	const float stepR{ (left.r - right.r) / width };
	const float stepG{ (left.g - right.g) / width };
	const float stepB{ (left.b - right.b) / width };
	const float stepA{ (left.a - right.a) / width };
	for (int i{0}; i <= width; i++) 
	{
		SetColor(left.r - (stepR * i), left.g - (stepG * i), left.b - (stepB * i), left.a - (stepA * i));
		FillRect(x + i, y, 1, height);
	}
}
void DrawLinearGradient(const Point2f& bl, float width, float height, const Color4f& left, const Color4f& right)
{
	DrawLinearGradient(bl.x, bl.y, width, height, left, right);
}
void DrawLinearGradient(const Rectf& rectf, const Color4f& left, const Color4f& right)
{
	DrawLinearGradient(rectf.bottom, rectf.left, rectf.width, rectf.height, left, right);
}

void DrawDotGrid(float x, float y, float radius, float rows, float columns, float dotSpace)
{
	if (dotSpace == 0) 
	{
		dotSpace = 2 * radius;
	}
	for (int i{0}; i < rows; i++) 
	{
		for (int a{ 0 }; a < columns; a++)
		{
			FillEllipse(x + a * dotSpace, y + i * dotSpace, radius, radius);
		}
	}
}
void DrawDotGrid(const Point2f& bottomLeft, float radius, float rows, float columns, float dotSpace)
{
	DrawDotGrid(bottomLeft.x, bottomLeft.y, radius, rows, columns, dotSpace);
}
#pragma endregion ownDefinitions