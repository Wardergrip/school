#include "pch.h"
#include "Game.h"
#include "Ball.h"
#include "Texture.h"
#include <vector>

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
	for (int i = 0; i < m_BallSize; ++i)
	{
		m_pBalls[i] = new Ball(
			Point2f{ float(rand() % 300 - 20), 100 }, 
			Vector2f{ 300,200 }, 
			Color4f{ 1,float(i%2),0,1 }, 
			60.0f);
	}
	m_pLogo = new Texture{ "Images/DAE.png" };
	m_pMainText = new Texture{ "Hello world!","Resources/DIN-light.otf",20,Color4f{1,1,1,1} };
	VectorTest();
}

void Game::Cleanup( )
{
	for (int i = 0; i < m_BallSize; ++i)
	{
		delete m_pBalls[i];
		m_pBalls[i] = nullptr;
	}
	delete m_pLogo;
	m_pLogo = nullptr;
	delete m_pMainText;
	m_pMainText = nullptr;
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
	for (int i = 0; i < m_BallSize; ++i)
	{
		m_pBalls[i]->Update(elapsedSec,Rectf{0,0,m_Window.width,m_Window.height});
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	for (int i = 0; i < m_BallSize; i++)
	{
		m_pBalls[i]->Draw();
	}
	m_pLogo->Draw(Point2f{ 20,20 });
	m_pMainText->Draw(Point2f{ 10,200 });
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

void Game::VectorTest()
{
	std::cout << "Vector Demo\n";
	std::vector<int> numbers{1,2,3};

	numbers.push_back(5);
	numbers.push_back(2);

	for (int e : numbers)
	{
		std::cout << e << ", ";
	}
	std::cout << '\n';
}
