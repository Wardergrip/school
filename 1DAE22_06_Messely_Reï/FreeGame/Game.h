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
enum class Direction
{
	up = 1,
	right = 1,
	down = -1,
	left = -1,
};
Direction g_LeftRight{ Direction::right };
Direction g_UpDown{ Direction::up };

const float g_PlatformLength{100};
const float g_PlatformHeight{ 10 };
Point2f g_PlatformPos{ g_WindowWidth / 2, 20 };

const float g_MainBallRadius{ 5 };
const float g_MainBallVelocity{ 100 };
Point2f g_MainBallPos{ g_PlatformPos.x, g_PlatformPos.y + (g_PlatformHeight / 2) + g_MainBallRadius };

// Declare your own functions here
void DrawPlatform(float x, float y, float totLength, float totHeight);
void DrawPlatform(const Point2f& midPos, float totLength, float totHeight);

void DrawBall(float x, float y, float r);
void DrawBall(const Point2f& pos, float r);
void UpdateBall(float& x, float& y, float r, float velocity, float elapsedSec);
void UpdateBall(Point2f& pos, float r, float velocity, float elapsedSec);
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
