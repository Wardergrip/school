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
	,m_Orbit{Circlef{Point2f{250,250},100}}
	,m_Angle{0}
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

void Card::Draw() const
{
	glPushMatrix();
	{
		glTranslatef(m_Orbit.center.x, m_Orbit.center.y, 0);

		glScalef(0.5f, 0.5f, 1);
		glRotatef(m_Angle, 0, 0, 1);
		glTranslatef(m_Orbit.radius, m_Orbit.radius, 0);

		glRotatef(90, 0, 0, 1);

		m_pTexture->Draw();
	}
	glPopMatrix();
}

void Card::Update(float elapsedSec)
{
	m_Angle += 90 * elapsedSec;
	if (m_Angle >= 360.0f) m_Angle -= 360.0f;
}

float Card::GetWidth() const
{
	return m_Width;
}

float Card::GetHeight() const
{
	return m_Height;
}

void Card::SetAngle(float angle)
{
	m_Angle = angle;
}
