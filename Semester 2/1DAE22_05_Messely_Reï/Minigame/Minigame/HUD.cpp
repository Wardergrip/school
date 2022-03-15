#include "pch.h"
#include "HUD.h"
#include "Texture.h"

#include <iostream>

HUD::HUD(const Point2f& topLeft, int totalPowerUps)
	:m_BottomLeft{topLeft.x,topLeft.y}
	,m_TotalPowerUps{totalPowerUps}
	,m_HitPowerUps{0}
	,m_pLeftTexture{ new Texture{"Resources/Images/HudLeft.png"}}
	,m_pRightTexture{ new Texture{"Resources/Images/HudRight.png"}}
	,m_pPowerUpTexture{ new Texture{"Resources/Images/HudPowerUp.png"}}
{
	m_BottomLeft.y -= m_pLeftTexture->GetHeight();
}

HUD::~HUD()
{
	delete m_pLeftTexture;
	m_pLeftTexture = nullptr;
	delete m_pRightTexture;
	m_pRightTexture = nullptr;
	delete m_pPowerUpTexture;
	m_pPowerUpTexture = nullptr;
}

void HUD::Draw() const
{
	const float leftWidth{ m_pLeftTexture->GetWidth() };
	const float midWidth{ m_pPowerUpTexture->GetWidth() / 2.f };
	m_pLeftTexture->Draw(m_BottomLeft);

	for (int i{ 0 }; i < m_TotalPowerUps; ++i)
	{
		float width{midWidth};
		if (m_HitPowerUps >= (i+1)) width = 0;
		Rectf srcRect{ width,0,midWidth,m_pPowerUpTexture->GetHeight()};
		m_pPowerUpTexture->Draw(Rectf{ m_BottomLeft.x + leftWidth + i * midWidth, m_BottomLeft.y, midWidth, m_pPowerUpTexture->GetHeight()}, srcRect);
	}

	m_pRightTexture->Draw(Point2f{ m_BottomLeft.x + leftWidth + m_TotalPowerUps * midWidth,m_BottomLeft.y});
}

void HUD::PowerUpHit()
{
	++m_HitPowerUps;
}
