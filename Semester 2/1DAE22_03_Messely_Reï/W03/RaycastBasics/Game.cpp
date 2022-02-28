#include "pch.h"
#include "Game.h"
#include "utils.h"
#include "Vector2f.h"
using namespace utils;

Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_Surface{}
	,m_MousePos{}
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_Surface.push_back(Point2f{ m_Window.width / 2, m_Window.height * 0.8f });
	m_Surface.push_back(Point2f{ m_Window.width * 0.8f, m_Window.height *0.6f });
	m_Surface.push_back(Point2f{ m_Window.width * 0.8f, m_Window.height *0.4f });
	m_Surface.push_back(Point2f{ m_Window.width / 2, m_Window.height * 0.2f });
	m_Surface.push_back(Point2f{ m_Window.width * 0.2f, m_Window.height * 0.4f });
	m_Surface.push_back(Point2f{ m_Window.width * 0.2f, m_Window.height * 0.6f });
}

void Game::Cleanup( )
{
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
}

void Game::Draw( )
{
	ClearBackground( );

	SetColor(Color4f{ 0,0,0,1 });
	FillPolygon(m_Surface);
	SetColor(Color4f{ 1,0.4f,0,1 });
	DrawPolygon(m_Surface, true, 2);

	Point2f rayPoint{ m_Window.width / 2,m_Window.height / 2  };
	HitInfo hitInfo{};
	SetColor(Color4f{1,1,0,1});
	DrawLine(rayPoint, m_MousePos);
	if (Raycast(m_Surface, rayPoint, m_MousePos, hitInfo))
	{
		// Normal
		SetColor(Color4f{ 0,1,0,1 });
		DrawVector(hitInfo.normal * 30, hitInfo.intersectPoint);
		// Afterline
		SetColor(Color4f{ 1,0.6f,0,1 });
		DrawLine(hitInfo.intersectPoint, m_MousePos);
		// Circle
		SetColor(Color4f{ 1,1,1,1 });
		FillEllipse(hitInfo.intersectPoint, 5, 5);
		// Reflect
		Vector2f rayVector{ rayPoint,m_MousePos };
		Vector2f reflectVector{ rayVector.Reflect(hitInfo.normal) * (1 - hitInfo.lambda) };
		DrawVector(reflectVector * (1 - hitInfo.lambda), hitInfo.intersectPoint);
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
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
	m_MousePos = Point2f{ float(e.x),float(e.y) };
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

void Game::DrawVector(const Vector2f& v, const Point2f& startPoint)
{
	const Point2f vectorPoint{ startPoint + v };
	const float vectorAngle{ atan2(v.x, v.y) };
	const float arrowAngle{ g_Pi / 6 };
	const float arrowLength{ 10 };
	const Point2f p1{ vectorPoint.x + arrowLength * cosf(1.5f * g_Pi - vectorAngle - arrowAngle), vectorPoint.y + arrowLength * sinf(1.5f * g_Pi - vectorAngle - arrowAngle) };
	const Point2f p2{ vectorPoint.x + arrowLength * cosf(1.5f * g_Pi - vectorAngle + arrowAngle), vectorPoint.y + arrowLength * sinf(1.5f * g_Pi - vectorAngle + arrowAngle) };
	DrawLine(startPoint, vectorPoint);
	//FillTriangle(vectorPoint, p1, p2);
}
