#include "pch.h"
#include "Game.h"
#include <iostream>

#include "Jonathan.h"
#include "Rei.h"


//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	InitMainMenu();
	InitGameOver();
	InitTileTextures();
	InitNumberTextures();

	InitWorldGrid();

	StartRei();
	StartJonathan();
}

void Draw()
{
	ClearBackground(53 / 255.0f, 152 / 255.0f, 219 /255.0f);
	
	// Put your own draw statements here
	SetColor(1, 1, 1, 1);
	// All game drawcalls
	if (!g_MainMenu)
	{
		// Must be drawn at the start so it ends up at the back
		DrawWorldGrid();
		//DrawSprite(g_BrownPilot, Point2f{ 100,100 });
		//DrawSprite(g_GreenPlane, Point2f{ 200,200 });
	
		// Must be drawn at the end so it ends up on top
		if (g_ShowGrid) DrawDebugGrid();
		
	}
	// All main menu drawcalls
	else
	{
		DrawMainMenu();
	}

	
	DrawJonathan();
	DrawRei();

	if (g_IsGameOver)
	{
		DrawGameOver();
	}

	// Fade
	if (g_Fade)
	{
		SetColor(g_FadeCol);
		FillRect(0, 0, g_WindowWidth, g_WindowHeight);
	}
}

void Update(float elapsedSec)
{
	// process input, do physics 

	// e.g. Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}

	// If we're out of mainMenu
	if (!g_MainMenu)
	{
		//UpdateSpriteAnimation(g_BrownPilot, elapsedSec);
		//UpdateSpriteAnimation(g_GreenPlane, elapsedSec);
		if (g_IsGameOver)
		{
			UpdateGameOver(elapsedSec);
		}
		Fade(g_FadeCol,g_FadeStep,g_MainMenu);
	}
	else
	{
		UpdateMainMenu();
		Fade(g_FadeCol, g_FadeStep, g_MainMenu);
	}

	UpdateRei(elapsedSec);
	UpdateJonathan(elapsedSec);
}

void End()
{
	// free game resources here
	DeleteTileTextures();
	DeleteNumberTextures();

	DeleteMainMenu();
	DeleteGameOver();
	DeleteWorldGrid();

	EndRei();
	EndJonathan();
	// Need to delete textures from Rotated folder
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{

}

void OnKeyUpEvent(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_g:
		if (!g_MainMenu) 
		{
			g_ShowGrid = !g_ShowGrid;
			std::cout << "DEBUG: Grid ";
			if (g_ShowGrid) std::cout << "ENABLED\n";
			else std::cout << "DISABLED\n";
		}
		break;
	case SDLK_i:
		ShowInfoInConsole();
		break;
	}
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	g_CurrentMousePos = Point2f{ float( e.x ), float( g_WindowHeight - e.y ) };
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	int tile{};
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		g_MousePosLMB = Point2f{ float(e.x), float(g_WindowHeight - e.y) };
		tile = GetTile(g_MousePosLMB);
		if (g_ShowGrid) std::cout << "Clicked on tile: " << tile << "\n";
		if (g_ShowGrid) GetWorldTileInfo(tile);
		g_MousePosLMBClicking = true;
		break;
	case SDL_BUTTON_RIGHT:
		g_MousePosRMB = Point2f{ float(e.x), float(g_WindowHeight - e.y) };
		break;
	}
}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		g_MousePosLMBClicking = false;
		break;
	}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here

void ShowInfoInConsole()
{
	std::cout << "\n== Welcome to TD Showdown! ==\n"
	   	    << " OBJECTIVE\n"
		    << " - Your goal is to survive as long as possible\n"
		    << " - You use money to buy new towers\n"
		    << " CONTROLS\n"
			<< " - Press I to see info\n"
			<< " - Press G to see grid and debug info\n"
			<< " - Click and drag to buy towers\n"
			<< " MADE BY\n"
			<< " Jonathan Menschaert [GD22N]\n"
			<< " Reï Messely [GD22N]\n"
			<< '\n';
	std::cout << '\n';
}

