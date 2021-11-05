#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
}

void Draw()
{
	ClearBackground(0,0,0);

	// Put your own draw statements here
	DrawPiles();
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
	switch (key)
	{
	case SDLK_1:
	case SDLK_KP_1:
		std::cout << "Key 1 released\n";
		UserTakesMatches(1);
		break;
	case SDLK_2:
	case SDLK_KP_2:
		std::cout << "Key 2 released\n";
		UserTakesMatches(2);
		break;
	case SDLK_3:
	case SDLK_KP_3:
		std::cout << "Key 3 released\n";
		UserTakesMatches(3);
		break;
	}
}
#pragma region MouseEvents
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
#pragma endregion MouseEvents
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here
void DrawMatch(float bottom, float left) 
{
	const float height{60}, width{4};
	const float h1{height * 0.8f}, h2{height * 0.2f};
	SetColor(g_Red);
	FillRect(bottom, left, width, h1);
	SetColor(g_Yellow);
	FillRect(bottom, left + h1, width, h2);
}
void DrawMatch(Point2f bottomLeft) 
{
	DrawMatch(bottomLeft.x, bottomLeft.y);
}
void DrawPiles()
{
	for (float i = float(g_Pile); i > 0; --i)
	{
		DrawMatch(10 + i * g_Step, g_WindowHeight / 2 + 50);
	}
	for (float i = float(g_UserPile); i > 0; --i) 
	{
		DrawMatch(10 + i * g_Step, 50);
	}
	for (float i = float(g_OpponentPile); i > 0; --i)
	{
		DrawMatch(10 + i * g_Step + g_WindowWidth / 2.0f, 50);
	}
}
void UserTakesMatches(int amount)
{
	if((amount <= g_Pile) && (g_UserTurn == true) && (g_SessionEnded == false)) 
	{
		g_UserPile += amount;
		g_Pile -= amount;
		std::cout << "User takes " << amount << " matches.\n";
	}
	g_UserMoves += std::to_string(amount) + " ";
	CheckSession();
}
void OpponentTakesMatches()
{
	int amount{};
	do 
	{
		amount = (rand() % 3) + 1;
	} while (!(amount <= g_Pile));
	std::cout << "Opponent takes " << amount << " matches.\n";
	g_OpponentPile += amount;
	g_Pile -= amount;
	g_OpponentMoves += std::to_string(amount) + " ";
}
void CheckSession()
{
	if (g_Pile == 0)
	{
		EndSession();
	}
	else if (g_UserTurn == true)
	{
		g_UserTurn = false;
	}
	if ((g_UserTurn == false) && (g_SessionEnded == false))
	{
		OpponentTakesMatches();
		if (g_Pile != 0)
		{
			g_UserTurn = true;
		}
		else 
		{
			EndSession();
		}
	}
}
void EndSession() 
{
	g_SessionEnded = true;
	std::cout << std::endl;
	std::cout << "Opponent moves [PC]: " << g_OpponentMoves << std::endl;
	std::cout << "User moves [YOU]: " << g_UserMoves << std::endl;
	if (g_UserTurn == false)
	{
		std::cout << "You win!\n";
	}
	else if (g_UserTurn == true)
	{
		std::cout << "You lose, better luck next time!\n";
	}

}
#pragma endregion ownDefinitions