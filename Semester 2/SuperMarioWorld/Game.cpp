#include "pch.h"
#include "Game.h"
#include "MainMenu.h"
#include <iostream>
#include "KoopaBase.h"
#include "Texture.h"
#include "Level.h"
#include "HUD.h"
#include "XMLProcessor.h"
#include "SoundManager.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_Camera{window.width,window.height}
	,m_Player{}
	,m_PersonalBestFilePath{"Resources/personalBest.xml"}
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	SoundManager::GetSoundEffect("Resources/deathSFX.ogg");
	SoundManager::GetSoundEffect("Resources/jumpSFX.ogg");
	SoundManager::GetSoundStream("Resources/OverworldTheme.mp3");

	XMLProcessor::ChangeFilePath("Resources/personalBest.xml");
	XMLProcessor::DisplayPersonalBest();

	m_pMainMenu = new MainMenu(m_Window, MainMenu::State::titlescreen);
	m_pLevel = new Level(m_Player);
	m_Camera.SetLevelBoundaries(Rectf{0,0,m_pLevel->GetFurthestXValue(),m_Window.height});
	m_pHUD = new HUD(m_Player,m_Window);

}

void Game::Cleanup( )
{
	delete m_pMainMenu;
	m_pMainMenu = nullptr;
	delete m_pLevel;
	m_pLevel = nullptr;
	delete m_pHUD;
	m_pHUD = nullptr;

	SoundManager::CleanUp();
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

	m_Player.Update(elapsedSec, *m_pLevel);
	if (m_Player.IsSoftReset())
	{
		m_Player.SoftReset();
		delete m_pLevel;
		m_pLevel = new Level(m_Player);
	}
	else if (m_Player.IsGameOver())
	{
		delete m_pLevel;
		m_pLevel = new Level(m_Player);
		m_Player.ResetAll();
		m_pMainMenu->m_State = MainMenu::State::titlescreen;
		XMLProcessor::DisplayPersonalBest();
	}

	m_pLevel->UpdateContent(elapsedSec, m_Player.GetpMario());
	m_Camera.UpdateTransitioning(m_Player.GetMarioRect(), elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );
	utils::SetColor(Color4f{ 0.73f, 0.9f, 1.f,1.f });
	// Mainmenu automatically disables itself, you can draw it at all times
	m_pMainMenu->Draw();

	if (m_pMainMenu->m_State != MainMenu::State::playing) return;
	glPushMatrix();
	{
		m_Camera.Transform(m_Player.GetMarioRect());

		m_pLevel->Draw(m_Camera.GetPos(), true);
		m_Player.Draw();
	}
	glPopMatrix();
	m_pHUD->Draw();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	m_Player.ProcessKeyDownEvent(e);
	switch ( e.keysym.sym )
	{
	case SDLK_p:
		m_Player.DebugPrintAllStats();
		break;
	case SDLK_0:
		XMLProcessor::WipeAndCleanSave();
		std::cout << "Current personalbest is reset\n";
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_i:
		DisplayInfo();
		break;
	case SDLK_d:
		std::cout << "[DEBUG] KoopaBaseHitBoxes ";
		if(KoopaBase::SwitchHitBoxDraw()) std::cout << "ENABLED\n";
		else std::cout << "DISABLED\n";
		break;
	case SDLK_g:
		std::cout << "[DEBUG] Level ";
		if (m_pLevel->SwitchDebugDrawLevel()) std::cout << "ENABLED\n";
		else std::cout << "DISABLED\n";
		break;
	}
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
	m_pMainMenu->CheckDownClicks(e);
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
	m_pMainMenu->CheckUpClicks(e);
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::DisplayInfo()
{
	std::cout << "\n"
		<< "Welcome to SuperMarioWorld!\n"
		<< "---------------------------\n"
		<< "Left & right arrow keys: moving left and right respectively\n"
		<< "Up arrow key: look up\n"
		<< "Down arrow key: duck\n"
		<< "Spacebar: jump\n"
		<< "Left shift: sprinting/grabbing (Hold)\n\n"
		<< "DEV: Press D to see KoopaBase hitboxes\n"
		<< "DEV: Press G to see level boundaries\n"
		<< "To disable main menu, change starting state in Game.cpp of the MainMenu object to playing\n"
		;
}
