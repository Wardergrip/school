#include "pch.h"
#include "Sprite.h"
#include <iostream>
using namespace utils;

#pragma region Structors
Sprite::Sprite(const std::string& filename, int nrCols, int nrRows, int nrOfFrames, float frameSec, float scale, bool loopOnce)
	:m_Cols{nrCols}
	,m_Rows{nrRows}
	,m_NrOfFrames{nrOfFrames}
	,m_FrameSec{frameSec}
	,m_AccuSec{ 0 }	
	,m_ActFrame{ 0 }
	,m_Scale{scale}
	,m_LoopOnce{loopOnce}
{
	if (!TextureFromFile(filename, m_Texture))
	{
		std::cout << "SpriteClassError: failed to load image, is the filename correct?\n";
	}
}
Sprite::Sprite(const std::string& filename) :Sprite(filename, 1, 1, 1, 1, 1)
{
}
Sprite::Sprite()
	:m_Texture{}
	, m_Cols{ 1 }
	, m_Rows{ 1 }
	, m_NrOfFrames{ 1 }
	, m_FrameSec{ 1 }
	, m_AccuSec{ 0 }
	, m_ActFrame{ 0 }
	, m_Scale{ 1 }
	, m_LoopOnce{ false }
{
}
Sprite::~Sprite()
{
	DeleteTexture(m_Texture);
}
#pragma endregion Structors

// =================================================================================== //

bool Sprite::ChangeTexture(const std::string& filename, int nrCols, int nrRows, int nrOfFrames, float frameSec, float scale, bool loopOnce)
{
	m_Cols = nrCols;
	m_Rows = nrRows;
	m_NrOfFrames = nrOfFrames;
	m_FrameSec = frameSec;
	m_AccuSec = 0;
	m_ActFrame = 0;
	m_Scale = scale;
	m_LoopOnce = loopOnce;
	if (!TextureFromFile(filename, m_Texture))
	{
		std::cout << "SpriteClassError: failed to update image, is the filename correct?\n";
		return false;
	}
	return true;
}

bool Sprite::Update(float elapsedSec)
{
	if (m_LoopOnce)
	{
		m_AccuSec += elapsedSec;
		if (m_AccuSec > m_FrameSec)
		{
			++m_ActFrame;
			if (m_ActFrame >= m_NrOfFrames)
			{
				return true;
			}
			m_AccuSec -= m_FrameSec;
		}
		return false;
	}
	else 
	{
	m_AccuSec += elapsedSec;
	if (m_AccuSec > m_FrameSec)
	{
		++m_ActFrame %= m_NrOfFrames;
		m_AccuSec -= m_FrameSec;
	}
	}
	return true;
}

void Sprite::InitLoopOnce()
{
	m_AccuSec = 0;
	m_ActFrame = 0;
}
void Sprite::ChangeLoopOnce(bool loopOnce)
{
	m_LoopOnce = loopOnce;
}

void Sprite::Draw(const Point2f& pos)
{
	Rectf srcRect{};
	srcRect.width = m_Texture.width / m_Cols;
	srcRect.height = m_Texture.height / (m_NrOfFrames / m_Cols);
	srcRect.left = (m_ActFrame % m_Cols) * srcRect.width;
	srcRect.bottom = ((m_ActFrame / m_Cols) + 1) * srcRect.height;

	Rectf destRect{};
	destRect.left = pos.x;
	destRect.bottom = pos.y;
	destRect.width = srcRect.width * m_Scale;
	destRect.height = srcRect.height * m_Scale;

	DrawTexture(m_Texture, destRect, srcRect);
}

// Gives the width of the scaled frame
float Sprite::GetFrameWidth()
{
	return ((m_Texture.width / m_Cols) * m_Scale);
}
// Gives the height of the scaled frame
float Sprite::GetFrameHeight()
{
	return ((m_Texture.height / m_Rows) * m_Scale);
}
