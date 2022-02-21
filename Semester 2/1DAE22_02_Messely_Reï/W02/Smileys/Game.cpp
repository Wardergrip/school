#include "pch.h"
#include "Game.h"
#include "Smiley.h"

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
	for (int i{ 0 }; i < m_MaxAmountOfSmileys; ++i)
	{
		m_pSmileys[i] = new Smiley(Point2f{ float(rand() % int(m_Window.width * 0.8f)), float(rand() % int(m_Window.height * 0.8f)) });
	}
}

void Game::Cleanup( )
{
	for (int i{ 0 }; i < m_MaxAmountOfSmileys; ++i)
	{
		if (m_pSmileys[i] != nullptr)
		{
			delete m_pSmileys[i];
			m_pSmileys[i] = nullptr;
		}
	}
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

	int highestIdx{};
	float highestY{0};
	for (int i{ 0 }; i < m_MaxAmountOfSmileys; ++i)
	{
		if (m_pSmileys[i] != nullptr)
		{
			m_pSmileys[i]->Update(elapsedSec, Rectf{ 0,0,m_Window.width,m_Window.height }, Rectf{50,50,m_Window.width * 0.8f,m_Window.height * 0.8f});
			m_pSmileys[i]->SetHighest(false);
			if (highestY <= m_pSmileys[i]->GetPosition().y)
			{
				highestY = m_pSmileys[i]->GetPosition().y;
				highestIdx = i;
			}
		}
	}
	if (m_pSmileys[highestIdx] != nullptr) m_pSmileys[highestIdx]->SetHighest(true);
}

void Game::Draw( ) const
{
	ClearBackground( );

	utils::DrawRect(Rectf{ 50,50,m_Window.width * 0.8f,m_Window.height * 0.8f });
	for (int i{ 0 }; i < m_MaxAmountOfSmileys; ++i)
	{
		if (m_pSmileys[i] != nullptr) m_pSmileys[i]->Draw();
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_UP:
		for (int i{ 0 }; i < m_MaxAmountOfSmileys; ++i)
		{
			if (m_pSmileys[i] != nullptr) m_pSmileys[i]->IncreaseSpeed();
		}
		break;
	case SDLK_DOWN:
		for (int i{ 0 }; i < m_MaxAmountOfSmileys; ++i)
		{
			if (m_pSmileys[i] != nullptr) m_pSmileys[i]->DecreaseSpeed();
		}
		break;
	case SDLK_DELETE:
		for (int i{ 0 }; i < m_MaxAmountOfSmileys; ++i)
		{
			if (m_pSmileys[i] != nullptr) 
			{
				if (m_pSmileys[i]->IsSleeping()) 
				{
					delete m_pSmileys[i];
					m_pSmileys[i] = nullptr;
				}
			}
		}
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		//std::cout << " left button " << std::endl;
		for (int i{ 0 }; i < m_MaxAmountOfSmileys; ++i)
		{
			if (m_pSmileys[i] != nullptr) m_pSmileys[i]->HitTest(Point2f{ float(e.x),float(e.y) });
		}
		break;
	case SDL_BUTTON_RIGHT:
		//std::cout << " right button " << std::endl;
		break;
	case SDL_BUTTON_MIDDLE:
		//std::cout << " middle button " << std::endl;
		break;
	}
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
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
