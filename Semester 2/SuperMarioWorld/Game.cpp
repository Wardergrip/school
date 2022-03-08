#include "pch.h"
#include "Game.h"
#include "MainMenu.h"
#include <iostream>

#include "Texture.h"
#include "Level.h"
#include "Mario.h"
#include "Coin.h"
#include "FireFlower.h"
#include "Mushroom.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_Camera{window.width,window.height}
	,m_Player{}
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
	m_pLevel = new Level(m_Player);
	m_pMario = new Mario();
	m_Camera.SetLevelBoundaries(Rectf{0,0,m_Window.width * 2,m_Window.height * 2});
}

void Game::Cleanup( )
{
	delete m_pMainMenu;
	m_pMainMenu = nullptr;
	delete m_pLevel;
	m_pLevel = nullptr;
	delete m_pMario;
	m_pMario = nullptr;
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

	if (m_pMainMenu->m_State != MainMenu::State::playing) return;
	m_pMario->Update(elapsedSec, *m_pLevel);
	m_pLevel->UpdatePickUps(elapsedSec, m_pMario->GetRect());
	m_Camera.UpdateTransitioning(m_pMario->GetRect(), elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );
	// Mainmenu automatically disables itself, you can draw it at all times
	m_pMainMenu->Draw();

	if (m_pMainMenu->m_State != MainMenu::State::playing) return;
	glPushMatrix();
	{
		m_Camera.Transform(m_pMario->GetRect());
		m_pLevel->DrawPickUps();

		m_pLevel->DebugDraw();
		m_pMario->Draw();
	}
	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_p:
		m_Player.DebugPrintAll();
		break;
	case SDLK_UP:
		m_pMario->Jump();
		break;
	}
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
