#include "pch.h"
#include "Game.h"
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
	TestSprites();

	m_pSprites.reserve(16);
	for (size_t i{ 0 }; i < m_pSprites.capacity(); ++i)
	{
		m_pSprites.push_back(new Sprite("Tibo.png", 5, 5, 1.f / (rand() % (16 - 10 + 1) + 10)));
	}
}

void Game::Cleanup( )
{
	for (size_t i{ 0 }; i < m_pSprites.size(); ++i)
	{
		delete m_pSprites[i];
		m_pSprites[i] = nullptr;
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
	for (Sprite* p : m_pSprites)
	{
		p->Update(elapsedSec);
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	int i{0};
	for (Sprite* p : m_pSprites)
	{
		p->Draw(Point2f{p->GetFrameWidth()*(float(i % 5)),p->GetFrameHeight() * (float(i / 5)) });
		++i;
	}
}

void Game::TestSprites()
{
	std::cout << "\n--> Sprite class: Test rule of 5 started\n";
	Sprite sprite1{ "RunningKnight.png", 8, 1, 0.08f };
	Sprite sprite2{ "RunningKnight.png", 8, 1, 0.08f };
	//Sprite sprite3{ sprite1 };
	//sprite2 = sprite1;
	Sprite sprite4{ CreateSprite("Tibo.png", 5, 5, 1 / 10.f) };
	sprite1 = CreateSprite("Tibo.png", 5, 5, 1 / 10.f);
	std::cout << "std::move: ";
	sprite2 = std::move(sprite1);
	std::cout << "--> Sprite class: Test rule of 5 ended\n";
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

Container Game::CreateContainer(int nrElements, int min, int max) const
{
	Container c{ nrElements };
	for (int i{ 0 }; i < nrElements; ++i)
	{
		c.PushBack(rand() % (max - min + 1) + min);
	}
	return c;
}

Sprite Game::CreateSprite(const std::string& filename, int nrCols, int nrRows, float frameSec)
{
	return Sprite(filename,nrCols,nrRows,frameSec);
}
