#include "pch.h"
#include "Game.h"

#include "Tower.h"
#include "Disk.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_CurrentMousePos{}
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_pTowers = new Tower[3]{
		Point2f{0,0},
		Point2f{300,0},
		Point2f{600,0}
	};
	m_pTowers[0].Pushback(new Disk{Disk::Size::large});
	m_pTowers[0].Pushback(new Disk{Disk::Size::medium});
	m_pTowers[0].Pushback(new Disk{Disk::Size::small});
}

void Game::Cleanup( )
{
	delete[] m_pTowers;
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
	for (int i{ 0 }; i < 3; ++i)
	{
		m_pTowers[i].FollowMouse(m_CurrentMousePos);
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	for (size_t i{ 0 }; i < 3; ++i)
	{
		m_pTowers[i].Draw();
	}
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
	m_CurrentMousePos = Point2f{ float(e.x),float(e.y) };
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		m_IsClickingLMB = true;
		for (int i{0}; i < 3; ++i)
		{
			m_pTowers[i].Select(Point2f{ float(e.x),float(e.y) });
		}
		break;
	}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		m_IsClickingLMB = false;
		for (int i{ 0 }; i < 3; ++i)
		{
			m_pTowers[i].Deselect(Point2f{ float(e.x),float(e.y) },m_pTowers);
		}
		break;
	}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