// Initialises mainmenu textures
void InitMainMenu()
{
	bool success{};
	std::string path{ "Resources/Fonts/Kenney Blocks.ttf" };

	success = TextureFromString("TD Showdown", path, 34, Color4f{ 1,1,1,1 }, g_TitleText.texture);
	if (g_ShowInitMsgs) if (success) std::cout << "Successfully loaded " << path << "\n";
	else std::cout << "Failed to load " << path << "\n";

	success = TextureFromString("Start", path, 26, Color4f{ 1,1,1,1 }, g_StartText.texture);
	if (g_ShowInitMsgs) if (success) std::cout << "Successfully loaded " << path << "\n";
	else std::cout << "Failed to load " << path << "\n";

	path = "Resources/UI/yellow_button00.png";
	success = TextureFromFile(path, g_LongButtonTexture);
	if (g_ShowInitMsgs) if (success) std::cout << "Successfully loaded " << path << "\n";
	else std::cout << "Failed to load " << path << "\n";

	path = "Resources/UI/yellow_button01.png";
	success = TextureFromFile(path, g_LongButtonPressedTexture);
	if (g_ShowInitMsgs) if (success) std::cout << "Successfully loaded " << path << "\n";
	else std::cout << "Failed to load " << path << "\n";

	g_StartButton.texture = g_LongButtonTexture;

	Point2f startButtonPoint{ g_WindowWidth / 2, g_WindowHeight / 2 };
	Point2f titlePoint{ g_WindowWidth / 2 ,(3 * g_WindowHeight) / 4 };
	InitUI(g_StartButton, g_MainMenuScale, startButtonPoint);
	InitUI(g_TitleText, g_MainMenuScale, titlePoint);
	InitUI(g_StartText, g_MainMenuScale, startButtonPoint);
}

void InitGameOver()
{
	bool success{};
	std::string path{ "Resources/Fonts/Kenney Blocks.ttf" };

	success = TextureFromString("Game Over!", path, 34, Color4f{ 1,1,1,1 }, g_GameOverText.texture);
	if (g_ShowInitMsgs) if (success) std::cout << "Successfully loaded " << path << "\n";
	else std::cout << "Failed to load " << path << "\n";

	Point2f gameOverTextPoint{ g_WindowWidth / 2 ,(3 * g_WindowHeight) / 4 };
	InitUI(g_GameOverText, g_MainMenuScale, gameOverTextPoint);
}

// Draws all elements of the main menu.
void DrawMainMenu()
{
	DrawTexture(g_TitleText.texture, g_TitleText.destRectf, g_TitleText.srcRectf);
	DrawTexture(g_StartButton.texture, g_StartButton.destRectf, g_StartButton.srcRectf);
	DrawTexture(g_StartText.texture, g_StartText.destRectf, g_StartText.srcRectf);
}

//Draws Game over menu
void DrawGameOver()
{
	SetColor(0.5f, 0.5f, 0.5f, 0.8f);
	FillRect(0, 0, g_WindowWidth, g_WindowHeight);
	DrawTexture(g_GameOverText.texture, g_GameOverText.destRectf, g_GameOverText.srcRectf);
}

// Checks for button clicks.
void UpdateMainMenu()
{
	if (IsInsideRect(g_StartButton.destRectf, g_MousePosLMB) && !g_Fade)
	{
		if (g_ShowButtonMsgs) std::cout << "Clicked start\n";
		// Reset mousepos
		g_MousePosLMB = Point2f{ 0,0 };
		g_StartButton.texture = g_LongButtonPressedTexture;
		InitUI(g_StartButton, g_MainMenuScale, Point2f{ g_WindowWidth / 2, g_WindowHeight / 2 });
		g_Fade = true;
	}
}

void UpdateGameOver(float elapsedSec)
{
	g_GameOverTime += elapsedSec;
	if (g_GameOverTime >= g_MaxGameOverTime)
	{
		ResetBoughtTowers();
		g_GameOverTime = 0;
		InitPlayer();
		g_WaveController.waveNr = 0;
		g_IsGameOver = false;
		g_MainMenu = true;
	}
}

// Overloaded function, Draws the worldtile with respective dest- and srcRect
void DrawTexture(WorldTile worldTile)
{
	DrawTexture(worldTile.texture, worldTile.destRectf, worldTile.srcRectf);
}
// Loads all .png files from 001 - 299
void InitTileTextures()
{
	bool success{};
	std::string path{};
	g_pTileTextures = new Texture[g_TileTextureAmount];
	// Starting from 001 since 000 doesn't exist
	for (int i{ 1 }; i < g_TileTextureAmount; ++i) 
	{
		path = "Resources/PNG/towerDefense_tile";
		if (i < 10) path = path + "00";
		else if (i < 100) path = path + "0";
		path = path + std::to_string(i) + ".png";
		success = TextureFromFile(path, g_pTileTextures[i]);
		if (g_ShowInitMsgs) if (success) std::cout << "Successfully loaded " << path << "\n";
		else std::cout << "Failed to load " << path << "\n";
	}
}
// Deletes all tile textures from 001-299
void DeleteTileTextures()
{
	for (int i{ 0 }; i < g_TileTextureAmount; ++i)
	{
		DeleteTexture(g_pTileTextures[i]);
	}
	delete[] g_pTileTextures;
	g_pTileTextures = nullptr;
}

