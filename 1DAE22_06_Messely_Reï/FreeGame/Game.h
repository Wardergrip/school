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

Point2f g_MousePos{};
Point2f g_ClickedMousePos{};

enum class Direction
{
	up = 1,
	right = 1,
	down = -1,
	left = -1,
};

#pragma region Colors
const Color4f g_SoftBlue{ 0.8f, 0.8f, 1, 1 };
const Color4f g_SoftGreen{ 0.8f, 1, 0.8f,1 };
const Color4f g_SoftPink{ 1, 0.8f, 0.8f, 1 };
const Color4f g_SoftYellow{ 1,1,0.8f,1 };
#pragma endregion
#pragma region Platform
const float g_PlatformLength{ 100 };
const float g_PlatformHeight{ 10 };
Point2f g_PlatformPos{ g_WindowWidth / 2, 20 };
Rectf g_PlatformRect{};
#pragma endregion
#pragma region MainBall
const float g_MainBallRadius{ 5 };
const float g_MainBallVelocity{ 200 };
Point2f g_MainBallPos{ g_PlatformPos.x, g_PlatformPos.y + (g_PlatformHeight / 2) + g_MainBallRadius };
bool g_MainBallFreeze{ true };
Direction g_MainBallLeftRight{ Direction::right };
Direction g_MainBallUpDown{ Direction::up };
#pragma endregion
#pragma region Blocks
const unsigned int g_AmountOfBoxes{ 144 };
struct BreakableBox
{
	Rectf rect;
	bool isVisible;
};
BreakableBox g_Boxes[g_AmountOfBoxes];
#pragma endregion

#pragma region SettingsVars
bool g_ShowDebugging{ false };
bool g_IsMainMenuActive{ true };
int g_Lives{ 3 };
float g_PassedTime{0};
#pragma endregion


// Declare your own functions here
void DrawPlatform(float x, float y, float totLength, float totHeight);
void DrawPlatform(const Point2f& midPos, float totLength, float totHeight);

void DrawBall(float x, float y, float r);
void DrawBall(const Point2f& pos, float r);

void UpdateBall(float& x, float& y, float r, float velocity, float elapsedSec, Direction& upDown, Direction& leftRight);
void UpdateBall(Point2f& pos, float r, float velocity, float elapsedSec, Direction& upDown, Direction& leftRight);

void DestroyBall(float x, float y);
void DestroyBall(Point2f& pos);

void UpdatePlatform(Rectf& rect, const Point2f& ballPos, Direction& upDown, Direction& leftRight);

void UpdateBox(BreakableBox& box, const Point2f& ballPos, Direction& upDown, Direction& leftRight);

void HideBox(BreakableBox& box);

void DrawMainMenu();

void InitialiseBoxes();

void ShowInfo();

#pragma endregion ownDeclarations

#pragma region JonasSamynText
void TextCheckColor(int color);
void FontLoader(char character, Point2f location, float width, float height, int color);
void FontLoader(char character, float x, float y, float width, float height, int color);
void LetterDrawer(int array[], float width, float height, Point2f location);
#pragma endregion JonasSamynText

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
