#include "pch.h"
#include "Game.h"
using namespace utils;

Game::Game( const Window& window ) 
	:m_Window{ window }
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

void Game::Draw( ) const
{
	ClearBackground( );

	//Surface
	Point2f surfaceP1{ 350.0f,50.0f };
	Point2f surfaceP2{ 150.0f,250.0f };
	SetColor(Color4f{ 1.0f,0.5f,0.2f,1.0f });
	DrawLine(surfaceP1, surfaceP2, 2);

	//The ray
	Point2f rayP1{ 100,40 };
	Point2f rayP2{ m_MousePos };
	SetColor(Color4f{ 1,1,0,1 });

	//Raycast
	HitInfo hitInfo{};
	std::vector<Point2f> surface{surfaceP1,surfaceP2};
	if (Raycast(surface, rayP1, rayP2, hitInfo))
	{
		DrawLine(rayP1, hitInfo.intersectPoint);

		// Intersect
		SetColor(Color4f{ 1,1,0,1 });
		DrawEllipse(hitInfo.intersectPoint, 10, 10, 2);

		// Normal
		SetColor(Color4f{ 0,1,0,1 });
		DrawVector(hitInfo.normal * 100, hitInfo.intersectPoint);

		// Reflection Vector
		SetColor(Color4f{ 1,1,1,1 });
		Vector2f rayVector{ rayP1,rayP2 };
		Vector2f reflectVector{ rayVector.Reflect(hitInfo.normal) * (1 - hitInfo.lambda) };
		DrawVector(reflectVector,hitInfo.intersectPoint);
	}
	else DrawLine(rayP1, rayP2);
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
	m_MousePos = Point2f{ float(e.x),float(e.y) };
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

void Game::DrawVector(const Vector2f& v, const Point2f& startPoint) const
{
	const Point2f vectorPoint{ startPoint + v };
	const float vectorAngle{ atan2(v.x, v.y) };
	const float arrowAngle{ g_Pi / 6 };
	const float arrowLength{ 10 };
	const Point2f p1{ vectorPoint.x + arrowLength * cosf(1.5f * g_Pi - vectorAngle - arrowAngle), vectorPoint.y + arrowLength * sinf(1.5f * g_Pi - vectorAngle - arrowAngle) };
	const Point2f p2{ vectorPoint.x + arrowLength * cosf(1.5f * g_Pi - vectorAngle + arrowAngle), vectorPoint.y + arrowLength * sinf(1.5f * g_Pi - vectorAngle + arrowAngle) };
	DrawLine(startPoint, vectorPoint);
	FillTriangle(vectorPoint, p1, p2);
	
}
