#include "pch.h"
#include "Game.h"
#include "MainMenu.h"
#include <iostream>
#include "PickUp.h"
#include "Texture.h"
#include "Level.h"
#include "Mario.h"
#include "Coin.h"
#include "FireFlower.h"
#include "Mushroom.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_pMainMenu = new MainMenu(m_Window, MainMenu::State::playing);
	m_pLevel = new Level();
	m_pLevel->Push_back(Point2f{ 0,0 });
	m_pLevel->Push_back(Point2f{ 0,100 });
	m_pLevel->Push_back(Point2f{ 200,100 });
	m_pLevel->Push_back(Point2f{ 200,10 });
	m_pLevel->Push_back(Point2f{ 400,10 });
	m_pLevel->Push_back(Point2f{ 400,100 });
	m_pLevel->Push_back(Point2f{ m_Window.width,100 });
	m_pLevel->Push_back(Point2f{ m_Window.width,0 });
	m_pLevel->Push_back(Point2f{ 0,0 });
	m_pMario = new Mario();
	m_pCoin = new Coin(Coin::Type::big, Point2f{200,300});
	m_pFF = new FireFlower(Point2f{ 0,300 });
	m_pMr = new Mushroom(m_pLevel, Point2f{0,400});
}

void Game::Cleanup( )
{
	delete m_pMainMenu;
	m_pMainMenu = nullptr;
	delete m_pLevel;
	m_pLevel = nullptr;
	delete m_pMario;
	m_pMario = nullptr;
	delete m_pCoin;
	m_pCoin;
	delete m_pMr;
	m_pMr = nullptr;
	delete m_pFF;
	m_pFF = nullptr;
}

void Game::Update( float elapsedSec )
{
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
	m_pMainMenu->Update(elapsedSec);
	m_pMario->Update(elapsedSec, *m_pLevel);
	m_pCoin->UpdateAnim(elapsedSec);
	m_pFF->UpdateAnim(elapsedSec);
	m_pMr->UpdateAnim(elapsedSec);
	m_pMr->Update(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );
	m_pMainMenu->Draw();
	m_pLevel->DebugDraw();
	m_pMario->Draw();
	m_pCoin->Draw();
	m_pFF->Draw();
	m_pMr->Draw();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
	m_pMainMenu->CheckSelect(Point2f{float(e.x),float(e.y)});
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	m_pMainMenu->CheckClicks(e);
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
