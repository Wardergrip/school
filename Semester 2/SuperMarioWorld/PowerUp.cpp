#include "pch.h"
#include "PowerUp.h"
#include "Texture.h"
#include "utils.h"

PowerUp::PowerUp(Texture* texture, int frameAmount, float maxSec)
	:GameObject()
	,m_pTexture{texture}
	,m_Velocity{}
	,m_Position{}
	,m_Frames{frameAmount}
	,m_ActFrame{0}
	,m_MaxSec{maxSec}
	,m_AccuSec{0}
{
	m_Rect = Rectf{0,0,m_pTexture->GetWidth() / frameAmount,m_pTexture->GetHeight()};
}

PowerUp::~PowerUp()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void PowerUp::Draw() const
{
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, 0);
		m_pTexture->Draw(Point2f{ 0,0 }, m_Rect);
	}
	glPopMatrix();
}

void PowerUp::Update(float elapsedSec)
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec >= m_MaxSec)
	{
		++m_ActFrame;
		m_ActFrame %= m_Frames;
		m_AccuSec = 0;
	}
	m_Rect.left = m_ActFrame * m_Rect.width;
	m_Position += m_Velocity;
}

bool PowerUp::IsOverlapping(const Rectf& other) const
{
	return utils::IsOverlapping(m_Rect,other);
}
