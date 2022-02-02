#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "FreeGame - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
#pragma region Colours
const Color4f g_White{ 1,1,1,1 };
const Color4f g_LightYellow{ 255 / 255.0f, 255 / 255.0f, 227 / 255.0f,1 };
const Color4f g_Yellow{ 255 / 255.0f, 255 / 255.0f, 227 /255.0f,1 };
const Color4f g_LightOrange{ 252 / 255.0f, 228 / 255.0f, 157 / 255.0f, 1};
const Color4f g_Orange{ 255 / 255.0f, 202 / 255.0f, 43 /255.0f, 1};
const Color4f g_DarkOrange{ 255 / 255.0f, 139 / 255.0f, 43 / 255.0f,1 };
const Color4f g_LightRed{ 255 / 255.0f, 153 / 255.0f, 153 / 255.0f,1 };
const Color4f g_Red{ 255 / 255.0f, 71 / 255.0f, 71 / 255.0f,1 };
const Color4f g_DarkRed{ 204 / 255.0f, 0, 0, 1 };
const Color4f g_Purple{ 236 / 255.0f, 116 / 255.0f, 242 / 255.0f,1 };
#pragma endregion Colours
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma region PaddleVars
const float g_PaddleWidth{ 20 };
const float g_PaddleHeight{ 80 };
const float g_PaddleSpeed{ 20 };

float g_FirstPaddleTranslation{};
float g_SecondPaddleTranslation{};

float g_FirstPaddleDirection{ 1 };
float g_SecondPaddleDirection{ 1 };

Point2f g_FirstPaddleBL{ 10, g_WindowHeight / 2 - g_PaddleHeight / 2 };
Point2f g_SecondPaddleBL{ g_WindowWidth - g_PaddleWidth - 10, g_WindowHeight / 2 - g_PaddleHeight / 2 };
#pragma endregion PaddleVars
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma region BallVars
const float g_BallRad{ 5 };
float g_BallSpeed{ 1 };
float g_BallSpeedIncrease{ 0.1f };
float g_BallXDirection{ 1 }, g_BallYDirection{ 1 };

Point2f g_BallCenterpoint{ g_WindowWidth / 2, g_WindowHeight / 2 };
Point2f g_BallTranslation{ 0,0 };
#pragma endregion BallVars
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool g_GamePaused{ false };
bool g_ViewDebugging{ false };
bool g_EnableSpeedIncrease{ true };

unsigned int g_ScoreP1{ 0 }, g_ScoreP2{ 0 };


// Declare your own functions here
void DrawDottedLine();
void DrawFirstPaddle();
void DrawSecondPaddle();
void MoveFirstPaddle(float direction);
void MoveSecondPaddle(float direction);
void DrawBall();
void CalculateBall();
void ShowInfo();
void ResetScore();

void DrawNumber(float x, float y, int number);
void DrawNumber(Point2f xy, int number);
Color4f SwitchBallColour(float speed);
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
