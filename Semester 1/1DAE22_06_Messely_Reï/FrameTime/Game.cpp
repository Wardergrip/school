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
	SetColor(211 / 255.0f, 84 / 255.0f, 0, 1);
	DrawBall(g_BallPos);
	SetColor(1, 1, 0, 1);
	DrawFreeFall(g_BlockPos);
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
	
	 /*if (g_NumberOfFrames % 100 == 0)
	 {
		std::cout << "Number of frames: " << g_NumberOfFrames << "	AccumulatedTime: " << g_AccumulatedTime << "		Framerate: " << 1 / elapsedSec << std::endl;
	 }
	++g_NumberOfFrames;
	g_AccumulatedTime += elapsedSec;*/

	g_ElapsedSec = elapsedSec;

	UpdateBall(g_BallPos);
	if (g_IsFalling) UpdateFreeFall(g_BlockPos);
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
	case SDLK_s:
		if (g_IsFalling) g_IsFalling = false;
		else g_IsFalling = true;
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
void UpdateBall(float& x, float& y, float radius)
{
	if (x >= (g_WindowWidth - radius)) 
	{
		g_IsGoingRight = false;
	}
	else if (x <= radius) 
	{
		g_IsGoingRight = true;
	}
	if (y >= (g_WindowHeight - radius)) 
	{
		g_IsGoingUp = false;
	}
	else if (y <= radius )
	{
		g_IsGoingUp = true;
	}

	if (g_IsGoingRight)
	{
		x += g_HorizontalSpeed * g_ElapsedSec;
	}
	else 
	{
		x -= g_HorizontalSpeed * g_ElapsedSec;
	}
	if (g_IsGoingUp) 
	{
		y += g_VerticalSpeed * g_ElapsedSec;
	}
	else 
	{
		y -= g_VerticalSpeed * g_ElapsedSec;
	}
	
}
void UpdateBall(Point2f& position, float radius)
{
	UpdateBall(position.x, position.y, radius);
}

void DrawBall(float x, float y, float radius)
{
	FillEllipse(x, y, radius, radius);
}
void DrawBall(const Point2f& position, float radius)
{
	DrawBall(position.x, position.y, radius);
}

void UpdateFreeFall(float& x, float& y)
{
	if (y >= 0) 
	{
		float velocity{float(g_PreviousVelocity + g_Gravity * g_ElapsedSec)};
		y += velocity * g_ElapsedSec;
		std::cout << "Current velocity: " << velocity << std::endl;
		g_PreviousVelocity = velocity;
	}
	else 
	{
		g_BlockPos.y = g_WindowHeight - 15;
		g_IsFalling = false;
		g_PreviousVelocity = 0;
	}

}
void UpdateFreeFall(Point2f& position)
{
	UpdateFreeFall(position.x, position.y);
}

void DrawFreeFall(float x, float y, float size)
{
	FillRect(x, y, size, size);
}
void DrawFreeFall(const Point2f& position, float size)
{
	DrawFreeFall(position.x, position.y, size);
}
#pragma endregion ownDefinitions