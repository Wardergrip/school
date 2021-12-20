#include "pch.h"
#include "Game.h"
#include "Sprite.h"
#include "SuperSprite.h"
#include <iostream>


//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	float speedKnight{ 1 / 10.0f };
	float speedTibo{ 1 / 10.0f };
	for (int i{ 0 }; i < g_AmountOfSprites; ++i)
	{
		if (i < 3)
		{
			g_pSprites[i] = new Sprite{ g_FilePathRunningKnight,8,1,8,speedKnight,i * 1.5f };
		}
		else
		{
			g_pSprites[i] = new Sprite{ g_FilePathTibo,5,5,25,speedTibo,i * 0.4f };
		}
	}
	g_Mario = new SuperSprite(3);
	g_Mario->InitState(int(AnimationState::idle), g_FilePathMarioIdle, 4, 2, 7, 0.1f, 1);
	g_Mario->InitState(int(AnimationState::running), g_FilePathMarioRun, 4, 4, 15, 0.05f, 1,true);
	g_Mario->InitState(int(AnimationState::jumping), g_FilePathMarioJump, 4, 3, 11, 0.15f, 1,true);
}

void Draw()
{
	ClearBackground();

	// Put your own draw statements here
	for (int i{ 0 }; i < g_AmountOfSprites; ++i)
	{
		if (i < 3)
		{
			g_pSprites[i]->Draw(Point2f{ float(10 + i * 30),10 });
		}
		else
		{
			g_pSprites[i]->Draw(Point2f{ float(10 + (i-3) * 190),70 });
		}
	}
	g_Mario->DrawSte(int(g_MarioState), 10, 10);
	
}

void Update(float elapsedSec)
{
	// process input, do physics 
	g_Mario->UpdateSte(elapsedSec);

	for (int i{ 0 }; i < g_AmountOfSprites; ++i)
	{
		g_pSprites[i]->Update(elapsedSec);
	}

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
	delete g_Mario;
	g_Mario = nullptr;
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
	case SDLK_LEFT:
		//std::cout << "Left arrow key released\n";
		for (int i{ 0 }; i < g_AmountOfSprites; ++i)
		{
			g_pSprites[i]->InitLoopOnce();
		}
		break;
	case SDLK_RIGHT:
		//std::cout << "Right arrow key released\n";
		g_MarioState = AnimationState((int(g_MarioState) + 1) % 3);
		break;
	case SDLK_1:
	case SDLK_KP_1:
		//std::cout << "Key 1 released\n";
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

#pragma endregion ownDefinitions