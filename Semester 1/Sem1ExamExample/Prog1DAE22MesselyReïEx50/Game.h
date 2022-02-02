#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Ex50 - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
class Tile;
bool g_IsGameFinished{ false };
const float g_TileWidth{ 128 };
const float g_TileHeight{ 128 };
const int g_AmountOfRows{ 2 };
const int g_AmountOfCols{ 2 };

Tile* g_TileGame[g_AmountOfRows*g_AmountOfCols];
const Point2f g_TileGamePos{ 130,168 };
Texture g_Names{};
int g_FinishedAnimal{ 0 };

// Declare your own functions here
void InitTileGame(const Point2f& topLeft);
void DrawTileGame();
void CheckTileGameFinished();

void DrawNames();
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