// Deletes all number textures
void DeleteNumberTextures()
{
	for (int i{ 0 }; i < g_AmountOfNumberText; ++i)
	{
		DeleteTexture(g_pNumberTextures[i]);
	}
	delete[] g_pNumberTextures;
	g_pNumberTextures = nullptr;
}

// Initialises the g_NumberTextures array of all textures that contain a number.
// Use g_NumberTextures[i] with i being your number to get the number texture.
void InitNumberTextures()
{
	g_pNumberTextures = new Texture[g_AmountOfNumberText];
	const int startIdx{276};
	for (int i{ 0 }; i < g_AmountOfNumberText; i++)
	{
		g_pNumberTextures[i] = g_pTileTextures[startIdx + i];
		if (g_ShowInitMsgs) std::cout << "Copied TileTexture[" << (startIdx + i) << "] to NumberTextures[" << i << "]\n";
	}
}
// Initialises the world grid.
// Defines: srsRect, defaultTexture and destRectf
void InitWorldGrid()
{
	WorldTile defaultTile{};
	defaultTile.direction = Direction::none;
	defaultTile.texture = g_pTileTextures[int(TileType::grass)];
	defaultTile.tile = TileType::grass;
	defaultTile.srcRectf.width = defaultTile.texture.width;
	defaultTile.srcRectf.height = defaultTile.texture.height;
	defaultTile.srcRectf.bottom = defaultTile.srcRectf.height;

	g_pWorldTiles = new WorldTile[g_WorldTileAmount];
	for (int i{ 0 }; i < g_WorldTileAmount; i++)
	{
		g_pWorldTiles[i] = defaultTile;
	}
	for (int i{ 0 }; i < g_WorldTileAmountRow; i++)
	{
		for (int j{ 0 }; j < g_WorldTileAmountCol; j++)
		{
			const int idx{ GetIndex(i, j, g_WorldTileAmountCol) };
			g_pWorldTiles[idx].destRectf.width = defaultTile.srcRectf.width * g_WorldTilescale;
			g_pWorldTiles[idx].destRectf.height = defaultTile.srcRectf.height * g_WorldTilescale;
			g_pWorldTiles[idx].destRectf.left = j * defaultTile.srcRectf.width * g_WorldTilescale;
			g_pWorldTiles[idx].destRectf.bottom = i * defaultTile.srcRectf.height * g_WorldTilescale;
		}
	}
}

void DeleteWorldGrid()
{
	for (int i{ 0 }; i < g_WorldTileAmount; i++)
	{
		DeleteTexture(g_pWorldTiles[i].texture);
	}
	delete[] g_pWorldTiles;
	g_pWorldTiles = nullptr;
}

void DeleteMainMenu()
{
	DeleteTexture(g_TitleText.texture);
	DeleteTexture(g_StartText.texture);
	DeleteTexture(g_LongButtonTexture);
	DeleteTexture(g_LongButtonPressedTexture);
	DeleteTexture(g_StartButton.texture);
}

void DeleteGameOver()
{
	DeleteTexture(g_GameOverText.texture);
}

