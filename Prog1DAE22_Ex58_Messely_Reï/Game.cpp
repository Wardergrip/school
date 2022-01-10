#include "pch.h"
#include "Game.h"
#include "Vehicle.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	InitTextures();
	ShowInfo();
	InitVehicles();
}

void Draw()
{
	ClearBackground();

	// Put your own draw statements here
	DrawTexture(g_BackgroundTexture, Point2f{ 0,0 });
	DrawTexture(g_PlayerTexture, g_PlayerDstRect, g_PlayerSrcRect);
	for (int i{ 0 }; i < g_AmountOfVehicles; ++i)
	{
		g_Vehicles[i]->Draw();
	}

	Point2f bottomLeft{};
	switch (g_GameState)
	{
	case GameState::reset:
		break;
	case GameState::spelen:
		break;
	case GameState::pauzeren:
		bottomLeft = Point2f{ g_WindowWidth / 2 - g_PausingTextTexture.width / 2, g_WindowHeight / 2 - g_PausingTextTexture.height / 2 };
		SetColor(g_BoxCol);
		FillRect(bottomLeft, g_PausingTextTexture.width, g_PausingTextTexture.height);
		DrawTexture(g_PausingTextTexture, bottomLeft);
		break;
	case GameState::winnen:
		bottomLeft = Point2f{ g_WindowWidth / 2 - g_WinningTextTexture.width / 2, g_WindowHeight / 2 - g_WinningTextTexture.height / 2 };
		SetColor(g_BoxCol);
		FillRect(bottomLeft, g_WinningTextTexture.width, g_WinningTextTexture.height);
		DrawTexture(g_WinningTextTexture, bottomLeft);
		break;
	case GameState::verliezen:
		bottomLeft = Point2f{ g_WindowWidth / 2 - g_LosingTextTexture.width / 2, g_WindowHeight / 2 - g_LosingTextTexture.height / 2 };
		SetColor(g_BoxCol);
		FillRect(bottomLeft, g_LosingTextTexture.width, g_LosingTextTexture.height);
		DrawTexture(g_LosingTextTexture, bottomLeft);
		break;
	default:
		break;
	}

}

void Update(float elapsedSec)
{
	// process input, do physics 

	bool isMoving{ false };

	if ((g_PlayerPos.y <= g_TrottoirBorder) && !(g_GameState == GameState::reset))
	{
		g_GameState = GameState::winnen;
	}

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	switch (g_GameState)
	{
	case GameState::spelen:
		if (pStates[SDL_SCANCODE_RIGHT])
		{
			MovePlayer(PlayerDirection::right, elapsedSec);
			isMoving = true;
		}
		if (pStates[SDL_SCANCODE_LEFT])
		{
			MovePlayer(PlayerDirection::left, elapsedSec);
			isMoving = true;
		}
		if (pStates[SDL_SCANCODE_DOWN])
		{
			MovePlayer(PlayerDirection::down, elapsedSec);
			isMoving = true;
		}
		for (int i{ 0 }; i < g_AmountOfVehicles; ++i)
		{
			if (g_Vehicles[i]->IsIntersecting(g_PlayerPos))
			{
				g_Vehicles[i]->SetActive(false);
				g_GameState = GameState::verliezen;
			}
		}
		break;
	case GameState::reset:
		g_PlayerPos = Point2f{ g_WindowWidth / 2, g_WindowHeight - 20 };
		for (int i{ 0 }; i < g_AmountOfVehicles; ++i)
		{
			g_Vehicles[i]->Reset();
		}
		g_GameState = GameState::spelen;
		break;
	}
	
	for (int i{ 0 }; i < g_AmountOfVehicles; ++i)
	{
		g_Vehicles[i]->Update(elapsedSec, g_WindowWidth);
	}

	if (!isMoving) g_PlayerDirection = PlayerDirection::neutral;
	UpdatePlayer();
}

