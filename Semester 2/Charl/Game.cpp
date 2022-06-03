#include "pch.h"
#include "Game.h"

#include "log.h"

#include "Champion.h"
#include "InfoPlate.h"
#include "LockOnProjectile.h"

#include "utils.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_TestingChamp{ new Champion{window} }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_TestPlate = new InfoPlate{m_TestingChamp};
	m_TestPlate->SetName("Tester");
	m_TestingChamp->TeleportTo(Point2f{ m_Window.width / 2,m_Window.height / 2 });
	m_LockOnProjs.reserve(16);
	m_LockOnProjs.push_back(new LockOnProjectile{ Point2f{0,0},m_TestingChamp});
}

void Game::Cleanup( )
{
	delete m_TestingChamp;
	m_TestingChamp = nullptr;
	delete m_TestPlate;
	m_TestingChamp = nullptr;
	for (size_t i{ 0 }; i < m_LockOnProjs.size(); ++i)
	{
		delete m_LockOnProjs[i];
		m_LockOnProjs[i] = nullptr;
	}
}

void Game::Update( float elapsedSec )
{
	// Check keyboard state
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	
	m_TestingChamp->OnKeyHold(elapsedSec, pStates, m_LastMousePos);
	m_TestingChamp->Update(elapsedSec);
	for (size_t i{ 0 }; i < m_LockOnProjs.size(); ++i)
	{
		if (m_LockOnProjs[i] == nullptr)
		{
			continue;
		}
		m_LockOnProjs[i]->Update(elapsedSec);
		if (m_LockOnProjs[i]->HasHit())
		{
			delete m_LockOnProjs[i];
			m_LockOnProjs[i] = nullptr;
		}
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	m_TestingChamp->Draw();
	m_TestPlate->Draw();
	
	for (auto proj : m_LockOnProjs)
	{
		if (proj)
		{
			proj->Draw();
		}
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_p:
		Unit::SwitchDrawingHitboxes();
		Log(std::boolalpha << "[DEBUG] DrawingHitboxes: " << Unit::IsDrawingHitboxes());
		break;
	case SDLK_o:
		InfoPlate::SwitchDrawInfoPlates();
		Log(std::boolalpha << "[DEBUG] DrawingInfoPlates: " << InfoPlate::IsDrawingInfoPlates());
		break;
	}
	m_TestingChamp->OnKeyDown(e, m_LastMousePos);
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

	m_TestingChamp->OnKeyUp(e, m_LastMousePos);
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
	m_LastMousePos = Point2f{ float(e.x),float(e.y) };

	m_TestingChamp->OnMouseMotion(e);
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	m_TestingChamp->OnMouseDown(e);
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		m_LockOnProjs.push_back(new LockOnProjectile{ Point2f{float(e.x),float(e.y)},m_TestingChamp});
		break;
	case SDL_BUTTON_RIGHT:
		break;
	case SDL_BUTTON_MIDDLE:
		break;
	}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	m_TestingChamp->OnMouseUp(e);
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

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