// Draws a grid to show where tiles start and end.
// Default key G to activate.
void DrawDebugGrid()
{
	SetColor(0.4f, 0.4f, 0.4f, 1);
	for (int i{ 0 }; i < g_WorldTileAmountRow; i++)
	{
		for (int j{ 0 }; j < g_WorldTileAmountCol; j++)
		{
			DrawLine(Point2f{ j * g_pWorldTiles[0].destRectf.width,0 }, Point2f{ j * g_pWorldTiles[0].destRectf.width, g_WindowHeight });
			DrawLine(Point2f{ 0,i * g_pWorldTiles[0].destRectf.height }, Point2f{g_WindowWidth, i * g_pWorldTiles[0].destRectf.height });
		}
	}
}
// Draws the world grid.
void DrawWorldGrid()
{
	for (int i{ 0 }; i < g_WorldTileAmount; i++)
	{
		DrawTexture(g_pWorldTiles[i]);
	}
}
// Returns the index of the tile that has been clicked or hovered.
// WILL RETURN 0 IN CASE NONE HAS BEEN CLICKED OR HOVERED.
int GetTile(const Point2f& position)
{
	for (int i{0}; i < g_WorldTileAmount; i++)
	{
		if (IsInsideRect(g_pWorldTiles[i].destRectf, position))
		{
			return i;
		}
	}
	return 0;
}
// Displays all possible info of the WorldTile in the debug.
void GetWorldTileInfo(int idx)
{
	if ((idx < g_WorldTileAmount) && (idx > -1))
	{
		std::cout << "TileNr: " << idx << std::endl;
		std::cout << "	TextureWidth " << g_pWorldTiles[idx].texture.width << std::endl;
		std::cout << "	TextureHeight " << g_pWorldTiles[idx].texture.height << std::endl;

		std::cout << "	srcRectfLeft " << g_pWorldTiles[idx].srcRectf.left << std::endl;
		std::cout << "	srcRectfBottom " << g_pWorldTiles[idx].srcRectf.bottom << std::endl;
		std::cout << "	srcRectfWidth " << g_pWorldTiles[idx].srcRectf.width << std::endl;
		std::cout << "	srcRectfHeight " << g_pWorldTiles[idx].srcRectf.height << std::endl;

		std::cout << "	destRectfLeft " << g_pWorldTiles[idx].destRectf.left << std::endl;
		std::cout << "	destRectfBottom " << g_pWorldTiles[idx].destRectf.bottom << std::endl;
		std::cout << "	destRectfWidth " << g_pWorldTiles[idx].destRectf.width << std::endl;
		std::cout << "	destRectfHeight " << g_pWorldTiles[idx].destRectf.height << std::endl;

		std::cout << "	Direction " << int(g_pWorldTiles[idx].direction) << std::endl;
	}
	else 
	{
		std::cout << "WorldTileInfo out of bounds.\n";
	}
}
// Fades a color from alpha 0 to 1 back to 0. Enable g_Fade to start, Fade() will disable itself.
void Fade(Color4f& fadeCol, float& fadeSpeed, bool& transitionTo)
{
	if (g_Fade)
	{
		fadeCol.a += fadeSpeed;
		if (fadeCol.a >= 1)
		{
			fadeCol.a = 1;
			fadeSpeed = -fadeSpeed;
			transitionTo = false;
			if(g_ShowFadeMsgs) std::cout << "Decreasing\n";
		}
		else if (g_FadeCol.a <= 0)
		{
			g_Fade = false;
			fadeSpeed = abs(fadeSpeed);
		}
		if (g_ShowFadeMsgs) std::cout << "Current Fade alpha: " << fadeCol.a << "\n";
	}
}
// Initialises the UserInterface srcRectf and destRectf. Do the texture manually. 
void InitUI(UserInterface& UI, float scale, const Point2f& middlePoint)
{
	UI.srcRectf.width = UI.texture.width;
	UI.srcRectf.height = UI.texture.height;
	UI.srcRectf.bottom = UI.srcRectf.height;
	UI.destRectf.width = UI.srcRectf.width * scale;
	UI.destRectf.height = UI.srcRectf.height * scale;
	UI.destRectf.left = middlePoint.x - UI.destRectf.width / 2;
	UI.destRectf.bottom = middlePoint.y - UI.destRectf.height / 2;
}

void DrawSprite(Sprite& sprite, const Point2f& bottomLeft, float scale)
{
	Rectf srcRect{};
	srcRect.width = sprite.texture.width / sprite.cols;
	srcRect.height = sprite.texture.height;
	srcRect.left = sprite.currentFrame * srcRect.width;
	srcRect.bottom = srcRect.height;

	Rectf destRect{};
	destRect.left = bottomLeft.x;
	destRect.bottom = bottomLeft.y;
	destRect.width = srcRect.width * scale;
	destRect.height = srcRect.height * scale;

	DrawTexture(sprite.texture, destRect, srcRect);
}
void UpdateSpriteAnimation(Sprite& sprite, float elapsedSec)
{
	sprite.accumulatedTime += elapsedSec;
	if (sprite.accumulatedTime > sprite.frameTime)
	{
		++sprite.currentFrame %= sprite.frames;
		sprite.accumulatedTime -= sprite.frameTime;
	}
}
#pragma endregion ownDefinitions