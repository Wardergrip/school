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
	ClearBackground();

	// Put your own draw statements here
	DrawSquare1();
	DrawSquare2();
	DrawSquare3();
	DrawSquare4();
}

void Update(float elapsedSec)
{
#pragma region Misc


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

#pragma endregion
	g_GlobalPos.x = float(int(++g_GlobalPos.x) % int(g_WindowWidth));
	g_GlobalPos.y = float(int(++g_GlobalPos.y) % int(g_WindowHeight));
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
void DrawSquare1() 
{
	g_SquareBL1 = g_GlobalPos;
	SetColor(g_SquareBorderColor);
	DrawRect(g_SquareBL1, g_SquareSize, g_SquareSize);
	SetColor(g_SquareColor1);
	FillRect(g_SquareBL1.x + 1.0f, g_SquareBL1.y + 1.0f, g_SquareSize - 1.0f, g_SquareSize - 1.0f);
}
void DrawSquare2() 
{
	g_SquareBL2 = g_GlobalPos;
	g_SquareBL2.y = g_WindowHeight - g_SquareBL2.y - g_SquareSize;
	SetColor(g_SquareBorderColor);
	DrawRect(g_SquareBL2.x, g_SquareBL2.y, g_SquareSize, g_SquareSize);
	SetColor(g_SquareColor2);
	FillRect(g_SquareBL2.x + 1.0f, g_SquareBL2.y + 1.0f, g_SquareSize - 1.0f, g_SquareSize - 1.0f);
}
void DrawSquare3() 
{
	g_SquareBL3 = g_GlobalPos;
	g_SquareBL3.x = g_WindowWidth - g_SquareBL3.x - g_SquareSize;
	SetColor(g_SquareBorderColor);
	DrawRect(g_SquareBL3.x, g_SquareBL3.y, g_SquareSize, g_SquareSize);
	SetColor(g_SquareColor3);
	FillRect(g_SquareBL3.x + 1.0f, g_SquareBL3.y + 1.0f, g_SquareSize - 1.0f, g_SquareSize - 1.0f);
}
void DrawSquare4() 
{
	g_SquareBL4 = g_GlobalPos;
	g_SquareBL4.x = g_WindowWidth - g_SquareBL4.x - g_SquareSize;
	g_SquareBL4.y = g_WindowHeight - g_SquareBL4.y - g_SquareSize;
	SetColor(g_SquareBorderColor);
	DrawRect(g_SquareBL4.x, g_SquareBL4.y, g_SquareSize, g_SquareSize);
	SetColor(g_SquareColor4);
	FillRect(g_SquareBL4.x + 1.0f, g_SquareBL4.y + 1.0f, g_SquareSize - 1.0f, g_SquareSize - 1.0f);

}
#pragma endregion ownDefinitions