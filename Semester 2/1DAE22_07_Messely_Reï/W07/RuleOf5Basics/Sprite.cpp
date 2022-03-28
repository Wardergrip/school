#include "pch.h"
#include "Sprite.h"

#include "Texture.h"
#include <iostream>

Sprite::Sprite( const std::string& path, int cols, int rows, float frameSec )
	: m_Cols( cols )
	, m_Rows( rows )
	, m_FrameSec( frameSec )
	, m_AccuSec{}
	, m_ActFrame{}
	, m_pTexture{ new Texture( path ) }
{
	//m_pTexture = new Texture( path );
	std::cout << "Normal constructor\n";
}

Sprite::Sprite(Sprite&& s) noexcept
	:m_Cols{s.m_Cols}
	,m_Rows{s.m_Rows}
	,m_FrameSec{s.m_FrameSec}
	,m_AccuSec{s.m_AccuSec}
	,m_ActFrame{s.m_ActFrame}
{
	m_pTexture = s.m_pTexture;

	s.m_pTexture = nullptr;
	s.m_Cols = 0;
	s.m_Rows = 0;
	s.m_FrameSec = 0;
	s.m_AccuSec = 0;
	s.m_ActFrame = 0;
	std::cout << "Move constructor\n";
}

Sprite& Sprite::operator=(Sprite&& s)noexcept
{
	if (m_pTexture) delete m_pTexture;
	m_pTexture = s.m_pTexture;
	m_Cols = s.m_Cols;
	m_Rows = s.m_Rows;
	m_FrameSec = s.m_FrameSec;
	m_AccuSec = s.m_AccuSec;
	m_ActFrame = s.m_ActFrame;

	s.m_pTexture = nullptr;
	s.m_Cols = 0;
	s.m_Rows = 0;
	s.m_FrameSec = 0;
	s.m_AccuSec = 0;
	m_ActFrame = 0;
	std::cout << "Move operator\n";
	return *this;
}

Sprite::~Sprite( )
{
	delete m_pTexture;
	std::cout << "Destructor\n";
}

void Sprite::Update( float elapsedSec )
{
	m_AccuSec += elapsedSec;

	if ( m_AccuSec > m_FrameSec )
	{
		// Go to next frame
		++m_ActFrame;
		if ( m_ActFrame >= m_Cols * m_Rows )
		{
			m_ActFrame = 0;
		}

		// Only keep the remaining time
		m_AccuSec -= m_FrameSec;
	}
}

void Sprite::Draw( const Point2f& pos, float scale )
{
	// frame dimensions
	const float frameWidth{  m_pTexture->GetWidth() / m_Cols };
	const float frameHeight{  m_pTexture->GetHeight() / m_Rows };
	int row = m_ActFrame / m_Cols;
	int col = m_ActFrame % m_Cols;

	Rectf srcRect;
	srcRect.height = frameHeight;
	srcRect.width = frameWidth;
	srcRect.left = m_ActFrame % m_Cols * srcRect.width;
	srcRect.bottom = m_ActFrame / m_Cols * srcRect.height + srcRect.height;
	Rectf destRect{ pos.x, pos.y,srcRect.width * scale,srcRect.height * scale };
	m_pTexture->Draw( destRect, srcRect );
}

float Sprite::GetFrameWidth( )
{
	return m_pTexture->GetWidth( ) / m_Cols;
}

float Sprite::GetFrameHeight( )
{
	return m_pTexture->GetHeight( ) / m_Rows;
}