void End()
{
	// free game resources here
	DeleteTexture(g_BackgroundTexture);
	DeleteTexture(g_PlayerTexture);

	DeleteTexture(g_WinningTextTexture);
	DeleteTexture(g_LosingTextTexture);
	DeleteTexture(g_PausingTextTexture);

	for (int i{ 0 }; i < g_AmountOfVehicles; ++i)
	{
		delete g_Vehicles[i];
		g_Vehicles[i] = nullptr;
	}
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
	case SDLK_r:
		g_GameState = GameState::reset;
		break;
	case SDLK_p:
		switch (g_GameState)
		{
		case GameState::pauzeren:
			g_GameState = GameState::spelen;
			break;
		case GameState::spelen:
			g_GameState = GameState::pauzeren;
			break;
		}
		break;
	}
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{

}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{

}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{

}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here
void InitTextures()
{
	if (!TextureFromFile(g_BackgroundTexturePath, g_BackgroundTexture)) std::cout << "Background failed to load\n";
	if (!TextureFromString(g_WinningText, g_TextPath, g_TextSize, Color4f{ 1,1,1,1 }, g_WinningTextTexture)) std::cout << "Winning msg error\n";
	if (!TextureFromString(g_LosingText, g_TextPath, g_TextSize, Color4f{ 1,1,1,1 }, g_LosingTextTexture)) std::cout << "Losing msg error\n";
	if (!TextureFromString(g_PausingText, g_TextPath, g_TextSize, Color4f{ 1,1,1,1 }, g_PausingTextTexture)) std::cout << "Pausing msg error\n";
	if (!TextureFromFile(g_PlayerTexturePath, g_PlayerTexture)) std::cout << "Player texture failed to load.\n";
}
void UpdatePlayer()
{
	int state{};
	switch (g_PlayerDirection)
	{
	case PlayerDirection::neutral:
		state = 0;
		break;
	default:
		state = int(g_PlayerDirection) - 1;
		break;
	}
	int cols{ 3 };

	g_PlayerSrcRect.width = g_PlayerTexture.width / cols;
	g_PlayerSrcRect.height = g_PlayerTexture.height;
	g_PlayerSrcRect.left = (state % cols) * g_PlayerSrcRect.width;
	g_PlayerSrcRect.bottom = g_PlayerSrcRect.height;
	g_PlayerDstRect.width = g_PlayerSrcRect.width;
	g_PlayerDstRect.height = g_PlayerSrcRect.height;
	g_PlayerDstRect.left = g_PlayerPos.x - g_PlayerDstRect.width / 2;
	g_PlayerDstRect.bottom = g_PlayerPos.y - g_PlayerDstRect.height / 2;
}
void MovePlayer(PlayerDirection pd, float elapsedSec)
{
	g_PlayerDirection = pd;
	switch (pd)
	{
	case PlayerDirection::down:
		g_PlayerPos.y -= g_PlayerSpeed * elapsedSec;
		break;
	case PlayerDirection::left:
		g_PlayerPos.x -= g_PlayerSpeed * elapsedSec;
		break;
	case PlayerDirection::right:
		g_PlayerPos.x += g_PlayerSpeed * elapsedSec;
		break;
	default:
		break;
	}
}
void ShowInfo()
{
	std::cout << "Press r to reset.\nPress p to pause / unpause\nUse the arrow keys to move the chicken.\n";
}

void InitVehicles()
{
	float laneWidth{ 45 };
	int* holder{ new int[g_AmountOfVehicles] {} };
	for (int i{ 0 }; i < g_AmountOfVehicles; ++i)
	{
		g_Vehicles[i] = new Vehicle{ i };
		holder[i] = int(g_TrottoirBorder + i * laneWidth);
	}
	Shuffle(holder, g_AmountOfVehicles, rand() % 7);
	for (int i{ 0 }; i < g_AmountOfVehicles; ++i)
	{
		g_Vehicles[i]->SetYPos(float(holder[i]));
	}
	delete[] holder;
}
void Shuffle(int* pArray, int size, int swaps)
{
	for (int i{ 0 }; i < swaps; i++)
	{
		int idx1{ rand() % size };
		int idx2{ rand() % size };
		int a{ pArray[idx1] };
		pArray[idx1] = pArray[idx2];
		pArray[idx2] = a;
	}
}
#pragma endregion ownDefinitions