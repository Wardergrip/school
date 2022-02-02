#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "LoopedDrawings - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 500 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
const Point2f g_CenterPointStairs{g_WindowWidth /4, 3 * g_WindowHeight / 4};
const Point2f g_CenterPointSpinning{3 * g_WindowWidth / 4, 3 * g_WindowHeight / 4};
const Point2f g_CenterPointSquares{g_WindowWidth / 4, g_WindowHeight / 4};
const Point2f g_CenterPointSpiral{3*g_WindowWidth / 4, g_WindowHeight / 4};

const Color4f g_Green{ 153 / 255.0f, 255 /255.0f, 204 / 255.0f, 1};
const Color4f g_Red{ 240 / 255.0f, 144 / 255.0f, 144 / 255.0f, 1 };
const Color4f g_Blue{ 134 / 255.0f, 179 / 255.0f, 223 / 255.0f,1 };
const Color4f g_Yellow{ 244 / 255.0f, 244 / 255.0f, 146 / 255.0f, 1 };
// Declare your own functions here
void DrawStairs();
void DrawSpinning();
void DrawSquares();
void DrawSpiral();
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
