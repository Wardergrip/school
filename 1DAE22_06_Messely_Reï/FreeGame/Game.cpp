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
	ClearBackground(0,0,0);

	// Put your own draw statements here
	SetColor(0.8f, 0.8f, 1, 1); // Soft blue
	DrawPlatform(g_PlatformPos, g_PlatformLength, g_PlatformHeight);
	DrawBall(g_MainBallPos, g_MainBallRadius);
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
	UpdateBall(g_MainBallPos, g_MainBallRadius, g_MainBallVelocity, elapsedSec);
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
	Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
	g_PlatformPos.x = mousePos.x;
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
void DrawPlatform(float x, float y, float totLength, float totHeight)
{
	FillRect(x - totLength / 2, y - totHeight / 2, totLength, totHeight);
}
void DrawPlatform(const Point2f& midPos, float totLength, float totHeight)
{
	DrawPlatform(midPos.x, midPos.y, totLength, totHeight);
}

void DrawBall(float x, float y, float r)
{
	FillEllipse(x, y, r, r);
}
void DrawBall(const Point2f& pos, float r)
{
	DrawBall(pos.x, pos.y, r);
}

void UpdateBall(float& x, float& y, float r, float velocity, float elapsedSec)
{
	x += velocity * elapsedSec * int(g_LeftRight);
	y += velocity * elapsedSec * int(g_UpDown);
}
void UpdateBall(Point2f& pos, float r, float velocity, float elapsedSec)
{
	UpdateBall(pos.x, pos.y, r, velocity, elapsedSec);
}
#pragma endregion ownDefinitions