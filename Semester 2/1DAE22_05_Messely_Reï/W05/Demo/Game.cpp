#include "pch.h"
#include "Game.h"
#include "utils.h"
#include <vector>
#include "Matrix2x3.h"
#include <iostream>

Game::Game( const Window& window ) 
	: m_Window{ window }
	, m_LogoText{"resources/DAE.png"}
	, m_Angle{30.f}
	, m_RotationSpeed{360.f/10}
	, m_Position{100,200}
	, m_Scale{ 0.5f }
	, m_MousePos{}
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

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	m_MousePos = Point2f{ float(e.x),float(e.y) };
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

void Game::Update(float elapsedSec)
{
	m_Angle += elapsedSec * m_RotationSpeed;
}

void Game::Draw() const
{
	ClearBackground();
	DrawLogo();
	DrawPoly();
}

void Game::DrawLogo() const
{

	// TODO: Use OpenGl modelview transformations to draw the logo that
	// - rotates arounds its center
	// - is scaled (0.5)
	// - center is located at position 100,200
	//-->
	m_LogoText.Draw();
	glPushMatrix();
	{
		// T R S
		glTranslatef(m_Position.x, m_Position.y, 0.0f);
		glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
		glScalef(m_Scale, m_Scale, 1.0f);
		glTranslatef(-m_LogoText.GetWidth() / 2, -m_LogoText.GetHeight() / 2, 0.0f);
		//m_LogoText.Draw(Point2f{ -m_LogoText.GetWidth() / 2, -m_LogoText.GetHeight() / 2 });
		m_LogoText.Draw();
	}
	glPopMatrix();
}

void Game::DrawPoly() const
{
	std::vector<Point2f> vertices{ Point2f{0,0},Point2f{0, m_LogoText.GetHeight()},Point2f{ m_LogoText.GetWidth(), m_LogoText.GetHeight()},Point2f{m_LogoText.GetWidth(), 0}};
	utils::SetColor(Color4f{ 1.f,1.f,0.f,1.0f });
	utils::DrawPolygon(vertices, true, 5.0f);

	// TODO: Use MATRIX2x3 transformations to draw the rectangle that
	// - rotates arounds its center
	// - is scaled (0.5)
	// - center is located at position 100,200
	//-->

	Matrix2x3 matTranslate, matRotate, matScale, matCenter;
	matTranslate.SetAsTranslate(Vector2f{ m_Position });
	matRotate.SetAsRotate(m_Angle);
	matScale.SetAsScale(m_Scale, m_Scale);
	matCenter.SetAsTranslate(-m_LogoText.GetWidth() / 2, -m_LogoText.GetHeight() / 2);

	Matrix2x3 matWorld = matTranslate * matRotate * matScale * matCenter;
	std::vector<Point2f> transformedVertices{};
	transformedVertices = matWorld.Transform(vertices);

	if (utils::IsPointInPolygon(m_MousePos,transformedVertices)) utils::SetColor(Color4f{ 1.0f,0,1.0f,1.0f });
	utils::DrawPolygon(transformedVertices, true, 5.0f);
}


