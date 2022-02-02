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
	SetColor(0, 0, 76 / 255.0f, 1);
	FillRect(0, 0, g_WindowWidth, g_WindowHeight);
	ThrowOneDie();
	ThrowTwoDice();
	VisualiseOneDie();
	VisualiseTwoDice();
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
void ThrowOneDie() 
{
	int result = (rand() % 6) + 1;
	switch (result)
	{
	case 1:
		++g_OneDieThrewOne;
		break;
	case 2:
		++g_OneDieThrewTwo;
		break;
	case 3:
		++g_OneDieThrewThree;
		break;
	case 4:
		++g_OneDieThrewFour;
		break;
	case 5:
		++g_OneDieThrewFive;
		break;
	case 6:
		++g_OneDieThrewSix;
		break;
	}
}
void ThrowTwoDice() 
{
	int result1 = (rand() % 6) + 1;
	int result2 = (rand() % 6) + 1;
	int result{ result1 + result2 };
	switch (result)
	{
	case 2:
		++g_TwoDiceThrewTwo;
		break;
	case 3:
		++g_TwoDiceThrewThree;
		break;
	case 4:
		++g_TwoDiceThrewFour;
		break;
	case 5:
		++g_TwoDiceThrewFive;
		break;
	case 6:
		++g_TwoDiceThrewSix;
		break;
	case 7:
		++g_TwoDiceThrewSeven;
		break;
	case 8:
		++g_TwoDiceThrewEight;
		break;
	case 9:
		++g_TwoDiceThrewNine;
		break;
	case 10:
		++g_TwoDiceThrewTen;
		break;
	case 11:
		++g_TwoDiceThrewEleven;
		break;
	case 12:
		++g_TwoDiceThrewTwelve;
		break;
	}
}
void VisualiseOneDie() 
{
	SetColor(255 / 255.0f, 102 / 255.0f, 102 / 255.0f, 1);
	const float offsetOfBorder{10};
	const float spaceBetween{ 5 };
	const float height{20};
	const Point2f p1{ offsetOfBorder,offsetOfBorder };
	const Point2f p2{ p1.x, p1.y + height + spaceBetween };
	const Point2f p3{ p1.x, p2.y + height + spaceBetween };
	const Point2f p4{ p1.x, p3.y + height + spaceBetween };
	const Point2f p5{ p1.x, p4.y + height + spaceBetween };
	const Point2f p6{ p1.x, p5.y + height + spaceBetween };
	FillRect(p1, float(g_OneDieThrewOne), height);
	FillRect(p2, float(g_OneDieThrewTwo), height);
	FillRect(p3, float(g_OneDieThrewThree), height);
	FillRect(p4, float(g_OneDieThrewFour), height);
	FillRect(p5, float(g_OneDieThrewFive), height);
	FillRect(p6, float(g_OneDieThrewSix), height);
}
void VisualiseTwoDice()
{
	SetColor(204 / 255.0f, 153 / 255.0f, 255 / 255.0f, 1);
	const float offsetOfBorder{ 10 };
	const float spaceBetween{ 5 };
	const float height{ 20 };
	const Point2f p1{ offsetOfBorder, 2* offsetOfBorder + 6 * height + 6*spaceBetween };
	const Point2f p2{ p1.x, p1.y + height + spaceBetween };
	const Point2f p3{ p1.x, p2.y + height + spaceBetween };
	const Point2f p4{ p1.x, p3.y + height + spaceBetween };
	const Point2f p5{ p1.x, p4.y + height + spaceBetween };
	const Point2f p6{ p1.x, p5.y + height + spaceBetween };
	const Point2f p7{ p1.x, p6.y + height + spaceBetween };
	const Point2f p8{ p1.x, p7.y + height + spaceBetween };
	const Point2f p9{ p1.x, p8.y + height + spaceBetween };
	const Point2f p10{ p1.x, p9.y + height + spaceBetween };
	const Point2f p11{ p1.x, p10.y + height + spaceBetween };
	FillRect(p1, float(g_TwoDiceThrewTwo), height);
	FillRect(p2, float(g_TwoDiceThrewThree), height);
	FillRect(p3, float(g_TwoDiceThrewFour), height);
	FillRect(p4, float(g_TwoDiceThrewFive), height);
	FillRect(p5, float(g_TwoDiceThrewSix), height);
	FillRect(p6, float(g_TwoDiceThrewSeven), height);
	FillRect(p7, float(g_TwoDiceThrewEight), height);
	FillRect(p8, float(g_TwoDiceThrewNine), height);
	FillRect(p9, float(g_TwoDiceThrewTen), height);
	FillRect(p10, float(g_TwoDiceThrewEleven), height);
	FillRect(p11, float(g_TwoDiceThrewTwelve), height);
}
#pragma endregion ownDefinitions