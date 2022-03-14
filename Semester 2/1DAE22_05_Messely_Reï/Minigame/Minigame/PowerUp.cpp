#include "pch.h"
#include "PowerUp.h"
#include "Texture.h"
#include "utils.h"
#include <iostream>
using namespace utils;

PowerUp::PowerUp(const Point2f& center, PowerUp::Type type)
	:m_Type{type}
	,m_pTexture{new Texture("resources/images/PowerUp.png")}
	,m_RotSpeed{360}
	,m_TextClip{0, m_pTexture->GetHeight(), m_pTexture->GetWidth(),m_pTexture->GetHeight() / 2}
	,m_Shape{center,m_pTexture->GetWidth() / 2}
	,m_Angle{0}
{
	if (type == Type::green) m_TextClip = Rectf{ 0,m_pTexture->GetHeight() / 2,m_pTexture->GetWidth(),m_pTexture->GetHeight() / 2};
	std::cout << "Creating powerup\n";
}

PowerUp::~PowerUp()
{
	delete m_pTexture;
	m_pTexture = nullptr;
	std::cout << "Destroying powerup\n";
}

void PowerUp::Update(float elapsedSec)
{
	m_Angle += m_RotSpeed * elapsedSec;
	if (m_Angle >= 360.0f) m_Angle -= 360.0f;
}

void PowerUp::Draw() const
{
	// T R S
	glPushMatrix(); // Store current matrix in some container
	{
		glTranslatef(m_Shape.center.x, m_Shape.center.y, 0);
		glRotatef(m_Angle, 0, 0, 1);
		
		//m_pTexture->Draw(Point2f{-m_pTexture->GetWidth() / 2,-m_pTexture->GetHeight() / 4}, m_TextClip); 
		glTranslatef(-m_pTexture->GetWidth() / 2, -m_pTexture->GetHeight() / 4, 0);

		m_pTexture->Draw(Point2f{}, m_TextClip);
	}
	glPopMatrix(); // Restore the stored matrix
}

bool PowerUp::IsOverlapping(const Rectf& rect) const
{
	return utils::IsOverlapping(rect, m_Shape);
}
