#include "pch.h"
#include "Game.h"


Game::Game( const Window& window ) 
	:m_Window{ window }
	, m_BoundingRect{ 0, 0, window.width, window.height}
	, m_MaxCircles{ 50 }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	CreateCircles( );
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	UpdateCircles( elapsedSec );
}

void Game::Draw( ) const
{
	ClearBackground( );
	DrawCircles( );
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
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

void Game::CreateCircles( )
{
	const int minRadius{ 10 };
	const int maxradius{ 30 };
	int winWidth = int( m_Window.width );
	int winHeight = int( m_Window.height );
	Point2f center{};
	for ( int i{ 0 }; i < m_MaxCircles; ++i )
	{
		float radius = float( rand( ) % ( maxradius - minRadius + 1 ) + minRadius );
		int iRadius = int( radius );
		center.x = rand( ) % ( winWidth - 2 * iRadius + 1 ) + radius;
		center.y = rand( ) % ( winHeight - 2 * iRadius + 1 ) + radius;
		m_Circles.push_back( TrailingCircle( radius, center ) );
	}
}

void Game::UpdateCircles( float elapsedSec )
{
	for ( TrailingCircle& tc : m_Circles )
	{
		tc.Update( elapsedSec, m_BoundingRect );
	}
}

void Game::DrawCircles( ) const
{
	for ( const TrailingCircle& tc : m_Circles )
	{
		tc.Draw( );
	}
}
