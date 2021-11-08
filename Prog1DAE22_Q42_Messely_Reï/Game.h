#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Qweek - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
enum class CircleState
{
	growing, shrinking, waiting
};
CircleState g_CircleState{CircleState::waiting};

int g_MaxRadius{ 150 };
int g_MinRadius{ 50 };

float g_NewRadius{};
float g_CurrentRadius{};
float g_PreviousRadius{};
Color4f g_NewColor{};
Color4f g_CurrentColor{};
Color4f g_PreviousColor{};
const Color4f g_ErrorColor{ 1,0,0,1 };

Point2f g_NewPos{};
Point2f g_CirclePos{};

double g_Speed{1.0};
const double g_Step{ 0.4 };
// Declare your own functions here
void PrintLetters();
bool IsHittingBorder();
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
