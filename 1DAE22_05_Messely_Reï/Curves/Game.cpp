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
	SetColor(0, 0, 76 / 255.0f, 1); // Dark blue
	FillRect(0, 0, g_WindowWidth, g_WindowHeight);
	SetColor(1, 0, 0, 1); // Red
	DrawOctagon();
	SetColor(86 / 255.0f, 86 / 255.0f, 196 / 255.0f); // Lighter blue
	DrawCrosier();
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
void DrawOctagon() 
{
	const Point2f centerPoint{ g_WindowWidth / 4, g_WindowHeight / 2 };
	const int amountOfVertices{ 8 };
	const float width{g_WindowWidth / 4 - 10}, height{g_WindowHeight /2 - 10};
	const float deltaAngle{2*g_Pi / amountOfVertices};
	float angle{0};
	float Px{0}, Py{0}, Sx{0}, Sy{0};
	for (int i{0}; i <= amountOfVertices; i++) 
	{
		if ((Px != 0) && (Py != 0)) // Check if the coords aren't 0
		{
			Sx = Px; Sy = Py;
		}
		else // Make the previous coords equal to current coords to make sure no unintended lines are drawn 
		{
			Sx = centerPoint.x + width * cosf(angle);
			Sy = centerPoint.y + height * sinf(angle);
		} 
		Px = centerPoint.x + width * cosf(angle);
		Py = centerPoint.y + height * sinf(angle);
		DrawLine(Sx, Sy, Px, Py);
		angle += deltaAngle;
	}
}
void DrawCrosier() 
{
	const Point2f centerPoint{ (3 * g_WindowWidth) / 4, g_WindowHeight / 2 };
	const float opening = g_WindowWidth / 4;
	const double angleSteps = 0.01;
	const int windings = 8;
	float r{};
	float Px{ 0 }, Py{ 0 }, Sx{ 0 }, Sy{ 0 };
	for (double i = g_Pi /2; i < ((double(windings) * 2*M_PI) + M_PI / 2); i += angleSteps) 
	{
		r = opening / float(sqrt(i));
		if ((Px != 0) && (Py != 0)) // Check if the coords aren't 0
		{
			Sx = Px; Sy = Py;
		}
		else // Make the previous coords equal to current coords to make sure no unintended lines are drawn
		{
			Sx = centerPoint.x + r * float(cos(i));
			Sy = centerPoint.y + r * float(sin(i));
		}
		Px = centerPoint.x + r * float(cos(i));
		Py = centerPoint.y + r * float(sin(i));
		DrawLine(Sx, Sy, Px, Py);
	}

}
#pragma endregion ownDefinitions