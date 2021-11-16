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
#pragma region DrawSquares
	SetColor(0, 0, 0, 1);
	DrawSquares(10, 230, 60, 10);
	DrawSquares(80, 230, 40, 5);
	DrawSquares(130, 230, 20, 3);
#pragma endregion
#pragma region ShrinkingTriangle
	SetColor(1,0,0,1);
	DrawEquilateralTriangle(200, 230, 60, 1);
	SetColor(0, 1, 0, 1);
	DrawEquilateralTriangle(210, 235, 40, 1);
	SetColor(0, 0, 1, 1);
	DrawEquilateralTriangle(215, 238, 30, 1);
#pragma endregion
#pragma region SmallerTriangles
	SetColor(0, 1, 1, 1);
	DrawEquilateralTriangle(270, 230, 30, 1);
	SetColor(1, 1, 0, 1);
	DrawEquilateralTriangle(300, 230, 30, 1);
	SetColor(1, 0, 1, 1);
	DrawEquilateralTriangle(285, 256, 30, 1);

	SetColor(0, 0, 0, 1);
	DrawEquilateralTriangle(270, 230, 30, 0);
	DrawEquilateralTriangle(300, 230, 30, 0);
	DrawEquilateralTriangle(285, 256, 30, 0);
#pragma endregion
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
void DrawSquares(float x, float y, float size, float numberOfSquares)
{
	float step{ (size / numberOfSquares) * 0.5f };
	for (int i{0}; i < numberOfSquares; i++) 
	{
		DrawRect(x + i * step, y + i * step, size - 2 * i * step, size - 2 * i * step);
	}
}
void DrawSquares(Point2f BottomLeft, float size, float numberOfSquares)
{
	DrawSquares(BottomLeft.x, BottomLeft.y, size, numberOfSquares);
}

void DrawEquilateralTriangle(float x, float y, float size, bool isFilled)
{
	Point2f bl{ x,y };
	Point2f br{ bl.x + size, bl.y };
	Point2f middle{ x + size * float(cos(1.04719755)), y + size * float(sin(1.04719755)) };
	if (isFilled == true) 
	{
		FillTriangle(bl, br, middle);
	}
	else 
	{
		DrawTriangle(bl, br, middle);
	}
}
void DrawEquilateralTriangle(Point2f bottomLeft, float size, bool isFilled) 
{
	DrawEquilateralTriangle(bottomLeft.x, bottomLeft.y, size, isFilled);
}

void DrawLinearGradient(float x, float y, float width, float height, Color4f left, Color4f right) 
{

}
void DrawLinearGradient(Point2f bl, float width, float height, Color4f left, Color4f right) 
{
	DrawLinearGradient(bl.x, bl.y, width, height, left, right);
}
void DrawLinearGradient(Rectf rectf, Color4f left, Color4f right) 
{
	DrawLinearGradient(rectf.bottom, rectf.left, rectf.width, rectf.height, left, right);
}
#pragma endregion ownDefinitions