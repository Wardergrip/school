#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "EventsAndDrawing - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
const Color4f g_Gray{0.5f,0.5f,0.5f,1.0f};
const Color4f g_Green{ 0.0f,1.0f,0.0f,1.0f };
const Color4f g_White{ 1.0f,1.0f,1.0f,1.0f };
Color4f g_SqrColor{ g_Gray };

const float g_BorderDistance{50};
const float g_SqrW{ 60 };
const float g_SqrH{ 40 };
const float g_BouncingLineSpeed{ 1 };
float g_Movement{ 0 };
float g_MovementPlus{ 0 };
float g_BoundingLineLength{};

Point2f g_BouncingLineMid{ 1, g_WindowHeight / 2 };
Point2f g_SqrPos{};
Point2f g_MousePos{};

bool g_IsGreen{ false };
int g_BouncingLineDirection{1}; // 1 = right, -1 = left
int g_BouncingLineLength{ 10 };
int g_BouncingLineGrowing{ 1 };

/* not my code but too cool to delete
Point2f g_BouncingPoint1{};
Point2f g_BouncingPoint1Vel{};
Point2f g_BouncingPoint2{};
Point2f g_BouncingPoint2Vel{};
*/
enum class SpecialState
{
	none, running, bouncing
};
SpecialState g_SpecialState{ SpecialState::none };
// Declare your own functions here
void DrawRandomRect();
void RandomiseCoords();
void DrawBouncingLine();

// void DrawBouncingLines(); not my code but too cool to delete
// void UpdateBouncingLines(float elapsedSec);
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
