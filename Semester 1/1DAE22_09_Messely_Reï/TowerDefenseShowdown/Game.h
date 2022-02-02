#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "TowerDefenseShowDown - Messely, Reï & Menschaert, Jonathan - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 1280 };
float g_WindowHeight{ 700 };
#pragma endregion gameInformation

#pragma region ownDeclarations
// Declare your own global variables here

bool g_MainMenu{ true };

// The following bools are for console debugging purposes
const bool g_ShowInitMsgs{ false };
const bool g_ShowButtonMsgs{ false };
const bool g_ShowFadeMsgs{ false };


// The following bools are for visual debugging purposes
bool g_ShowGrid{ false };

struct UserInterface
{
	Texture texture{};
	Rectf destRectf{};
	Rectf srcRectf{};
};
enum class Direction 
{
	none,
	start,
	end,
	right,
	up,
	left,
	down
};

enum class TileType
{
	grass = 24,
	borderBottomRightOutside = 69,
	borderMiddleBottom = 70,
	borderBottomLeftOutside = 71,
	borderTopLeftInside = 72,
	borderTopRightInside = 73,
	pathEnd = 91,
	borderMiddleLeft = 92,
	dirt = 93,
	borderMiddleRight = 94,
	borderBottomLeftInside = 95,
	borderBottomRightInside = 96,
	borderTopRightOutside = 115,
	borderMiddleTop = 116,
	borderTopLeftOutside = 117,
	towerBase = 180
};

struct WorldTile
{
	Texture texture{};
	Rectf destRectf{};
	Rectf srcRectf{};
	Direction direction{};
	TileType tile{};
};
struct Sprite
{
	Texture texture;
	int frames;
	int cols;
	float frameTime;
	int currentFrame;
	float accumulatedTime;
};



// MousePos
Point2f g_CurrentMousePos{};
Point2f g_MousePosLMB{};
Point2f g_MousePosRMB{};
bool g_MousePosLMBClicking{ false };

// Textures
Texture g_LongButtonTexture{};
Texture g_LongButtonPressedTexture{};
// UI
const float g_MainMenuScale{ 2 };
UserInterface g_TitleText{};
UserInterface g_StartButton{};
UserInterface g_StartText{};

UserInterface g_GameOverText{};
UserInterface g_WaveAmountText{};

bool g_IsPlayPressed{ false };

//
int g_TileTextureAmount{ 300 };
Texture* g_pTileTextures{ nullptr };
int g_AmountOfNumberText{ 10 };
Texture* g_pNumberTextures{ nullptr };

// WorldTile
const float g_WorldTilescale{ 1 };
const int g_WorldTileAmountRow{ 11 };
const int g_WorldTileAmountCol{ 20 };
//
const int g_WorldTileAmount{ g_WorldTileAmountRow * g_WorldTileAmountCol };
WorldTile* g_pWorldTiles{ nullptr };

// Fade
bool g_Fade{ false };
float g_FadeStep{ 0.01f };
Color4f g_FadeCol{ 0,0,0,0 };

// Game Over
float g_MaxGameOverTime{5.f};
float g_GameOverTime{};
bool g_IsGameOver{ false };

////Player default variables
//const float g_Health{ 100 };
//const int g_Coins{ 20 };


// Declare your own functions here

void ShowInfoInConsole();

void InitMainMenu();
void DrawMainMenu();
void InitGameOver();
void DrawGameOver();
void UpdateMainMenu();
void UpdateGameOver(float elapsedSec);

void DrawTexture(WorldTile worldTile); 

void InitTileTextures();
void InitNumberTextures();
void DeleteTileTextures();
void DeleteNumberTextures();

void InitWorldGrid();
void DeleteWorldGrid();
void DrawDebugGrid();
void DrawWorldGrid();

void DeleteMainMenu();
void DeleteGameOver();

int GetTile(const Point2f& position);
void GetWorldTileInfo(int idx);
void Fade(Color4f& fadeCol, float& fadeSpeed, bool& transitionTo);

void InitUI(UserInterface& UI, float scale, const Point2f& middlePoint);

void DrawSprite(Sprite& sprite, const Point2f& bottomLeft, float scale = 1);
void UpdateSpriteAnimation(Sprite& sprite, float elapsedSec);
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
