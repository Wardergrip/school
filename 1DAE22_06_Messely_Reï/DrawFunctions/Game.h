#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "DrawFunctions - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here

// Declare your own functions here
void DrawSquares(Point2f BottomLeft, float size, float numberOfSquares = 1);
void DrawSquares(float x, float y, float size, float numberOfSquares = 1);

void DrawEquilateralTriangle(float x, float y, float size, bool isFilled = 0);
void DrawEquilateralTriangle(Point2f bottomLeft, float size, bool isFilled = 0);

void DrawLinearGradient(float x, float y, float width, float height, Color4f left, Color4f right);
void DrawLinearGradient(Point2f bl, float width, float height, Color4f left, Color4f right);
void DrawLinearGradient(Rectf rectf, Color4f left, Color4f right);

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
