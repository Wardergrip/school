#include "pch.h"
#include "Card.h"
#include "Texture.h"
#include <iostream>

Card::Card(Suit suit, int rank)
	:m_MinRank{1}
	,m_MaxRank{13}
	,m_pTexture{nullptr}
	,m_Scale{0.5f}
	,m_Width{}
	,m_Height{}
	,m_Suit{suit}
	,m_Rank{rank}
{
	if (!((rank >= m_MinRank) && (rank <= m_MaxRank))) return;
	std::cout << "Resources/" + std::to_string(int(suit) * 100 + rank) + ".png" << '\n';
	m_pTexture = new Texture{ "Resources/" + std::to_string(int(suit) * 100 + rank) + ".png" };
	m_Width = m_pTexture->GetWidth() * m_Scale;
	m_Height = m_pTexture->GetHeight() * m_Scale;
}

Card::~Card()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Card::Draw(const Rectf& destRect) const
{
	m_pTexture->Draw(Rectf{
		destRect.left, 
		destRect.bottom, 
		destRect.width, 
		destRect.height});
}

float Card::GetWidth() const
{
	return m_Width;
}

float Card::GetHeight() const
{
	return m_Height;
}
