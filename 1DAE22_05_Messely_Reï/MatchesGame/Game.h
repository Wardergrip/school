#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "MatchesGame - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
const Color4f g_Red{ 255 / 255.0f, 102 / 255.0f, 102 / 255.0f, 1 };
const Color4f g_Yellow{ 254 / 255.0f, 254 /255.0f, 101 /255.0f, 1};

std::string g_OpponentMoves{};
std::string g_UserMoves{};

const int g_Step{ 8 };
int g_Pile{ 21 };
int g_UserPile{0};
int g_OpponentPile{0};

bool g_UserTurn{ true };
bool g_SessionEnded{ false };
// Declare your own functions here
void DrawMatch(float bottom, float left);
void DrawMatch(Point2f bottomLeft);

void DrawPiles();
void UserTakesMatches(int amount);
void OpponentTakesMatches();
void CheckSession();
void EndSession();
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
