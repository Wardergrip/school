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

struct OxoTile
{
	Texture texture{};
	Rectf rect{};
};

const int g_TileAmount{ 9 }; 
OxoTile g_OxoTiles[g_TileAmount];
OxoTile g_PlayerTiles[2];
// Declare your own functions here
void InitFiles();
void DeleteTextures();
void DrawTexture(OxoTile oxoTile);

void InitOxoGrid();
void DrawOxoGrid();

void InitPlayers();
void DrawPlayers();
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
