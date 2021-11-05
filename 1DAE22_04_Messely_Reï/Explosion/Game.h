#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Explosion - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
const Color4f g_Black{ 0,0,0,1 };
const Color4f g_ExplodedBombColour{ 0,0,0,0.5f };
const Color4f g_Red{ 1,0,0,1 };

bool g_IsExploding(false);

const float g_BombSize{ 40 };
const float g_ExplosionSize{ 40 };
float g_Drift{};

const Point2f g_BombPoint{g_WindowWidth / 2 - g_BombSize / 2, g_WindowHeight / 2 - g_BombSize / 2};
Point2f g_ExplosionPoint{ g_WindowWidth / 2 - g_ExplosionSize / 2, g_WindowHeight / 2 - g_ExplosionSize / 2 };
Point2f g_MousePos{};

// Declare your own functions here
void ProcessMouseClick();
void DrawExplosion();
void UpdateExplosion();
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
