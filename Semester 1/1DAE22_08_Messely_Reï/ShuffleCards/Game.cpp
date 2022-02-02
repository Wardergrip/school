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
	DrawCards();
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

	if (g_Shuffle)
	{
		ShuffleCards();
		g_Shuffle = false;
	}
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
	switch (key)
	{
	case SDLK_s:
		std::cout << "s key released.\n";
		g_Shuffle = true;
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
void Swap(Texture* pArray, int size, int idx1, int idx2)
{
	if ((idx1 >= size) || (idx2 >= size) || (idx1 < 0) || (idx2 < 0)) std::cout << "Texture Swapping error: swapping out of bounds\n";
	Texture a{ pArray[idx1] };
	pArray[idx1] = pArray[idx2];
	pArray[idx2] = a;
}
void Swap(Rectf* pArray, int size, int idx1, int idx2)
{
	if ((idx1 >= size) || (idx2 >= size) || (idx1 < 0) || (idx2 < 0)) std::cout << "Rectf Swapping error: swapping out of bounds\n";
	Rectf a{ pArray[idx1] };
	pArray[idx1] = pArray[idx2];
	pArray[idx2] = a;
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
			DrawTexture(g_CardTextures[GetIndex(j, i, 13)], g_CardRects[GetIndex(j, i, 13)]); 
		}
	}
}
void ShuffleCards()
{
	const int amountShuffle{ GenerateRandom(50, 150) };
	unsigned int a{};
	unsigned int b{};
	const bool debugMsg{ false };
	if (debugMsg) std::cout << "Shuffling for " << amountShuffle << " times.\n";
	for (int i{ 0 }; i < amountShuffle; i++)
	{
		do {
		a = GenerateRandom(0, g_AmountOfCards - 1);
		b = GenerateRandom(0, g_AmountOfCards - 1);
		} while (a == b); // Making sure you don't swap a card with the same card
		// One of the following 2 lines should be commented, if both are left uncommented, nothing will happen but changing the draworder
		//Swap(g_CardTextures, g_AmountOfCards, a, b); // Swaps Textures
		Swap(g_CardRects, g_AmountOfCards, a, b); // Swaps Position
		if (debugMsg) std::cout << "Swapped " << a << " & " << b << std::endl;
	}
}
#pragma endregion ownDefinitions