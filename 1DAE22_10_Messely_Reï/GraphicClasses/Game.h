#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "GraphicClasses - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
class Fraction;
Fraction* g_pFrac1{ nullptr };
Fraction* g_pFrac2{ nullptr };
Fraction* g_pFrac3{ nullptr };
Fraction* g_pFrac4{ nullptr };
Fraction* g_pFrac5{ nullptr };
Fraction* g_pFrac6{ nullptr };

class Light;
Light* g_pLight1{ nullptr };
Light* g_pLight2{ nullptr };
Light* g_pLight3{ nullptr };
Light* g_pLight4{ nullptr };
Light* g_pLight5{ nullptr };
Light* g_pLight6{ nullptr };
Light* g_pLight7{ nullptr };
Light* g_pLight8{ nullptr };

class DaeEllipse;
DaeEllipse* g_pDell1{ nullptr };
DaeEllipse* g_pDell2{ nullptr };
DaeEllipse* g_pDell3{ nullptr };

// Declare your own functions here
void CreateFractions();
void DeleteFractions();
void DrawFractions();

void CreateLights();
void DeleteLights();
void DrawLights();
void HitLights(const Point2f& pos);

void CreateDells();
void DeleteDells();
void DrawDells();
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
