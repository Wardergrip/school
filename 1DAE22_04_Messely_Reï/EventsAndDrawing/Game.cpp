#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	RandomiseCoords();
	std::cout << "Drew rectangle: " << "X " << g_SqrPos.x << "Y " << g_SqrPos.y << "W " << g_SqrW << "H " << g_SqrH << std::endl;
	/* not my code but too cool to delete
	//Init line points
	g_BouncingPoint1 = Random(Point2f{}, Point2f{ g_WindowWidth, g_WindowHeight });
	g_BouncingPoint2 = Random(Point2f{}, Point2f{ g_WindowWidth, g_WindowHeight });
	g_BouncingPoint1Vel = Random(Point2f{}, Point2f{ 1.f, 1.f});
	g_BouncingPoint2Vel = Random(Point2f{}, Point2f{ 1.f, 1.f});
	*/
}

void Draw()
{
	ClearBackground();
	// Put your own draw statements here
	DrawRandomRect();
	DrawBouncingLine();
	// DrawBouncingLines(); not my code but too cool to delete
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
	if ((((g_MousePos.x >= g_SqrPos.x + g_Movement) && (g_MousePos.y >= g_SqrPos.y) && ((g_MousePos.x <= g_SqrPos.x + g_SqrW + g_Movement) && (g_MousePos.y <= g_SqrPos.y + g_SqrH))) || ((g_MousePos.x >= g_MovementPlus - g_SqrW) && (g_MousePos.y >= g_SqrPos.y) && (g_MousePos.x <= g_MovementPlus) && (g_MousePos.y <= g_SqrPos.y + g_SqrH))) && (g_IsGreen == false))
	{
		g_SqrColor = g_Green;
		g_IsGreen = true;
		g_MousePos.x = -1; g_MousePos.y = -1; // Put mouse in impossible range to prevent automatic double click
	}
	else if ((((g_MousePos.x >= g_SqrPos.x + g_Movement) && (g_MousePos.y >= g_SqrPos.y) && ((g_MousePos.x <= g_SqrPos.x + g_SqrW + g_Movement) && (g_MousePos.y <= g_SqrPos.y + g_SqrH))) || ((g_MousePos.x >= g_MovementPlus - g_SqrW) && (g_MousePos.y >= g_SqrPos.y) && (g_MousePos.x <= g_MovementPlus) && (g_MousePos.y <= g_SqrPos.y + g_SqrH))) && (g_IsGreen == true))
	{
		RandomiseCoords();
		// Debugging
		std::cout << "Drew rectangle: " << "X " << g_SqrPos.x << "Y " << g_SqrPos.y << "W " << g_SqrW << "H " << g_SqrH << std::endl;
		// 
		g_SqrColor = g_Gray;
		g_IsGreen = false;
		g_Movement = 0;
		g_MovementPlus = 0;
	}
	switch (g_SpecialState)
	{
	case SpecialState::none:
		break;
	case SpecialState::running:
		if (g_SqrPos.x + g_Movement + g_SqrW >= g_WindowWidth) 
		{
			++g_MovementPlus;
		}
		if (g_MovementPlus - g_SqrW == 0)
		{
			g_SqrPos.x = 0;
			g_MovementPlus = 0;
			g_Movement = 0;
		}
		++g_Movement;
		break;
	case SpecialState::bouncing:
		// UpdateBouncingLines(elapsedSec); not my code but too cool to delete
		if (g_BouncingLineLength >= g_WindowHeight / 2)
		{
			g_BouncingLineGrowing = -1;
		}
		else if (g_BouncingLineLength <= 1)
		{
			g_BouncingLineGrowing = 1;
		}
		g_BouncingLineLength += g_BouncingLineGrowing;
		if (g_BouncingLineMid.x >= g_WindowWidth)
		{
			g_BouncingLineDirection = -1;
			std::cout << "Change direction to left\n";
		}
		else if (g_BouncingLineMid.x <= 0)
		{
			g_BouncingLineDirection = 1;
			std::cout << "Change direction to right\n";
		}
		g_BouncingLineMid.x += g_BouncingLineSpeed * g_BouncingLineDirection;
		break;
	}

	
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
	case SDLK_r:
		std::cout << "r key released\n";
		if (g_SpecialState != SpecialState::running) {
			g_SpecialState = SpecialState::running;
		}
		else 
		{
			g_SpecialState = SpecialState::none;
		}
		break;
	case SDLK_l:
		std::cout << "l key released\n";
		if (g_SpecialState != SpecialState::bouncing) {
			g_SpecialState = SpecialState::bouncing;
		}
		else
		{
			g_SpecialState = SpecialState::none;
		}
		break;
	case SDLK_n:
		std::cout << "n key released\n";
		g_SpecialState = SpecialState::none;
		break;
	}
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
	std::cout << "  [" << e.x << ", " << e.y << "]\n";
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
	{
		std::cout << "Left mouse button released\n";
		Point2f mousePos{ float(e.x), float(g_WindowHeight - e.y) };
		g_MousePos = mousePos;
		break;
	}
	case SDL_BUTTON_RIGHT:
		std::cout << "Right mouse button released\n";
		break;
	case SDL_BUTTON_MIDDLE:
		std::cout << "Middle mouse button released\n";
		break;
	}
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
void DrawRandomRect() 
{
	SetColor(g_SqrColor);
	FillRect(g_SqrPos.x + g_Movement, g_SqrPos.y, g_SqrW, g_SqrH);
	FillRect(g_MovementPlus - g_SqrW, g_SqrPos.y, g_SqrW, g_SqrH);
}
void RandomiseCoords()
{
	g_SqrPos.x = (rand() % int(g_WindowWidth - 2 * g_BorderDistance - g_SqrW)) + g_BorderDistance;
	g_SqrPos.y = (rand() % int(g_WindowHeight - 2 * g_BorderDistance - g_SqrH)) + g_BorderDistance;
}
void DrawBouncingLine()
{
	SetColor(g_White);
	DrawLine(g_BouncingLineMid.x, g_BouncingLineMid.y + g_BouncingLineLength, g_BouncingLineMid.x, g_BouncingLineMid.y - g_BouncingLineLength);
}
/*
void DrawBouncingLines()
{
	DrawLine(g_BouncingPoint1, g_BouncingPoint2);
}
void UpdateBouncingLines(float elapsedSec)
{
	if(g_BouncingPoint1.x > g_WindowWidth || g_BouncingPoint1.x < 0.f)
		g_BouncingPoint1Vel.x *= -1;

	if(g_BouncingPoint1.y > g_WindowHeight || g_BouncingPoint1.y < 0.f)
		g_BouncingPoint1Vel.y *= -1;

	if(g_BouncingPoint2.x > g_WindowWidth || g_BouncingPoint2.x < 0.f)
		g_BouncingPoint2Vel.x *= -1;

	if(g_BouncingPoint2.y > g_WindowHeight || g_BouncingPoint2.y < 0.f)
		g_BouncingPoint2Vel.y *= -1;

	g_BouncingPoint1.x += g_BouncingPoint1Vel.x * elapsedSec * 500.f;
	g_BouncingPoint1.y += g_BouncingPoint1Vel.y * elapsedSec * 500.f;
	g_BouncingPoint2.x += g_BouncingPoint2Vel.x * elapsedSec * 500.f;
	g_BouncingPoint2.y += g_BouncingPoint2Vel.y * elapsedSec * 500.f;
}
*/
#pragma endregion ownDefinitions