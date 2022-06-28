#include "pch.h"
#include "Game.h"

#include "log.h"

#include "unit.h"
#include "InfoPlate.h"
#include "Champion.h"
#include "ProjectileManager.h"
#include "Ability.h"

#include "TargetDummy.h"

#include "utils.h"

#include "SmartTextComponent.h"

#include "OrientationManager.h"
#include "HUD.h"

#include "CircleProgression.h"
#include "Timer.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_Camera{window.width,window.height}
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	ProjectileManager::ChangeUnits(&m_Units);
	m_ProjectileManager = new ProjectileManager(&m_Units);
	Ability::InitProjManager(m_ProjectileManager);
	
	m_TestingChamp = new Champion(m_Window, m_ProjectileManager);
	m_TestingChamp->TeleportTo(Point2f{ m_Window.width / 2,m_Window.height / 2 });

	m_Units.push_back(new TargetDummy(Point2f{ 70,50 }));

	m_Orientation = new SmartTextComponent("w");
	m_Orientation->ChangeTransform(Transform{ Point2f{0,m_Window.height - 25} });

	m_Camera.SetLevelBoundaries(Rectf{ 0,0,400,400 });

	m_pInGameHUD = new HUD(HUD::HUDName::ingame);

}

void Game::Cleanup( )
{
	delete m_TestingChamp;
	m_TestingChamp = nullptr;
	delete m_ProjectileManager;
	m_ProjectileManager = nullptr;
	for (size_t i{ 0 }; i < m_Units.size(); ++i)
	{
		delete m_Units[i];
		m_Units[i] = nullptr;
	}

	delete m_pInGameHUD;
	m_pInGameHUD = nullptr;
}

void Game::Update( float elapsedSec )
{
	// Check keyboard state
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	
	m_TestingChamp->OnKeyHold(elapsedSec, pStates, m_LastMousePos);
	m_TestingChamp->Update(elapsedSec);
	m_ProjectileManager->UpdateAll(elapsedSec, pStates);
	for (size_t i{ 0 }; i < m_Units.size(); ++i)
	{
		m_Units[i]->Update(elapsedSec);
	}
	m_Orientation->UpdateText("Location: " + std::to_string(int(m_TestingChamp->GetTransform().location.x)) + " " + std::to_string(int(m_TestingChamp->GetTransform().location.y)));
	OrientationManager::UpdateCameraLoc(m_Camera.GetCameraPosition(m_TestingChamp->GetTransform().location));
}

void Game::Draw( ) const
{
	ClearBackground( );
	glPushMatrix();
	{
		m_Camera.Transform(m_TestingChamp->GetTransform().location);
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
	glPopMatrix();

	m_pInGameHUD->DrawAll();
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
