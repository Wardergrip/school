#include "pch.h"
#include "Game.h"
#include "SoundStream.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_StreamMenuText{ "Resources/Images/StreamsMenu.png" }
	,m_EffectMenuText { "Resources/Images/EffectsMenu.png" }
	,m_StreamTest {true}
	,m_pDonkeyKongSong{new SoundStream("Resources/Sounds/DonkeyKong.mp3")}
	,m_pMarioSong{new SoundStream("Resources/Sounds/Mario.mp3")}
	,m_pLaserSFX{new SoundEffect("Resources/Sounds/laser.ogg")}
	,m_pJinglesSFX{new SoundEffect("Resources/Sounds/jingles.ogg")}
	// TODO: 1. Create the DonkeyKong and Mario SoundStream objects
	
	// TODO: 4. Create the Laser and Jingles SoundEffect objects

{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
}

void Game::Cleanup( )
{
	delete m_pDonkeyKongSong;
	m_pDonkeyKongSong = nullptr;
	delete m_pMarioSong;
	m_pMarioSong = nullptr;

	delete m_pLaserSFX;
	m_pLaserSFX = nullptr;
	delete m_pJinglesSFX;
	m_pJinglesSFX = nullptr;
}

void Game::Update( float elapsedSec )
{
}

void Game::Draw( ) const
{
	ClearBackground( );
	DrawMenu( );
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	switch ( e.keysym.sym )
	{
	case SDLK_RIGHT:
	case SDLK_LEFT:
		SwitchTest( );
		break;
	default:
		// Handle user request
		if ( m_StreamTest )
		{
			TestStreams( e );
		}
		else
		{
			TestEffects( e );
		}
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::DrawMenu( ) const
{
	if ( m_StreamTest )
	{
		m_StreamMenuText.Draw( );
	}
	else
	{
		m_EffectMenuText.Draw( );
	}
}

void Game::SwitchTest( )
{
	if ( m_StreamTest )
	{
		// TODO: 3. User switches to the "Effect test", stop the music
		m_pDonkeyKongSong->Stop();
		m_pMarioSong->Stop();
	}
	else
	{
		// TODO: 6. User switches to the "Stream test", stop the effects
		m_pLaserSFX->StopAll();
		m_pJinglesSFX->StopAll();
	}
	m_StreamTest = !m_StreamTest;
}

void Game::TestStreams( const SDL_KeyboardEvent& e )
{
	// TODO: 2. Handle the user requests in the "Stream test" menu 
	switch ( e.keysym.sym )
	{
	case SDLK_1:
	case SDLK_KP_1:
		// Play Donkey Kong (repeated)
		m_pDonkeyKongSong->Play(true);
		break;
	case SDLK_2:
	case SDLK_KP_2:
		// Play Mario (not repeated)
		m_pMarioSong->Play(true);
		break;
	case SDLK_p:
		// Pause the SoundStream
		if(m_pDonkeyKongSong->IsPlaying()) m_pDonkeyKongSong->Pause();
		if(m_pMarioSong->IsPlaying()) m_pMarioSong->Pause();
		break;
	case SDLK_r:
		// Resume the SoundStream
		m_pDonkeyKongSong->Resume();
		m_pMarioSong->Resume();
		break;
	case SDLK_s:
		// Stop the SoundStream
		m_pDonkeyKongSong->Stop();
		m_pMarioSong->Stop();
		break;
	case SDLK_UP:
		// Increase volume of SoundStream
		if (m_pDonkeyKongSong->IsPlaying()) m_pDonkeyKongSong->SetVolume(m_pDonkeyKongSong->GetVolume() + 1);
		else if (m_pMarioSong->IsPlaying()) m_pMarioSong->SetVolume(m_pMarioSong->GetVolume() + 1);
		break;
	case SDLK_DOWN:
		// Decrease volume of SoundStream
		if (m_pDonkeyKongSong->IsPlaying()) m_pDonkeyKongSong->SetVolume(m_pDonkeyKongSong->GetVolume() - 1);
		else if (m_pMarioSong->IsPlaying()) m_pMarioSong->SetVolume(m_pMarioSong->GetVolume() - 1);
		break;
	}
}

void Game::TestEffects( const SDL_KeyboardEvent& e )
{
	// TODO: 5. Handle the user requests in the "Effect test" menu 
	switch ( e.keysym.sym )
	{
	case SDLK_1:
	case SDLK_KP_1:
		// Play laser (repeated)
		m_pLaserSFX->Play(999);
		break;
	case SDLK_2:
	case SDLK_KP_2:
		// Play jingles (a number of times)
		m_pJinglesSFX->Play(3);
		break;
	case SDLK_p:
		// Pause all soundEffects
		m_pLaserSFX->PauseAll();
		m_pJinglesSFX->PauseAll();
		break;
	case SDLK_r:
		// Resume all soundEffects
		m_pLaserSFX->ResumeAll();
		m_pJinglesSFX->ResumeAll();
		break;
	case SDLK_s:
		// Stop  all soundEffects
		m_pLaserSFX->StopAll();
		m_pJinglesSFX->StopAll();
		break;
	case SDLK_UP:
		// Increase volume of all SoundEffects
		m_pLaserSFX->SetVolume(m_pLaserSFX->GetVolume() + 1);
		m_pJinglesSFX->SetVolume(m_pJinglesSFX->GetVolume() + 1);
		break;
	case SDLK_DOWN:
		// Decrease volume of all SoundEffects
		m_pLaserSFX->SetVolume(m_pLaserSFX->GetVolume() - 1);
		m_pJinglesSFX->SetVolume(m_pJinglesSFX->GetVolume() - 1);
		break;
	}
}

