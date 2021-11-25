#include "pch.h"
#include "Game.h"
#include <iostream>

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
	UpdateIsPlacing(Player::player0);
	UpdateIsPlacing(Player::player0);
	UpdateIsPlacing(Player::player1);
	UpdateIsPlacing(Player::player1);
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
	switch (key)
	{
	case SDLK_a:
		UpdateIsPlacing(Player::player0);
		break;
	case SDLK_i:
		UpdateIsPlacing(Player::player1);
		break;
	case SDLK_s:
		switch (g_Turn)
		{
		case Player::player0:
			g_Turn = Player::player1;
			break;
		case Player::player1:
			g_Turn = Player::player0;
			break;
		}
		break;
	}
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
	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
	{
		//std::cout << "Left mouse button released\n";
		UpdateOxoGrid(Point2f{ float( e.x ), float( g_WindowHeight - e.y ) },g_Turn);
		break;
	}
	}
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
		g_OxoTiles[i].player = Player::none;
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
	switch (g_Turn)
	{
	case Player::player0:
		for (int i{ 0 }; i < g_TileAmount; i++)
		{
			if (g_OxoTiles[i].player == Player::player0)
			{
				if (g_OxoTiles[i].placed == Placing::x) g_OxoTiles[i].texture = g_GreenXTxt;
				else if (g_OxoTiles[i].placed == Placing::o) g_OxoTiles[i].texture = g_GreenOTxt;
				else std::cout << "DrawOxoGrid Error: 0\n";
			}
			else
			{
				switch (g_OxoTiles[i].placed)
				{
				case Placing::o:
					g_OxoTiles[i].texture = g_WhiteOTxt;
					break;
				case Placing::x:
					g_OxoTiles[i].texture = g_WhiteXTxt;
					break;
				}
			}
		}
		break;
	case Player::player1:
		for (int i{ 0 }; i < g_TileAmount; i++)
		{
			if (g_OxoTiles[i].player == Player::player1)
			{
				if (g_OxoTiles[i].placed == Placing::x) g_OxoTiles[i].texture = g_GreenXTxt;
				else if (g_OxoTiles[i].placed == Placing::o) g_OxoTiles[i].texture = g_GreenOTxt;
				else std::cout << "DrawOxoGrid Error: 1\n";
			}
			else
			{
				switch (g_OxoTiles[i].placed)
				{
				case Placing::o:
					g_OxoTiles[i].texture = g_WhiteOTxt;
					break;
				case Placing::x:
					g_OxoTiles[i].texture = g_WhiteXTxt;
					break;
				}
			}
		}
		break;
	}
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
void UpdateIsPlacing(Player player)
{
	Texture x{}, o{};
	if (g_Turn == player)
	{
		x = g_GreenXTxt;
		o = g_GreenOTxt;
	}
	else
	{
		x = g_WhiteXTxt;
		o = g_WhiteOTxt;
	}

	switch (player)
	{
	case Player::none:
		break;
	case Player::player0:
		switch (g_Player0Placing)
		{
		case Placing::none:
			break;
		case Placing::x:
			g_PlayerTiles[0].texture = o;
			g_Player0Placing = Placing::o;
			break;
		case Placing::o:
			g_PlayerTiles[0].texture = x;
			g_Player0Placing = Placing::x;
			break;
		case Placing::win:
			break;
		}
		break;
	case Player::player1:
		switch (g_Player1Placing)
		{
		case Placing::none:
			break;
		case Placing::x:
			g_PlayerTiles[1].texture = o;
			g_Player1Placing = Placing::o;
			break;
		case Placing::o:
			g_PlayerTiles[1].texture = x;
			g_Player1Placing = Placing::x;
			break;
		case Placing::win:
			break;
		}
		break;
	}
}

void UpdateOxoGrid(const Point2f mousePos, Player player)
{
	for (int i{ 0 }; i < g_TileAmount; i++)
	{
		if (IsInsideRect(g_OxoTiles[i].rect, mousePos))
		{
			g_OxoTiles[i].player = player;
			switch (player)
			{
			case Player::player0:
				g_OxoTiles[i].placed = g_Player0Placing;
				g_Turn = Player::player1;
				break;
			case Player::player1:
				g_OxoTiles[i].placed = g_Player1Placing;
				g_Turn = Player::player0;
				break;
			}
		}
	}
}
#pragma endregion ownDefinitions