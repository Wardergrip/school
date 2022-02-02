#include "pch.h"
#include "Game.h"
#define _USING_MATH_DEFINES
#include <cmath>
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	std::cout << "% people playing games" << std::endl;
	std::cout << "In the range [0,20]? ";
	std::cin >> g_ZeroToTwenty;
	std::cout << "In the range [21,40]? ";
	std::cin >> g_TwentyoneToForty;
	std::cout << "In the range [41,60]? ";
	std::cin >> g_FortyoneToSixty;
	std::cout << "Older than 60? ";
	std::cin >> g_SixtyPlus;
}

void Draw()
{
	ClearBackground();
	SetColor(g_BackgroundColor);
	FillRect(0, 0, g_WindowWidth, g_WindowHeight);
	DrawHouse();
	DrawFlag();
	DrawCheckerPattern();
	DrawColorBand();
	DrawPentagram();
	DrawColumnChart();
	// Put your own draw statements here

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
void DrawHouse() 
{
	// House
	SetColor(g_HouseColor);
	FillRect(g_HouseX, g_HouseY, g_HouseW, g_HouseH / 2);
	// Roof
	SetColor(g_HouseRoofColor);
	FillRect(g_HouseX, g_HouseY, g_HouseW, g_HouseH / 2);
	const Point2f p1{ g_HouseX, g_HouseY + g_HouseH / 2  };
	const Point2f p2{ g_HouseX + g_HouseW, g_HouseY + g_HouseH / 2 };
	const Point2f p3{ g_HouseX + g_HouseW / 2, g_HouseY + g_HouseH};
	FillTriangle(p1, p2, p3);
	// Border
	SetColor(g_HouseBorder);
	DrawRect(g_HouseX, g_HouseY, g_HouseW, g_HouseH / 2, 2.0f);
	DrawTriangle(p1, p2, p3, 2.0f);
}
void DrawFlag() 
{
	SetColor(g_FlagBorder);
	DrawRect(g_FlagX, g_FlagY, g_FlagW, g_FlagH, 1.0f);
	// First block
	SetColor(g_Black);
	FillRect(g_FlagX + 1, g_FlagY + 1, g_FlagW / 3 - 1, g_FlagH - 1);
	// Second block
	SetColor(g_Yellow);
	FillRect(g_FlagX + 1 + g_FlagW / 3, g_FlagY + 1, (g_FlagW / 3)-1, g_FlagH - 1);
	// Third block
	SetColor(g_Red);
	FillRect(g_FlagX + (2*g_FlagW) / 3, g_FlagY + 1, (g_FlagW  / 3) -1, g_FlagH - 1);
}
void DrawCheckerPattern() 
{
	SetColor(g_CheckersBorder);
	DrawRect(g_CheckersX, g_CheckersY, g_CheckersSize, g_CheckersSize, 1.0f);
	//First row, starting from bottom left
	SetColor(g_Black);
	FillRect(g_CheckersX, g_CheckersY + 1, (g_CheckersSize - 1) / 3, (g_CheckersSize - 1) / 3);
	SetColor(g_White);
	FillRect(g_CheckersX + (g_CheckersSize - 1) / 3, g_CheckersY + 1, (g_CheckersSize - 1) / 3, (g_CheckersSize - 1) / 3);
	SetColor(g_Black);
	FillRect(g_CheckersX + 2*((g_CheckersSize - 1) / 3), g_CheckersY + 1, (g_CheckersSize - 5) / 3, (g_CheckersSize - 1) / 3);
	//Second row
	SetColor(g_White);
	FillRect(g_CheckersX, (g_CheckersY + 1) + (g_CheckersSize - 1) / 3, (g_CheckersSize - 1) / 3, (g_CheckersSize - 1) / 3);
	SetColor(g_Black);
	FillRect(g_CheckersX + (g_CheckersSize - 1) / 3, (g_CheckersY + 1) + (g_CheckersSize - 1) / 3, (g_CheckersSize - 1) / 3, (g_CheckersSize - 1) / 3);
	SetColor(g_White);
	FillRect(g_CheckersX + 2*((g_CheckersSize - 1) / 3), (g_CheckersY + 1) + (g_CheckersSize - 1) / 3, (g_CheckersSize - 1) / 3, (g_CheckersSize - 1) / 3);
	//Third row
	SetColor(g_Black);
	FillRect(g_CheckersX, (g_CheckersY + 1) + 2 *((g_CheckersSize - 1) / 3), (g_CheckersSize - 1) / 3, (g_CheckersSize - 1) / 3);
	SetColor(g_White);
	FillRect(g_CheckersX + (g_CheckersSize - 1) / 3, (g_CheckersY + 1) + 2 * ((g_CheckersSize - 1) / 3), (g_CheckersSize - 1) / 3, (g_CheckersSize - 1) / 3);
	SetColor(g_Black);
	FillRect(g_CheckersX + 2 * ((g_CheckersSize - 1) / 3), (g_CheckersY + 1) + 2 * ((g_CheckersSize - 1) / 3), (g_CheckersSize - 5) / 3, (g_CheckersSize - 1) / 3);

}
void DrawColorBand() 
{
	const Color4f color1{ 50 / 255.0f, 50 / 255.0f, 50 / 255.0f , 1.0f};
	const Color4f color2{ 1.0f, 0.0f, 0.0f, 1.0f };
	const Color4f color3{ 0.0f, 1.0f, 0.0f, 1.0f};
	const Color4f color4{ 0.0f, 0.0f, 1.0f, 1.0f};
	const Color4f color5{ 1.0f, 0.0f, 1.0f, 1.0f};
	const Color4f color6{ 1.0f, 1.0f, 0.0f, 1.0f};
	const Color4f color7{ color3};
	const Color4f color8{ 0.0f, 1.0f, 1.0f, 1.0f};
	const Color4f color9{ 1.0f, 1.0f, 1.0f, 1.0f};
	const Color4f darken{ 0.0f, 0.0f, 0.0f, 0.5f};
	const float smallBoxWidth{ g_BandW / 9 };
#pragma region drawAllLittleBoxes
	SetColor(color1);
	FillRect(g_BandX, g_BandY, smallBoxWidth, g_BandH);
	SetColor(color2);
	FillRect(g_BandX + 1 * smallBoxWidth, g_BandY, smallBoxWidth, g_BandH);
	SetColor(color3);
	FillRect(g_BandX + 2 * smallBoxWidth, g_BandY, smallBoxWidth, g_BandH);
	SetColor(color4);
	FillRect(g_BandX + 3 * smallBoxWidth, g_BandY, smallBoxWidth, g_BandH);
	SetColor(color5);
	FillRect(g_BandX + 4 * smallBoxWidth, g_BandY, smallBoxWidth, g_BandH);
	SetColor(color6);
	FillRect(g_BandX + 5 * smallBoxWidth, g_BandY, smallBoxWidth, g_BandH);
	SetColor(color7);
	FillRect(g_BandX + 6 * smallBoxWidth, g_BandY, smallBoxWidth, g_BandH);
	SetColor(color8);
	FillRect(g_BandX + 7 * smallBoxWidth, g_BandY, smallBoxWidth, g_BandH);
	SetColor(color9);
	FillRect(g_BandX + 8 * smallBoxWidth, g_BandY, smallBoxWidth, g_BandH);
#pragma endregion
	//Darken lower part of the "LittleBoxes"
	SetColor(darken);
	FillRect(g_BandX, g_BandY, g_BandW, g_BandH / 2);

	//Draw border
	SetColor(g_BandBorder);
	DrawRect(g_BandX, g_BandY, g_BandW, g_BandH, 3.0f);
}
void DrawPentagram() 
{
	SetColor(g_Pentagram);
	float angle = g_StartingAngle;
	const Point2f p1{g_PentagramCenterpoint.x + (cos(angle) * g_PentagramRadius), g_PentagramCenterpoint.y + (sin(angle) * g_PentagramRadius) };
	angle += 0.4f * float(M_PI);
	const Point2f p2{ g_PentagramCenterpoint.x + (cos(angle) * g_PentagramRadius), g_PentagramCenterpoint.y + (sin(angle) * g_PentagramRadius) };
	angle += 0.4f * float(M_PI);
	const Point2f p3{ g_PentagramCenterpoint.x + (cos(angle) * g_PentagramRadius), g_PentagramCenterpoint.y + (sin(angle) * g_PentagramRadius) };
	angle += 0.4f * float(M_PI);
	const Point2f p4{ g_PentagramCenterpoint.x + (cos(angle) * g_PentagramRadius), g_PentagramCenterpoint.y + (sin(angle) * g_PentagramRadius) };
	angle += 0.4f * float(M_PI);
	const Point2f p5{ g_PentagramCenterpoint.x + (cos(angle) * g_PentagramRadius), g_PentagramCenterpoint.y + (sin(angle) * g_PentagramRadius) };
	DrawLine(p1, p3, g_PentagramThickness);
	DrawLine(p1, p4, g_PentagramThickness);
	DrawLine(p2, p4, g_PentagramThickness);
	DrawLine(p2, p5, g_PentagramThickness);
	DrawLine(p3, p5, g_PentagramThickness);
}
void DrawColumnChart() 
{
	const Color4f blue1{ 0, 139 / 255.0f, 139 / 255.0f, 1.0f };
	const Color4f blue2{ 0, 154 / 255.0f, 205 / 255.0f, 1.0f };
	const Color4f blue3{ 0, 191 / 255.0f, 255 / 255.0f, 1.0f };
	const Color4f blue4{ 0, 139 / 255.0f, 205 / 255.0f, 1.0f };
	
	SetColor(blue1);
	FillRect(g_ColumnX, g_ColumnY, g_ColumnW / 4, (g_ZeroToTwenty/100.0f) * g_ColumnMaxHeight);
	SetColor(blue2);
	FillRect(g_ColumnX + g_ColumnW / 4, g_ColumnY, g_ColumnW / 4, (g_TwentyoneToForty / 100.0f) * g_ColumnMaxHeight);
	SetColor(blue3);
	FillRect(g_ColumnX + 2*(g_ColumnW / 4), g_ColumnY, g_ColumnW / 4, (g_FortyoneToSixty / 100.0f) * g_ColumnMaxHeight);
	SetColor(blue4);
	FillRect(g_ColumnX + 3*(g_ColumnW / 4), g_ColumnY, g_ColumnW / 4, (g_SixtyPlus / 100.0f) * g_ColumnMaxHeight);

}
#pragma endregion ownDefinitions