#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	InitCards();
}

void Draw()
{
	ClearBackground();

	// Put your own draw statements here
	//DrawCards();
	DrawTexture(g_CardTextures[0], Point2f{ 0,0 }, Rectf{ 0,0,140,190 });
	DrawTexture(g_CardTextures[0], Point2f{ 150,0 });
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
	DeleteCards();
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
int GetIndex(int rowIdx, int colIdx, int nrCols)
{
	return (rowIdx * nrCols + colIdx);
}

void InitCards()
{
	for (int i{0}; i < g_AmountOfCards; i++)
	{
		int calc{ (((i / 13)+1) * 100) + ((i % 13)+1) };
		std::cout << "Initialising card nr. "<< calc << ": " << TextureFromFile("Resources/" + std::to_string(calc) + ".png", g_CardTextures[i]);
		g_CardRects[i].width = g_DefaultCard.width * g_CardScale;
		g_CardRects[i].height = g_DefaultCard.height * g_CardScale;
		std::cout << std::endl;
	}
	for (int i{ 0 }; i < 13; i++)
	{
		for (int j{ 0 }; j < 4; j++)
		{
			g_CardRects[GetIndex(j, i, 13)].left = i * g_CardRects[0].width;
			g_CardRects[GetIndex(j, i, 13)].bottom = j * g_CardRects[0].height;
		}
	}
}
void DeleteCards()
{
	for (int i{ 0 }; i < g_AmountOfCards; i++)
	{
		DeleteTexture(g_CardTextures[i]);
	}
}
void DrawCards()
{

	for (int i{ 0 }; i < 13; i++)
	{
		for (int j{ 0 }; j < 4; j++)
		{
			DrawTexture(g_CardTextures[GetIndex(j, i, 13)], Point2f{ i * g_CardRects[0].width,j * g_CardRects[0].height });//, g_CardRects[GetIndex(j, i, 13)]);
		}
	}
}
#pragma endregion ownDefinitions