#include "pch.h"
#include "Game.h"
#include "Tile.h"

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	InitTileGame(g_TileGamePos);
}

void Draw()
{
	ClearBackground(0,0,0);

	// Put your own draw statements here

	DrawTileGame();
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
	for (int i{ 0 }; i < (g_AmountOfCols * g_AmountOfRows); ++i)
	{
		delete g_TileGame[i];
		g_TileGame[i] = nullptr;
	}
	DeleteTexture(g_Names);
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
	const Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
	for (int i{ 0 }; i < (g_AmountOfCols * g_AmountOfRows); ++i)
	{
		g_TileGame[i]->CheckActivation(mousePos);
	}
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
		const Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
		for (int i{ 0 }; i < (g_AmountOfCols * g_AmountOfRows); ++i)
		{
			g_TileGame[i]->CheckHit(mousePos);
		}
		CheckTileGameFinished();
		break;
	}
	case SDL_BUTTON_RIGHT:
		//std::cout << "Right mouse button released\n";
		break;
	case SDL_BUTTON_MIDDLE:
		//std::cout << "Middle mouse button released\n";
		break;
	}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here
void InitTileGame(const Point2f& topLeft)
{
	const float width{ g_TileWidth };
	const float height{ g_TileHeight };
	const int nrOfAnimals{ 6 };
	const std::string baseFilePath{ "Resources/Tiles" };
	const std::string fileType{ ".png" };
	for (int r{ 0 }; r < g_AmountOfRows; ++r)
	{
		for (int c{ 0 }; c < g_AmountOfRows; ++c)
		{
			const Rectf destRect{ topLeft.x + c*width,topLeft.y - r*height, width, height };
			g_TileGame[GetIndex(r, c, g_AmountOfRows)] = new Tile{destRect,baseFilePath + std::to_string(r) + std::to_string(c) + fileType,nrOfAnimals};
		}
	}
	const Rectf destRect{ topLeft.x, topLeft.y - (g_AmountOfRows - 1) * height - 32.0f, 2 * width, 32.0f };
	TextureFromFile("Resources/Names.png", g_Names);

}
void DrawTileGame()
{
	float width{ g_TileWidth };
	float height{ g_TileHeight };
	for (int i{ 0 }; i < (g_AmountOfCols * g_AmountOfRows); ++i)
	{
		g_TileGame[i]->Draw();
	}
	if (g_IsGameFinished)
	{
		SetColor(0, 1, 0, 1);
		DrawNames();
	}
	else
	{
		SetColor(1, 0, 0, 1);
	}
	DrawRect(g_TileGamePos.x, g_TileGamePos.y - ((g_AmountOfRows - 1) * height), width * g_AmountOfCols, height * g_AmountOfRows);
}
void CheckTileGameFinished()
{
	int n{ 0 };
	int max{ (g_AmountOfRows * g_AmountOfCols) };
	for (int i{ 0 }; i < max; ++i)
	{
		if (g_TileGame[i]->GetCurrentAnimal() == g_TileGame[(i + 1) % max]->GetCurrentAnimal())
		{
			++n;
		}
	}
	if (n == max)
	{
		for (int i{ 0 }; i < max; ++i)
		{
			g_TileGame[i]->Deactivate();
		}
		g_IsGameFinished = true;
		g_FinishedAnimal = g_TileGame[0]->GetCurrentAnimal();
		
	}
}

void DrawNames()
{
	int cols{ 1 };
	int rows{ 6 };
	Rectf srcRect{};
	srcRect.width = g_Names.width / cols;
	srcRect.height = g_Names.height / rows;
	srcRect.left = (g_FinishedAnimal % cols) * srcRect.width;
	srcRect.bottom = (g_FinishedAnimal + 1) * srcRect.height;

	Rectf destRect{};
	destRect.left = g_TileGamePos.x;
	destRect.bottom = 2;
	destRect.width = srcRect.width;
	destRect.height = srcRect.height;

	DrawTexture(g_Names, destRect, srcRect);
}
#pragma endregion ownDefinitions