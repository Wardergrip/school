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
	SetColor(g_BackgroundColor);
	FillRect(0, 0, g_WindowWidth, g_WindowHeight);
	// Put your own draw statements here
	DrawMinutes();
	DrawHours();
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

	// Use += for counter clock wise rotation, -= for clockwise rotation
	g_AngleMinutes -= 2*g_Pi / 240.0f;
	g_AngleHours -= (2 * g_Pi / 240.0f) / 12.0f;
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
void DrawMinutes() 
{
	SetColor(g_White);
	float AngleMinutesOffset1{ g_AngleMinutes + 0.1f * g_Pi }; // Offset is not able to be changed, unfortunately
	float AngleMinutesOffset2{ g_AngleMinutes - 0.1f * g_Pi }; // Offset is not able to be changed, unfortunately
	
	float RadiusOffsetPart1{ g_RadiusMinutes / 5.0f };
	float RadiusOffsetPart2{ g_RadiusMinutes * 0.81333333333333f };
	
	// I tried really hard to use trigonometry to be able to make both offsetparts adaptive to both the offset angle and place of how close it is to the centerpoint.

	DrawLine(g_CenterPoint.x, g_CenterPoint.y, g_CenterPoint.x + float(cos(AngleMinutesOffset1) * RadiusOffsetPart1), g_CenterPoint.y + float(sin(AngleMinutesOffset1) * RadiusOffsetPart1));
	DrawLine(g_CenterPoint.x + float(cos(AngleMinutesOffset1) * RadiusOffsetPart1), g_CenterPoint.y + float(sin(AngleMinutesOffset1) * RadiusOffsetPart1), g_CenterPoint.x + float(cos(g_AngleMinutes) * g_RadiusMinutes), g_CenterPoint.y + float(sin(g_AngleMinutes) * g_RadiusMinutes));
	
	DrawLine(g_CenterPoint.x, g_CenterPoint.y, g_CenterPoint.x + float(cos(AngleMinutesOffset2) * RadiusOffsetPart1), g_CenterPoint.y + float(sin(AngleMinutesOffset2) * RadiusOffsetPart1));
	DrawLine(g_CenterPoint.x + float(cos(AngleMinutesOffset2) * RadiusOffsetPart1), g_CenterPoint.y + float(sin(AngleMinutesOffset2) * RadiusOffsetPart1), g_CenterPoint.x + float(cos(g_AngleMinutes) * g_RadiusMinutes), g_CenterPoint.y + float(sin(g_AngleMinutes) * g_RadiusMinutes));

}
void DrawHours() 
{
	SetColor(g_White);
	float AngleHoursOffset1{ g_AngleHours + 0.1f * g_Pi }; // Offset is not able to be changed, unfortunately
	float AngleHoursOffset2{ g_AngleHours - 0.1f * g_Pi }; // Offset is not able to be changed, unfortunately

	float RadiusOffsetPart1{ g_RadiusHours / 5.0f };
	float RadiusOffsetPart2{ g_RadiusHours * 0.81333333333333f };

	// I tried really hard to use trigonometry to be able to make both offsetparts adaptive to both the offset angle and place of how close it is to the centerpoint.

	DrawLine(g_CenterPoint.x, g_CenterPoint.y, g_CenterPoint.x + float(cos(AngleHoursOffset1) * RadiusOffsetPart1), g_CenterPoint.y + float(sin(AngleHoursOffset1) * RadiusOffsetPart1));
	DrawLine(g_CenterPoint.x + float(cos(AngleHoursOffset1) * RadiusOffsetPart1), g_CenterPoint.y + float(sin(AngleHoursOffset1) * RadiusOffsetPart1), g_CenterPoint.x + float(cos(g_AngleHours) * g_RadiusHours), g_CenterPoint.y + float(sin(g_AngleHours) * g_RadiusHours));

	DrawLine(g_CenterPoint.x, g_CenterPoint.y, g_CenterPoint.x + float(cos(AngleHoursOffset2) * RadiusOffsetPart1), g_CenterPoint.y + float(sin(AngleHoursOffset2) * RadiusOffsetPart1));
	DrawLine(g_CenterPoint.x + float(cos(AngleHoursOffset2) * RadiusOffsetPart1), g_CenterPoint.y + float(sin(AngleHoursOffset2) * RadiusOffsetPart1), g_CenterPoint.x + float(cos(g_AngleHours) * g_RadiusHours), g_CenterPoint.y + float(sin(g_AngleHours) * g_RadiusHours));
}
#pragma endregion ownDefinitions