#include "pch.h"
#include "Game.h"
#include "Fraction.h"
#include "Light.h"
#include "DaeEllipse.h"
#include <iostream>


//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	CreateFractions();
	CreateLights();
	CreateDells();
}

void Draw()
{
	ClearBackground(0,0,0);

	// Put your own draw statements here
	DrawFractions();
	DrawLights();
	DrawDells();
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
	DeleteFractions();
	DeleteLights();
	DeleteDells();
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
	g_pDell1->ActivateTest(mousePos);
	g_pDell2->ActivateTest(mousePos);
	g_pDell3->ActivateTest(mousePos);
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{

}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
	{
		//std::cout << "Left mouse button released\n";
		Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
		HitLights(mousePos);
		break;
	}
	case SDL_BUTTON_RIGHT:
		//std::cout << "Right mouse button released\n";
		break;
	case SDL_BUTTON_MIDDLE:
		//std::cout << "Middle mouse button released\n";
		break;
	}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here
void CreateFractions()
{
	g_pFrac1 = new Fraction{ 3,5 };
	g_pFrac2 = new Fraction{ 2,5 };
	g_pFrac3 = new Fraction{ 2,3 };
	g_pFrac4 = new Fraction{ 2,4 };
	g_pFrac5 = new Fraction{ 1,4 };
	g_pFrac6 = new Fraction{ 1,3 };
}
void DeleteFractions()
{
	delete g_pFrac1;
	g_pFrac1 = nullptr;
	delete  g_pFrac2;
	g_pFrac2 = nullptr;
	delete g_pFrac3;
	g_pFrac3 = nullptr;
	delete g_pFrac4;
	g_pFrac4 = nullptr;
	delete g_pFrac5; 
	g_pFrac5 = nullptr;
	delete g_pFrac6;
	g_pFrac6 = nullptr;
}
void DrawFractions()
{
	const Point2f bl{ 10,10 };
	const float size{ 20 };
	g_pFrac6->Draw(bl, size);
	g_pFrac5->Draw(Point2f{bl.x, bl.y + (size + size / 2)}, size);
	g_pFrac4->Draw(Point2f{ bl.x, bl.y + 2*(size + size / 2) }, size);
	g_pFrac3->Draw(Point2f{ bl.x, bl.y + 3*(size + size / 2) }, size);
	g_pFrac2->Draw(Point2f{ bl.x, bl.y + 4*(size + size / 2) }, size);
	g_pFrac1->Draw(Point2f{ bl.x, bl.y + 5*(size + size / 2) }, size);
}

void CreateLights()
{
	float height{ 20 };
	float left{120};
	int low{ 20 }, high{ 50 };
	g_pLight1 = new Light{ Rectf{left,10,float(GenerateRandom(low,high)),height}, RandomColor() };
	g_pLight2 = new Light{ Rectf{left + 50,10,float(GenerateRandom(low,high)),height}, RandomColor() };
	g_pLight3 = new Light{ Rectf{left,10 + height,float(GenerateRandom(low,high)),height}, RandomColor() };
	g_pLight4 = new Light{ Rectf{left + 50,10 + height,float(GenerateRandom(low,high)),height}, RandomColor() };
	g_pLight5 = new Light{ Rectf{left,10 + 2 * height,float(GenerateRandom(low,high)),height}, RandomColor() };
	g_pLight6 = new Light{ Rectf{left + 50,10 + 2 * height,float(GenerateRandom(low,high)),height}, RandomColor() };
	g_pLight7 = new Light{ Rectf{left,10 + 3 * height,float(GenerateRandom(low,high)),height}, RandomColor() };
	g_pLight8 = new Light{ Rectf{left + 50,10 + 3 * height,float(GenerateRandom(low,high)),height}, RandomColor() };
}
void DeleteLights()
{
	delete g_pLight1;
	g_pLight1 = nullptr;
	delete g_pLight2;
	g_pLight2 = nullptr;
	delete g_pLight3;
	g_pLight3 = nullptr;
	delete g_pLight4;
	g_pLight4 = nullptr;
	delete g_pLight5;
	g_pLight5 = nullptr;
	delete g_pLight6;
	g_pLight6 = nullptr;
	delete g_pLight7;
	g_pLight7 = nullptr;
	delete g_pLight8;
	g_pLight8 = nullptr;
}
void DrawLights()
{
	g_pLight1->Draw();
	g_pLight2->Draw();
	g_pLight3->Draw();
	g_pLight4->Draw();
	g_pLight5->Draw();
	g_pLight6->Draw();
	g_pLight7->Draw();
	g_pLight8->Draw();
}
void HitLights(const Point2f& pos)
{
	bool isChanged{ false };
	if(g_pLight1->IsHit(pos)) isChanged = true;
	if(g_pLight2->IsHit(pos)) isChanged = true;
	if(g_pLight3->IsHit(pos)) isChanged = true;
	if(g_pLight4->IsHit(pos)) isChanged = true;
	if(g_pLight5->IsHit(pos)) isChanged = true;
	if(g_pLight6->IsHit(pos)) isChanged = true;
	if(g_pLight7->IsHit(pos)) isChanged = true;
	if(g_pLight8->IsHit(pos)) isChanged = true;

	if (isChanged)
	{
		int amountOn{ g_pLight1->IsOn() + g_pLight2->IsOn() + g_pLight3->IsOn() + g_pLight4->IsOn() + g_pLight5->IsOn() + g_pLight6->IsOn() + g_pLight7->IsOn() + g_pLight8->IsOn() };
		std::cout << amountOn << " lights are on.\n";
	}
}

void CreateDells()
{
	g_pDell1 = new DaeEllipse{ Point2f{40,250}, 30, 40, Color4f{1,0,0,1} };
	g_pDell2 = new DaeEllipse{ Point2f{160,250}, 80, 40, Color4f{0,1,0,1} };
	g_pDell3 = new DaeEllipse{ Point2f{350,150}, 120, 140, Color4f{1,1,0,1} };
}
void DeleteDells()
{
	delete g_pDell1;
	g_pDell1 = nullptr;
	delete g_pDell2;
	g_pDell2 = nullptr;
	delete g_pDell3;
	g_pDell3 = nullptr;
}
void DrawDells()
{
	g_pDell1->Draw();
	g_pDell2->Draw();
	g_pDell3->Draw();
}

#pragma endregion ownDefinitions