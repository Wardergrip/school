#include "pch.h"
#include "Game.h"

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
}

void Draw()
{
	ClearBackground(0, 0, 0); // Make background black

	// Put your own draw statements here
	DrawStairs();
	DrawSpinning();
	DrawSquares();
	DrawSpiral();
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
void DrawStairs() 
{
	const float maxSize{ 200 };
	const float amountOfSteps{ 5 };
	const float width{ maxSize / amountOfSteps };
	const float height{ maxSize / amountOfSteps };
	
	bool isBlue{false};
	for (float i{}; i < amountOfSteps; ++i)
	{
		if (isBlue == false) 
		{
			SetColor(g_Red);
			isBlue = true;
		}
		else 
		{
			SetColor(g_Blue);
			isBlue = false;
		}
		DrawLine(g_CenterPointStairs.x - maxSize / 2.0f + i * width, g_CenterPointStairs.y - maxSize / 2.0f + i * height, g_CenterPointStairs.x - maxSize / 2.0f + (i + 1) * width, g_CenterPointStairs.y - maxSize / 2.0f + i * height);
		DrawLine(g_CenterPointStairs.x - maxSize / 2.0f + (i + 1) * width, g_CenterPointStairs.y - maxSize / 2.0f  + i * height, g_CenterPointStairs.x - maxSize / 2.0f + (i + 1) * width, g_CenterPointStairs.y - maxSize / 2.0f + (i + 1) * height);
	}
}
void DrawSpinning() 
{
	const float maxSize{ 200 };
	const float amountOfLines{5.0f};
	const float step{maxSize / amountOfLines};	
	for (int i{}; i <= amountOfLines; ++i)
	{
		SetColor(g_Green);
		DrawLine(g_CenterPointSpinning.x - maxSize / 2.0f + i*step, g_CenterPointSpinning.y + maxSize / 2.0f, g_CenterPointSpinning.x + maxSize / 2.0f, g_CenterPointSpinning.y + maxSize / 2.0f - i * step);
		SetColor(g_Red);
		DrawLine(g_CenterPointSpinning.x + maxSize / 2.0f, g_CenterPointSpinning.y + maxSize / 2.0f - i * step, g_CenterPointSpinning.x + maxSize / 2.0f - i * step, g_CenterPointSpinning.y - maxSize / 2.0f);
		SetColor(g_Yellow);
		DrawLine(g_CenterPointSpinning.x + maxSize / 2.0f - i * step, g_CenterPointSpinning.y - maxSize / 2.0f, g_CenterPointSpinning.x - maxSize / 2.0f, g_CenterPointSpinning.y - maxSize / 2.0f + i * step);
		SetColor(g_Blue);
		DrawLine(g_CenterPointSpinning.x - maxSize / 2.0f , g_CenterPointSpinning.y - maxSize / 2.0f + i * step, g_CenterPointSpinning.x - maxSize / 2.0f + i * step, g_CenterPointSpinning.y + maxSize / 2.0f );
	}
}
void DrawSquares() 
{
	const float startingSize{ 50 };
	const float step{ 30 };
	const float maxSize{ 200 };
	
	SetColor(g_Green);
	for (float i = startingSize; i <= maxSize; i += step) 
	{
		DrawRect(g_CenterPointSquares.x - i / 2.0f, g_CenterPointSquares.y - i / 2.0f, i, i);
	}
}
void DrawSpiral() 
{
	const float startingSize{ 200 };
	const float step{ 15 };
	const float minimumSize{ 30 };
	SetColor(g_Blue);
	for (float i = startingSize / 2.0f; i >= minimumSize; i -= step)
	{
		DrawLine(g_CenterPointSpiral.x - i, g_CenterPointSpiral.y - i, g_CenterPointSpiral.x +  i, g_CenterPointSpiral.y - i);
		DrawLine(g_CenterPointSpiral.x + i, g_CenterPointSpiral.y - i, g_CenterPointSpiral.x +  i, g_CenterPointSpiral.y + i - step);
		DrawLine(g_CenterPointSpiral.x + i, g_CenterPointSpiral.y + i - step, g_CenterPointSpiral.x - i + step, g_CenterPointSpiral.y + i - step);
		DrawLine(g_CenterPointSpiral.x - i + step, g_CenterPointSpiral.y + i - step, g_CenterPointSpiral.x - i + step, g_CenterPointSpiral.y - i + step);

	}
}
#pragma endregion ownDefinitions