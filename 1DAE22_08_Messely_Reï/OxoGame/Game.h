#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "OxoGame - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here

Texture g_FreeCellTxt;
Texture g_GreenOTxt;
Texture g_GreenXTxt;
Texture g_OXOTxt;
Texture g_WhiteOTxt;
Texture g_WhiteXTxt;
Texture g_WinTxt;

enum class Player
{
	none,
	player0,
	player1
};
enum class Placing
{
	none,
	x,
	o,
	win
};

struct OxoTile
{
	Texture texture{};
	Rectf rect{};
	Player player{ Player::none };
	Placing placed{ Placing::none };
};

const int g_TileAmount{ 9 };
OxoTile g_OxoTiles[g_TileAmount];
OxoTile g_PlayerTiles[2];

Player g_Turn{ Player::player0 };
Placing g_Player0Placing{ Placing::o };
Placing g_Player1Placing{ Placing::o };

// Declare your own functions here
void InitFiles();
void DeleteTextures();
void DrawTexture(OxoTile oxoTile);

void InitOxoGrid();
void DrawOxoGrid();

void InitPlayers();
void DrawPlayers();

void UpdateIsPlacing(Player player = Player::none);
void UpdateOxoGrid(const Point2f mousePos, Player player);
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
