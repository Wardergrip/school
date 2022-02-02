#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "MovingLines - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 500 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
const Color4f g_BackgroundColor(100 / 255.0f, 100/255.0f, 170 / 255.0f, 1.0f);
const Color4f g_White(1.0f, 1.0f, 1.0f, 1.0f);
const Color4f g_Yellow(200 / 255.0f, 200 / 255.0f, 59 / 255.0f, 1.0f);

float g_GlobalPos{};
// Declare your own functions here
void DrawLineHorizontalOne();
void DrawLineHorizontalTwo();
void DrawLineVerticalOne();
void DrawLineVerticalTwo();
void DrawYellowBox();

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
