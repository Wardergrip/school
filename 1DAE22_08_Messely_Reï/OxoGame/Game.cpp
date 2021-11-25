#include "pch.h"
#include "Game.h"

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	InitFiles();
	InitOxoGrid();
	InitPlayers();
}

void Draw()
{
	ClearBackground();

	// Put your own draw statements here
	
	// Background
	DrawTexture(g_OXOTxt, Rectf{ 0,0,g_WindowWidth,g_WindowHeight });
	// 
	DrawOxoGrid();
	DrawPlayers();

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
}

void End()
{
	// free game resources here
	DeleteTextures();
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{

}

void OnKeyUpEvent(SDL_Keycode key)
{
	//switch (key)
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{

}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	////std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//switch (e.button)
	//{
	//case SDL_BUTTON_LEFT:
	//{
	//	//std::cout << "Left mouse button released\n";
	//	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
	//	break;
	//}
	//case SDL_BUTTON_RIGHT:
	//	//std::cout << "Right mouse button released\n";
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	//std::cout << "Middle mouse button released\n";
	//	break;
	//}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here
void InitFiles()
{
	TextureFromFile("Resources/FreeCell.png", g_FreeCellTxt);
	TextureFromFile("Resources/GreenO.png", g_GreenOTxt);
	TextureFromFile("Resources/GreenX.png", g_GreenXTxt);
	TextureFromFile("Resources/OXO.png", g_OXOTxt);
	TextureFromFile("Resources/WhiteO.png", g_WhiteOTxt);
	TextureFromFile("Resources/WhiteX.png", g_WhiteXTxt);
	TextureFromFile("Resources/Win.png", g_WinTxt);
}
void DeleteTextures()
{
	DeleteTexture(g_FreeCellTxt);
	DeleteTexture(g_GreenOTxt);
	DeleteTexture(g_GreenXTxt);
	DeleteTexture(g_OXOTxt);
	DeleteTexture(g_WhiteOTxt);
	DeleteTexture(g_WhiteXTxt);
	DeleteTexture(g_WinTxt);
	for (int i{ 0 }; i < g_TileAmount; i++)
	{
		DeleteTexture(g_OxoTiles[i].texture);
	}
	DeleteTexture(g_PlayerTiles[0].texture);
	DeleteTexture(g_PlayerTiles[1].texture);
}
void DrawTexture(OxoTile oxoTile)
{
	DrawTexture(oxoTile.texture, oxoTile.rect);
}

void InitOxoGrid()
{
	const float size{ 60 };
	const Point2f bottomLeftGrid{g_WindowWidth / 2 - 1.5f*size, g_WindowHeight / 2 - 1.5f * size };
	const float spaceBetween{ 3 };
	const float sqrtAmountf{ float(sqrt(g_TileAmount)) };
	const int sqrtAmounti{ int(sqrt(g_TileAmount)) };
	
	for (int i{ 0 }; i < g_TileAmount; i++)
	{
		g_OxoTiles[i].rect.width = size;
		g_OxoTiles[i].rect.height = size;
		g_OxoTiles[i].texture = g_FreeCellTxt;
	}
	for (int i{ 0 }; i < sqrtAmounti; i++)
	{
		for (int j{ 0 }; j < sqrtAmounti; j++)
		{
			g_OxoTiles[GetIndex(i, j, sqrtAmounti)].rect.left = bottomLeftGrid.x + j * size + j * spaceBetween;
			g_OxoTiles[GetIndex(i, j, sqrtAmounti)].rect.bottom = bottomLeftGrid.y + i * size + i * spaceBetween;
		}
	}
}
void DrawOxoGrid()
{
	for (int i{ 0 }; i < g_TileAmount; i++)
	{
		DrawTexture(g_OxoTiles[i]);
	}
}

void InitPlayers()
{
	const float size{ 60 };
	const float border{ 20 };

	g_PlayerTiles[0].rect.width = size;
	g_PlayerTiles[0].rect.height = size;
	g_PlayerTiles[0].rect.left = border;
	g_PlayerTiles[0].rect.bottom = border;

	g_PlayerTiles[1].rect.width = size;
	g_PlayerTiles[1].rect.height = size;
	g_PlayerTiles[1].rect.left = g_WindowWidth - border - size;
	g_PlayerTiles[1].rect.bottom = border;

	g_PlayerTiles[0].texture = g_GreenOTxt;
	g_PlayerTiles[1].texture = g_WhiteOTxt;
}
void DrawPlayers()
{
	DrawTexture(g_PlayerTiles[0]);
	DrawTexture(g_PlayerTiles[1]);
}
#pragma endregion ownDefinitions