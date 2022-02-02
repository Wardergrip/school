#include "pch.h"		
#include "Tile.h"
#include "utils.h"
#include <iostream>
using namespace utils;

Tile::Tile(const Rectf& dstRect, const std::string& textPath, int nrAnimals)
	:m_DstRect{dstRect}
	,m_NrAnimals{nrAnimals - 1}
	,m_IsPlayable{ true }
	,m_IsActivated{false}
{
	Randomize();
	if (!TextureFromFile(textPath, m_Texture))
	{
		std::cout << "Error loading image\n";
	}
}
Tile::~Tile()
{
	DeleteTexture(m_Texture);
}

void Tile::Draw()
{
	Rectf srcRect{};
	srcRect.width = m_Texture.width / (m_NrAnimals + 1);
	srcRect.height = m_Texture.height;
	srcRect.left = (m_CurrentAnimal % (m_NrAnimals + 1)) * srcRect.width;
	srcRect.bottom = srcRect.height;

	DrawTexture(m_Texture, m_DstRect, srcRect);
	if (m_IsActivated && m_IsPlayable)
	{
		SetColor(0.4f, 0.4f, 0.4f, 0.4f); // Grey
		FillRect(m_DstRect);
		SetColor( 1,0,0,1 ); // Red
		DrawRect(m_DstRect.left, m_DstRect.bottom, m_DstRect.width / 4, m_DstRect.height / 4);
		DrawRect(m_DstRect.left + (3 * m_DstRect.width) / 4, m_DstRect.bottom, m_DstRect.width / 4, m_DstRect.height / 4);
	}
}

void Tile::CheckActivation(const Point2f& pos)
{
	if (m_IsPlayable)
	{
		if (IsInsideRect(m_DstRect, pos))
		{
			m_IsActivated = true;
		}
		else
		{
			m_IsActivated = false;
		}
	}
}

bool Tile::CheckHit(const Point2f& pos)
{
	if (m_IsPlayable)
	{
		const Rectf buttonLeft{ m_DstRect.left, m_DstRect.bottom, m_DstRect.width / 4, m_DstRect.height / 4 };
		const Rectf buttonRight{ m_DstRect.left + (3 * m_DstRect.width) / 4, m_DstRect.bottom, m_DstRect.width / 4, m_DstRect.height / 4 };
		if (IsInsideRect(buttonLeft, pos))
		{
			--m_CurrentAnimal;
			if (m_CurrentAnimal < 0) m_CurrentAnimal = m_NrAnimals;
			return true;
		}
		else if (IsInsideRect(buttonRight, pos))
		{
			++m_CurrentAnimal;
			if (m_CurrentAnimal > m_NrAnimals) m_CurrentAnimal = 0;
			return true;
		}
	}
	return false;
}

int Tile::GetCurrentAnimal()
{
	return (m_CurrentAnimal);
}

void Tile::Deactivate()
{
	m_IsPlayable = false;
}

void Tile::Randomize()
{
	m_CurrentAnimal = GenerateRandom(0, m_NrAnimals - 1);
}