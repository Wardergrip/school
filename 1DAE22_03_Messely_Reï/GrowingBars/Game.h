#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "GrowingBars - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
float g_RedValue{ 120.0f };

const Color4f g_Yellow(200 / 255.0f, 200 / 255.0f, 0.0f, 1.0f);
const Color4f g_White(1.0f, 1.0f, 1.0f, 1.0f);
Color4f g_Red(g_RedValue / 255.0f, 0.0f, 0.0f, 1.0f);

const float g_borderOffset{ 10 };
const float g_YellowBarW{g_WindowWidth - 2* g_borderOffset};
const float g_YellowBarH{ (g_WindowHeight /2 - 2* g_borderOffset) -1};
float g_YellowBarCurrentW{};

const float g_RedBarW{g_YellowBarW};
const float g_RedBarH{ g_YellowBarH };
float g_RedBarCurrentW{};

const Point2f g_YellowBarBL{ 10, g_WindowHeight - g_YellowBarH - 10 };
const Point2f g_RedBarBL{ 10, 10 };

int g_NrFrames{0};

// Declare your own functions here
void DrawYellowBar();
void DrawRedBar();
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
