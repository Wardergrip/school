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
#pragma region Colors
const Color4f g_White{ 1,1,1,1 };
const Color4f g_Black{ 0,0,0,1 };
const Color4f g_Red{ 1,0,0,1 };
const Color4f g_Magenta{ 1,0,1,1 };
const Color4f g_Yellow{ 121 / 255.0f, 120 / 255.0f, 2 / 255.0f, 1 };
const Color4f g_Salmon{ 255 / 255.0f, 120 / 255.0f, 120 / 255.0f, 1 };
const Color4f g_Blue{ 11 / 255.0f, 50 / 255.0f, 254 / 255.0f, 1 };
const Color4f g_TransparentSalmon{ 255 / 255.0f, 120 / 255.0f, 120 / 255.0f, 0 };
#pragma endregion

// Declare your own functions here
void DrawSquares(const Point2f& BottomLeft, float size, float numberOfSquares = 1);
void DrawSquares(float x, float y, float size, float numberOfSquares = 1);

void DrawEquilateralTriangle(float x, float y, float size, bool isFilled = 0);
void DrawEquilateralTriangle(const Point2f& bottomLeft, float size, bool isFilled = 0);

void DrawPentagram(const Point2f& centerpoint, float radius, float startingAngle = 0, float thickness = 1);
void DrawPentagram(float x, float y, float radius, float startingAngle = 0, float thickness = 1);

void DrawLinearGradient(float x, float y, float width, float height, const Color4f& left, const Color4f& right);
void DrawLinearGradient(const Point2f& bl, float width, float height, const Color4f& left, Color4f& right);
void DrawLinearGradient(const Rectf& rectf, const Color4f& left, const Color4f& right);

void DrawDotGrid(float x, float y, float radius, float rows = 3, float columns = 3, float dotSpace = 0);
void DrawDotGrid(const Point2f& bottomLeft,float radius, float rows = 3, float columns = 3, float dotSpace = 0);
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
