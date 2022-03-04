#include "pch.h"
#include "PickUp.h"
#include "Texture.h"
#include "utils.h"

PickUp::PickUp(Texture* texture, int horAmount, float maxSec, int vertAmount, int row)
	:GameObject()
	,m_Type{PickUpType::coin}
	,m_pTexture{texture}
	,m_Position{}
	,m_Frames{horAmount}
	,m_ActFrame{0}
	,m_MaxSec{maxSec}
	,m_AccuSec{0}
{
	if (texture != nullptr)
	{
		AdjustRectToTexture(horAmount, maxSec, vertAmount, row);
	}
}

PickUp::~PickUp()
{
	if (!m_pTexture) return;
	delete m_pTexture;
	m_pTexture = nullptr;
}

void PickUp::Draw() const
{
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, 0);
		glScalef(1.75f, 1.75f, 0);
		m_pTexture->Draw(Point2f{ 0,0 }, m_Rect);
	}
	glPopMatrix();
}

void PickUp::Update(float elapsedSec)
{
	UpdateAnim(elapsedSec);
}

void PickUp::UpdateAnim(float elapsedSec)
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec >= m_MaxSec)
	{
		++m_ActFrame;
		m_ActFrame %= m_Frames;
		m_AccuSec = 0;
	}
	m_Rect.left = m_ActFrame * m_Rect.width;
}

bool PickUp::IsOverlapping(const Rectf& other) const
{
	return utils::IsOverlapping(Rectf{m_Position.x,m_Position.y,m_Rect.width,m_Rect.height}, other);
}

PickUp::PickUpType PickUp::GetType() const
{
	return m_Type;
}

void PickUp::AdjustRectToTexture(int horAmount, float maxSec, int vertAmount, int row)
{
	m_Rect = Rectf{ 0,m_pTexture->GetHeight() - (row * (m_pTexture->GetHeight() / vertAmount)),m_pTexture->GetWidth() / horAmount,m_pTexture->GetHeight() / vertAmount };
}
