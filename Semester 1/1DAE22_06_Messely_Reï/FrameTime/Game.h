#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "FrameTime - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
unsigned int g_NumberOfFrames{ 0 };
float g_AccumulatedTime{ 0 };
float g_ElapsedSec{};

const float g_VerticalSpeed{ 80 };
const float g_HorizontalSpeed{ 100 };

Point2f g_BallPos{ g_WindowWidth / 2, g_WindowHeight / 2 };
bool g_IsGoingUp{ true };
bool g_IsGoingRight{ true };

Point2f g_BlockPos{ g_WindowWidth / 4, g_WindowHeight - 15};

const double g_Gravity{ -9.81 };
float g_PreviousVelocity{};
bool g_IsFalling{false};
// Declare your own functions here

void UpdateBall(float& x, float& y, float radius = 50);
void UpdateBall(Point2f& position, float radius = 50);

void DrawBall(float x, float y, float radius = 50);
void DrawBall(const Point2f& position, float radius = 50);

void UpdateFreeFall(float& x, float& y);
void UpdateFreeFall(Point2f& position);

void DrawFreeFall(float x, float y, float size = 10);
void DrawFreeFall(const Point2f& position, float size = 10);
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
