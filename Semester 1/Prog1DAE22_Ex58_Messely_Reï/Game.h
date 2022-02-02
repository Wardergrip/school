#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Ex58 - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
const std::string g_BackgroundTexturePath{ "Resources/street.PNG" };
Texture g_BackgroundTexture;

const std::string g_PlayerTexturePath{ "Resources/Chicken.bmp" };
Texture g_PlayerTexture;
Point2f g_PlayerPos{ g_WindowWidth / 2, g_WindowHeight - 20 };
const float g_PlayerSpeed{ 100 };
Rectf g_PlayerDstRect{};
Rectf g_PlayerSrcRect{};

const float g_TrottoirBorder{ 43 };

const std::string g_TextPath{ "Resources/consola.ttf" };
const int g_TextSize{ 40 };

const Color4f g_BoxCol{ 0, 0, 0, 0.5f };

const std::string g_WinningText{ "The Chicken survived!" };
Texture g_WinningTextTexture;

const std::string g_LosingText{ "The Chicken died." };
Texture g_LosingTextTexture;

const std::string g_PausingText{ "Paused" };
Texture g_PausingTextTexture;

enum class GameState
{
	reset,
	spelen,
	pauzeren,
	winnen,
	verliezen
};
GameState g_GameState{ GameState::spelen };

enum class PlayerDirection
{
	neutral,
	down,
	left,
	right
};
PlayerDirection g_PlayerDirection{ PlayerDirection::down };

class Vehicle; // Class forward declaration
const int g_AmountOfVehicles{ 5 };
Vehicle* g_Vehicles[g_AmountOfVehicles];

// Declare your own functions here
void InitTextures();
void UpdatePlayer();
void MovePlayer(PlayerDirection pd, float elapsedSec);
void ShowInfo();
void InitVehicles();
void Shuffle(int* pArray, int size, int swaps);

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
