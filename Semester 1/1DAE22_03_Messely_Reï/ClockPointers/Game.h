#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "ClockPointers - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
const Color4f g_BackgroundColor{ 0.0f,0.0f,0.0f,1.0f };
const Color4f g_White{ 1.0f, 1.0f, 1.0f, 1.0f};

const Point2f g_CenterPoint{ g_WindowWidth / 2, g_WindowHeight / 2 };

const float g_RadiusMinutes{ 150 };
const float g_RadiusHours{ 75 };
float g_AngleMinutes{};
float g_AngleHours{};
// Declare your own functions here
void DrawMinutes();
void DrawHours();
#pragma endregion ownDeclarations

#pragma region gameFunctions											
void Start();
void Draw();
void Update(float elapsedSec);
void End();
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
#pragma endregion inputHandling
