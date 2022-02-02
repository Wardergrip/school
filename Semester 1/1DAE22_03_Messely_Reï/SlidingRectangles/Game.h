#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "SlidingRectangles - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 500 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
const Color4f g_SquareBorderColor{ 0, 0, 0, 0.5f };
const Color4f g_SquareColor1{ 76 / 255.0f, 237 / 255.0f, 98 / 255.0f, 0.5f };
const Color4f g_SquareColor2{ 76 / 255.0f, 87 / 255.0f, 248 / 255.0f, 0.5f};
const Color4f g_SquareColor3{ 226 / 255.0f, 87 / 255.0f, 98 / 255.0f, 0.5f};
const Color4f g_SquareColor4{ 226 / 255.0f, 237 / 255.0f, 98 / 255.0f,0.5f};

const float g_SquareSize{100};

Point2f g_GlobalPos{};

Point2f g_SquareBL1{};
Point2f g_SquareBL2{};
Point2f g_SquareBL3{};
Point2f g_SquareBL4{};

// Declare your own functions here
void DrawSquare1();
void DrawSquare2();
void DrawSquare3();
void DrawSquare4();
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
