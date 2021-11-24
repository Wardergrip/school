#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	InitPentagrams(g_Pentagrams,g_PentagramsMaxSize);
	InitRandStatsToFont();
}

void Draw()
{
	ClearBackground(0,0,0);

	// Put your own draw statements here
	DrawClickedPoints(g_ClickedPositions, g_MaxNumberOfClickedPos);
	SetColor(0.4f, 1, 0.4f, 1);
	DrawPentagrams(g_Pentagrams, g_PentagramsMaxSize, g_PentagramCenterPoint, g_PentagramRadius);
	SetColor(g_SoftYellow);
	DrawRandStats();
	DrawMousePos(g_LastMousePos,g_MaxNumberOfLastPos);
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

	UpdatePentagrams(g_Pentagrams, g_PentagramsMaxSize, elapsedSec);
	UpdateRandStats();
}

void End()
{
	// free game resources here
	for (int i{ 0 }; i < g_RandStatAmount; i++)
	{
		DeleteTexture(g_RandStatTextures[i]);
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
	Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
	AddPointToArray(g_LastMousePos, g_MaxNumberOfLastPos, mousePos, g_CurrentMousePosIdx);
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{

}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	////std::cout << "  [" << e.x << ", " << e.y << "]\n";
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
	{
		// std::cout << "Left mouse button released\n";
		Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
		AddPointToArray(g_ClickedPositions, g_MaxNumberOfClickedPos, mousePos, g_CurrentClickedPosIdx);
		break;
	}
	case SDL_BUTTON_RIGHT:
		// std::cout << "Right mouse button released\n";
		break;
	case SDL_BUTTON_MIDDLE:
		// std::cout << "Middle mouse button released\n";
		break;
	}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here
void AddPointToArray(Point2f* arr, const int arrSize, const Point2f& mousePos, int& currentIdx)
{
	bool isFull{ false };
	for (int i{ 0 }; i < arrSize; i++)
	{
		if ((arr[i].x == 0) && (arr[i].y == 0)) isFull = true;
	}
	if (isFull)
	{
		for (int i{ 0 }; i < arrSize; i++)
		{
			if (i == arrSize - 1) arr[i] = mousePos;
			else arr[i] = arr[i + 1];
		}
	}
	else
	{
		arr[currentIdx] = mousePos;
		currentIdx = (currentIdx + 1) % arrSize;
	}
}
void DrawClickedPoints(const Point2f* pClickedPositions, const int arrSize)
{
	const float pointRad{ 4 };
	const Color4f pointColor{ 1,0.4f,0.4f,1 };
	SetColor(pointColor);
	for (int i{ 0 }; i < arrSize; i++)
	{
		if (!((pClickedPositions[i].x <= 0) && (pClickedPositions[i].y <= 0)))
		{
			FillEllipse(pClickedPositions[i], pointRad, pointRad);
			if (!((pClickedPositions[i - 1].x <= 0) && (pClickedPositions[i - 1].y <= 0)))
			{
				if (i == 0) DrawLine(pClickedPositions[i], pClickedPositions[arrSize - 1]);
				else DrawLine(pClickedPositions[i], pClickedPositions[i - 1]);
			}
		}
	}
}

void InitPentagrams(AngleSpeed* pArr, const int arrSize)
{
	for (int i{ 0 }; i < arrSize; i++)
	{
		pArr[i].speed = float(GenerateRandom(200, 1100) / 1000.0f);
	}
}
void DrawPentagrams(AngleSpeed* pPentagrams, const int arrSize, const Point2f& centerPoint, float rad)
{
	for (int i{ 0 }; i < arrSize; i++)
	{
		DrawPentagram(centerPoint, rad, pPentagrams[i].angle);
	}
}
void UpdatePentagrams(AngleSpeed* pPentagrams, const int arrSize, float elapsedSec)
{
	for (int i{ 0 }; i < arrSize; i++)
	{
		pPentagrams[i].angle += pPentagrams[i].speed * elapsedSec;
	}
}

void InitRandStatsToFont()
{
	for (int i{}; i < g_RandStatAmount; i++)
	{
		g_RandStats[i] = i;
		std::cout << "Initialising: " << std::to_string(g_RandStats[i]) << " in " << i << " <=> " << TextureFromString(std::to_string(g_RandStats[i]), "Resources/DIN-Light.otf", 22, g_SoftYellow, g_RandStatTextures[i]);
		std::cout << std::endl;
	}
}
void UpdateRandStats()
{
	g_RandStats[rand() % g_RandStatAmount]++;
}
void DrawRandStats()
{
	for (int i{ 0 }; i < g_RandStatAmount; i++)
	{
		DrawTexture(g_RandStatTextures[i], Point2f{ 10,g_WindowHeight - 30 - i * 20 });
		FillRect(Point2f{ 25,g_WindowHeight - 25 - i * 20 }, float(g_RandStats[i]), 10);
	}
}

void DrawMousePos(Point2f* arr, const int arrSize)
{
	for (int i{ 0 }; i < arrSize; i++)
	{
		SetColor(Color4f{ 0,0.4f,0.4f,0.6f });
		FillEllipse(arr[i], float(i*2), float(i*2));
		// Need to make sure that the size is in colleration with the lastIdx
	}
}
#pragma endregion ownDefinitions