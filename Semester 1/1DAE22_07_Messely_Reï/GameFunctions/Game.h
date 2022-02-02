#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "GameFunctions - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
const float g_Radius{ 40 };
const Circlef g_RandomCircle{float(GenerateRandom(int(g_Radius), int(g_WindowWidth - g_Radius))), float(GenerateRandom(int(g_Radius), int(g_WindowHeight - g_Radius))), g_Radius};
const Point2f g_RandomRectPos{ float(GenerateRandom(int(g_Radius), int(g_WindowWidth - g_Radius))), float(GenerateRandom(int(g_Radius), int(g_WindowHeight - g_Radius))) };
const Rectf g_RandomRect{ g_RandomRectPos.x,g_RandomRectPos.y, 60,30 };

Point2f g_MousePos{};
Rectf g_MouseRect{0,0,40,20};
Circlef g_MouseCircle{ 0,0,30 };
// Declare your own functions here

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
