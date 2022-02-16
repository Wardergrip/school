#include "pch.h"
#include "Game.h"
#include "Card.h"
#include <iostream>

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
	int amountOfCards{ 52 };
	for (int i{ 0 }; i < amountOfCards; i++)
	{
		m_pCards.push_back( new Card{ Card::Suit((i / 13) + 1),int(((i % 13) + 1)) });
	}
}

void Game::Cleanup( )
{
	for (Card* pC : m_pCards)
	{
		delete pC;
		pC = nullptr;
	}
	m_pCards.clear();
	m_Numbs.clear();
}

void Game::Update( float elapsedSec )
{
	// Check keyboard state
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if ( pStates[SDL_SCANCODE_S] )
	{
		ShuffleCards();
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	for (int i{ 0 }; i < 13; ++i)
	{
		for (int j{ 0 }; j < 4; ++j)
		{
			m_pCards.at(GetIndex(j, i, 13))->Draw(Rectf{
				i * m_pCards[0]->GetWidth() * 0.5f,
				j * m_pCards[0]->GetHeight(),
				m_pCards[0]->GetWidth(),
				m_pCards[0]->GetHeight() });
		}
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
	case SDLK_EQUALS: // Must be SDLK_PLUS but doesn't work for me
		m_Numbs.push_back(rand() % 31);
		PrintElements();
		break;
	case SDLK_MINUS:
		if (m_Numbs.size() == 0) break;
		m_Numbs.pop_back();
		PrintElements();
		break;
	case SDLK_UP:
		for (size_t i{0}; i < m_Numbs.size(); ++i)
		{
			++m_Numbs[i];
		}
		PrintElements();
		break;
	case SDLK_DOWN:
		for (int& e : m_Numbs)
		{
			--e;
		}
		PrintElements();
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
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::PrintElements()
{
	/*for (size_t i = 0; i < m_Numbs.size(); i++)
	{
		std::cout << m_Numbs[i] << ' ';
	}
	std::cout << '\n';*/
	for (int e : m_Numbs)
	{
		std::cout << e << ' ';
	}
	std::cout << '\n';
}
void Game::ShuffleCards()
{
	int swapAmount(52);
	size_t a, b;
	for (int i{ 0 }; i < swapAmount; ++i)
	{
		do {
			a = rand() % m_pCards.size();
			b = rand() % m_pCards.size();
		} while (a == b); // Making sure you don't swap a card with the same card
		Card* temp = m_pCards[a];
		m_pCards[a] = m_pCards[b];
		m_pCards[b] = temp;
		temp = nullptr;
	}
}
size_t Game::GetIndex(size_t rowIdx, size_t colIdx, size_t nrCols) const
{
	return (rowIdx * nrCols + colIdx);
}
