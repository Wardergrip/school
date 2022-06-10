#include "pch.h"
#include "Game.h"

#include "log.h"

#include "unit.h"
#include "InfoPlate.h"
#include "Champion.h"
#include "ProjectileManager.h"

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
	m_TestingChamp->TeleportTo(Point2f{ m_Window.width / 2,m_Window.height / 2 });
	m_ProjectileManager = new ProjectileManager();
	
	m_Units.push_back(new Unit(Point2f{ 30,30 }, Rectf{ 0,0,20,20 }));
}

void Game::Cleanup( )
{
	delete m_TestingChamp;
	m_TestingChamp = nullptr;
	m_TestingChamp = nullptr;
	delete m_ProjectileManager;
	m_ProjectileManager = nullptr;
	for (size_t i{ 0 }; i < m_Units.size(); ++i)
	{
		delete m_Units[i];
		m_Units[i] = nullptr;
	}
}

void Game::Update( float elapsedSec )
{
	// Check keyboard state
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	
	m_TestingChamp->OnKeyHold(elapsedSec, pStates, m_LastMousePos);
	m_TestingChamp->Update(elapsedSec);
	m_ProjectileManager->UpdateAll(elapsedSec);
	for (size_t i{ 0 }; i < m_Units.size(); ++i)
	{
		m_Units[i]->Update(elapsedSec);
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	m_TestingChamp->Draw();
	
	m_ProjectileManager->DrawAll();
	for (Unit* unit : m_Units)
	{
		if (unit)
		{
			unit->Draw();
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
		break;
	case SDL_BUTTON_RIGHT:
		m_ProjectileManager->TryAutoAttack(Point2f{ float(e.x),float(e.y) }, m_TestingChamp, &m_Units);
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
