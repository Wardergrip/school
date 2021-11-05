#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "QweekExample - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 200 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
int g_Even{};
int g_Odd{};
int g_Any{};

float g_Timer{};
float g_PreviousTimer{};
float g_ElapsedSec{};

const float g_ElevatorTotalWidth{ 40 };
const float g_ElevatorTotalHeight{ 60 };
const float g_ElevatorWallThickness{ 10 };

const float g_Border{30};
const float g_Speed{100};

enum class ElevatorDirection 
{
	idle, up, down
};
ElevatorDirection g_Direction{ ElevatorDirection::idle };
ElevatorDirection g_PreviousDirection{ ElevatorDirection::up };

Point2f g_ElevatorPos{g_WindowWidth - g_Border - g_ElevatorTotalWidth, g_Border};

const Color4f g_IdleColour{ 51 / 255.0f, 51 / 255.0f, 51 / 255.0f, 1.0f };
const Color4f g_UpColour{ 1.0f, 0, 0, 1.0f };
const Color4f g_DownColour{ 0 , 1.0f, 0, 1.0f };
// Declare your own functions here
void Generate();
void PrintRandomNumbers();

void DrawElevator(float x, float y, ElevatorDirection direction);
void DrawElevator(Point2f xy, ElevatorDirection direction);

void SwitchMovement();
void CalculateMovement();
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
