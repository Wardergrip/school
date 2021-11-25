#include "pch.h"
#include "Game.h"

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	InitFiles();
}

void Draw()
{
	ClearBackground();

	// Put your own draw statements here
	DrawTexture(g_OXOTxt, Rectf{ 0,0,g_WindowWidth,g_WindowHeight });
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
	
}
#pragma endregion ownDefinitions