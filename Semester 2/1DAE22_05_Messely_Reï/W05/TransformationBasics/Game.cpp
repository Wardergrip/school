#include "pch.h"
#include "Game.h"

#include "Matrix2x3.h"
#include "Texture.h"
#include "utils.h"
using namespace utils;

Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_TransVertices{}
	,m_IsSelected{false}
	,m_pDiamondTexture{nullptr}
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	const float diamondSize{ 48 };
	m_Vertices.push_back(Point2f{ 0, diamondSize / 2 });
	m_Vertices.push_back(Point2f{ diamondSize / 2, diamondSize });
	m_Vertices.push_back(Point2f{ diamondSize, diamondSize / 2 });
	m_Vertices.push_back(Point2f{ diamondSize / 2, 0 });
	m_Translation = Vector2f{};
	m_Scale = 1;
	m_Angle = 0;
	m_pDiamondTexture = new Texture{ "Resources/Diamond.png" };
}

void Game::Cleanup( )
{
	delete m_pDiamondTexture;
	m_pDiamondTexture = nullptr;
}

void Game::Update( float elapsedSec )
{
	const float rotationSpeed{ 60 };
	const float movementSpeed{ 120 };
	const float scaleSpeed{ 3 };
	// Check keyboard state
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if ( pStates[SDL_SCANCODE_A] )
	{
		m_Angle += rotationSpeed * elapsedSec;
	}
	if ( pStates[SDL_SCANCODE_D])
	{
		m_Angle -= rotationSpeed * elapsedSec;
	}
	if ( pStates[SDL_SCANCODE_W])
	{
		m_Scale *= 1 + (scaleSpeed * elapsedSec);
	}
	if ( pStates[SDL_SCANCODE_S])
	{
		m_Scale /= 1 + (scaleSpeed * elapsedSec);
	}
	if ( pStates[SDL_SCANCODE_UP] )
	{
		m_Translation.y += movementSpeed * elapsedSec;
	}
	if ( pStates[SDL_SCANCODE_DOWN])
	{
		m_Translation.y -= movementSpeed * elapsedSec;
	}
	if ( pStates[SDL_SCANCODE_LEFT])
	{
		m_Translation.x -= movementSpeed * elapsedSec;
	}
	if ( pStates[SDL_SCANCODE_RIGHT])
	{
		m_Translation.x += movementSpeed * elapsedSec;
	}

	Matrix2x3 matTranslate, matRotate, matScale, matCenter, matWorld;
	matTranslate.SetAsTranslate(m_Translation);
	matCenter.SetAsTranslate(-24.f, -24.f);
	matRotate.SetAsRotate(m_Angle);
	matScale.SetAsScale(m_Scale, m_Scale);
	matWorld = matTranslate * matRotate * matScale * matCenter;

	m_TransVertices = matWorld.Transform(m_Vertices);
}

void Game::Draw( ) const
{
	ClearBackground( );

	SetColor(Color4f{ 0,0,1.0f,1.0f });
	DrawPolygon(m_Vertices, true, 2.0f);

	glPushMatrix();
	{
		glTranslatef(m_Translation.x, m_Translation.y, 0);
		glRotatef(m_Angle, 0.f, 0.f, 1.f);
		glScalef(m_Scale, m_Scale, 1.f);
		glTranslatef(-24.f, -24.f, 0);
		m_pDiamondTexture->Draw();
	}
	glPopMatrix();

	if (m_IsSelected) SetColor(Color4f{ 1.0f,0,0,1.0f });
	else SetColor(Color4f{ 0,0,1.0f,1.0f });
	DrawPolygon(m_TransVertices, true, 2.0f);
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
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		if (utils::IsPointInPolygon(Point2f{ float(e.x),float(e.y) }, m_TransVertices))
		{
			m_IsSelected = !m_IsSelected;
		}
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
